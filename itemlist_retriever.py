import json  # used to convert string obtained from database to a dictionary
import time  # used to sleep the program for a certain amount of time
from serial import Serial  # used to connect to the serial port
import mysql.connector  # used to connect to the database


PORT = "COM9"  # change this to the port that the arduino is connected to
BAUDRATE = 9600  # change this to the baudrate that the serial port is using

# change this to the credentials of the database that you are using
CREDENTIALS = {
    "host": "aws.connect.psdb.cloud",
    "user": "yaoj2ulg7876aqw6i0kd",
    "password": "pscale_pw_kQnhJDvpSU1FwgFyr6VMYzgPOvblBcdOWoauO69hbj0",
    "database": "pam-project",
    "use_pure": True,
    "connect_timeout": 30,
}

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
    def __init__(self, port, baudrate):
        self.port = port
        self.baudrate = baudrate
        self.ser = Serial(port, baudrate)
        print("Connected to serial -- success")

    def write(self, data):
        self.ser.write(data.encode())

    def read(self):
        try:
            return self.ser.readline().decode().strip()
        except:
            return ">>>>> ERROR <<<<<"

    def close(self):
        self.ser.close()


class BotCommander:
    def __init__(self, db, ser):
        self.db = db
        self.ser = ser


def main():
    db = DatabaseConnection(CREDENTIALS)
    ser = SerialConnection(PORT, BAUDRATE)
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
