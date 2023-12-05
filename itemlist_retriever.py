import json  # used to convert string obtained from database to a dictionary
import time  # used to sleep the program for a certain amount of time
from serial import Serial  # used to connect to the serial port
import mysql.connector  # used to connect to the database
from credentials import CREDENTIALS  # used to store the credentials for the database
from os import name as os_name  # used to check the operating system

BAUDRATE = (
    9600  # baudrate of the serial connection to the arduino, change this if needed
)


# used to store the previous items that were retrieved from the database
# this is used to check if the items have changed during the next iteration of the loop
prev_items = None


# Class that is used to connect to the database
class DatabaseConnection:
    def __init__(self, credentials):
        self.conn = mysql.connector.connect(**credentials)  # connect to the database
        while not self.conn.is_connected():
            print("Connecting to database...")
            time.sleep(1)

    # Function that is used to fetch all the items from the database
    def fetch_all_items(self):
        cursor = self.conn.cursor()
        query = "SELECT id, products from `Order`"
        cursor.execute(query)
        rows = cursor.fetchall()
        items_dict = {}
        for row in rows:
            items_dict[row[0]] = json.loads(row[1])
        return items_dict


class SerialConnection:
    def __init__(self, baudrate):
        self.port = self.find_ARDUINO_serial_port()
        self.baudrate = baudrate
        self.ser = Serial(self.port, self.baudrate)
        print("Connected to serial -- success")

    def write(self, data):
        self.ser.write(data.encode())

    @staticmethod
    def find_ARDUINO_serial_port():
        if os_name == "nt":
            for i in range(0, 256):
                try:
                    port = "COM" + str(i)
                    ser = Serial(port)
                    return port
                except:
                    pass
        elif os_name == "posix":
            for port_num in range(0, 256):
                for port_prefix in ["/dev/ttyUSB", "/dev/ttyACM"]:
                    try:
                        port = port_prefix + str(port_num)
                        ser = Serial(port)
                        ser.close()
                        return port
                    except:
                        pass

        else:
            raise Exception("Unknown OS")

    def read(self):
        try:
            return self.ser.readline().decode().strip()
        except Exception as e:
            print(e)

    def close(self):
        self.ser.close()


def main():
    db = DatabaseConnection(CREDENTIALS)
    ser = SerialConnection(BAUDRATE)
    items_dict = db.fetch_all_items()
    prev_items = items_dict
    iter_cnt = 0
    while True:
        if iter_cnt % 5 == 0 and iter_cnt != 0:
            db.conn.close()
            db = DatabaseConnection(CREDENTIALS)
            items_dict = db.fetch_all_items()

        if max(items_dict.keys()) != max(prev_items.keys()):
            print(
                "Items changed " + "New item : " + items_dict[max(items_dict.keys())][0]
            )
            to_write = items_dict[max(items_dict.keys())][0].lower() + "\n"
            prev_items = items_dict
            ser.write(to_write)
        else:
            print("Items not changed")
        print("Reading from serial... :" + ser.read())
        iter_cnt += 1
        time.sleep(0.1)


if __name__ == "__main__":
    main()
    # test()
