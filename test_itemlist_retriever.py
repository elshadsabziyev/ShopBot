import unittest
from unittest.mock import patch
from itemlist_retriever import DatabaseConnection, SerialConnection


class TestDatabaseConnection(unittest.TestCase):
    def setUp(self):
        self.credentials = {
            "host": "localhost",
            "user": "root",
            "password": "password",
            "database": "test_db",
        }
        self.db = DatabaseConnection(self.credentials)

    def test_fetch_all_items(self):
        expected_items = {1: ["item1", "item2"], 2: ["item3", "item4"]}
        with patch.object(self.db.conn, "cursor") as mock_cursor:
            mock_cursor.return_value.fetchall.return_value = [
                (1, '["item1", "item2"]'),
                (2, '["item3", "item4"]'),
            ]
            items_dict = self.db.fetch_all_items()
            self.assertEqual(items_dict, expected_items)


class TestSerialConnection(unittest.TestCase):
    def setUp(self):
        self.baudrate = 9600
        self.ser = SerialConnection(self.baudrate)

    def test_write(self):
        with patch.object(self.ser.ser, "write") as mock_write:
            data = "test data"
            self.ser.write(data)
            mock_write.assert_called_once_with(data.encode())

    def test_read(self):
        with patch.object(self.ser.ser, "readline") as mock_readline:
            mock_readline.return_value.decode.return_value = "test"
            result = self.ser.read()
            self.assertEqual(result, "test")

    def test_close(self):
        with patch.object(self.ser.ser, "close") as mock_close:
            self.ser.close()
            mock_close.assert_called_once()


if __name__ == "__main__":
    unittest.main()
import unittest
from unittest.mock import patch
from itemlist_retriever import DatabaseConnection, SerialConnection, main


class TestDatabaseConnection(unittest.TestCase):
    def setUp(self):
        self.credentials = {
            "host": "localhost",
            "user": "root",
            "password": "password",
            "database": "test_db",
        }
        self.db = DatabaseConnection(self.credentials)

    def test_fetch_all_items(self):
        expected_items = {1: ["item1", "item2"], 2: ["item3", "item4"]}
        with patch.object(self.db.conn, "cursor") as mock_cursor:
            mock_cursor.return_value.fetchall.return_value = [
                (1, '["item1", "item2"]'),
                (2, '["item3", "item4"]'),
            ]
            items_dict = self.db.fetch_all_items()
            self.assertEqual(items_dict, expected_items)


class TestSerialConnection(unittest.TestCase):
    def setUp(self):
        self.baudrate = 9600
        self.ser = SerialConnection(self.baudrate)

    def test_write(self):
        with patch.object(self.ser.ser, "write") as mock_write:
            data = "test data"
            self.ser.write(data)
            mock_write.assert_called_once_with(data.encode())

    def test_read(self):
        with patch.object(self.ser.ser, "readline") as mock_readline:
            mock_readline.return_value.decode.return_value = "test"
            result = self.ser.read()
            self.assertEqual(result, "test")

    def test_close(self):
        with patch.object(self.ser.ser, "close") as mock_close:
            self.ser.close()
            mock_close.assert_called_once()


class TestMain(unittest.TestCase):
    def test_main(self):
        # TODO: Add your test case for the main function here
        pass


if __name__ == "__main__":
    unittest.main()
