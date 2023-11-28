#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <SPI.h>
#include <Servo.h>

// RC522 MODULE    Uno/Nano     MEGA
// SDA             D10          D9
// SCK             D13          D52
// MOSI            D11          D51
// MISO            D12          D50
// IRQ             N/A          N/A
// GND             GND          GND
// RST             D9           D8
// 3.3V            3.3V         3.3V

#define servoPin 3            // Set servo pin
String previousUID = "0";     // Do not change //
String previousRFIDUID = "0"; // Do not change //
String fromSerialUID = "0";   // Do not change //
String fromRFIDUID = "0";     // Do not change //
String readSerialFlag = "0";  // Do not change //
int printCounter = 0;         // Do not change //
int pickUpTimeout = 1500;     // Set timeout for picking up item
int serialBaudRate = 9600;    // Set serial baud rate
int optimizationDelay = 50;   // Fine tune this value to optimize performance
int firstMainLoop = 1;        // Do not change //
Servo myServo;                // Do not change //
MFRC522 card(10, 9);          // SDA, RST set up for MEGA
int motor1pin1 = 2;           // pin 2 on L293D
int motor1pin2 = 4;           // pin 7 on L293D
int motor2pin1 = 7;           // pin 10 on L293D
int motor2pin2 = 8;           // pin 15 on L293D
int enable1pin = 5;           // pin 1 on L293D
int enable2pin = 6;           // pin 9 on L293D

void setup()
{
  Serial.begin(serialBaudRate);
  SPI.begin();
  card.PCD_Init();
  card.PCD_DumpVersionToSerial();
  myServo.attach(servoPin);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(enable1pin, OUTPUT);
  pinMode(enable2pin, OUTPUT);
  analogWrite(enable1pin, 150);
  analogWrite(enable2pin, 150);
}

void loop()
{
  if (firstMainLoop == 1)
  {
    makeStartupNoiseUsingServo();
    firstMainLoop = 0;
  }
  if (readSerialFlag == "0")
  {
    // if there is a new RFID from DB, set flag to 1
    fromSerialUID = readSerial();
    if (fromSerialUID != "0")
    {
      readSerialFlag = "1";
      moveForward();
    }
  }
  delay(optimizationDelay);
  fromRFIDUID = readRFIDUID();
  delay(optimizationDelay);
  // if there is a new RFID from DB and RFID from RFID reader are the same
  if (fromSerialUID == fromRFIDUID && fromSerialUID != "0" && fromRFIDUID != "0")
  {
    Serial.println("Going to pick item");
    pickItem();
    delay(pickUpTimeout);
    // set flag to 0
    readSerialFlag = "0";
    previousUID = "0";
    previousRFIDUID = "0";
    Serial.println("Item picked and ready to get another RFID");
  }
  // if there is a new RFID from DB and RFID from RFID reader are not the same
  else if (fromSerialUID == "0")
  {
    if (printCounter % 11 == 0)
    {
      Serial.println("Waiting for RFID from DB");
    }
  }
  // if there is no new RFID from DB and RFID from RFID reader are not the same
  else if (fromRFIDUID == "0")
  {
    if (printCounter % 11 == 0)
    {
      void makeStartupNoiseUsingServo();
      Serial.println("Waiting for RFID from RFID reader");
    }
  }
  else
  {
    Serial.println("RFID from DB and RFID from RFID reader are not the same");
  }
  // printCounter is used to print message every 10 iterations
  printCounter++;
}

// function to read RFID from DB via serial
String readSerial()
{
  String fromSerialRFID = "";
  while (Serial.available() > 0)
  {
    fromSerialRFID = Serial.readString();
  }
  char fromSerialRFIDArray[fromSerialRFID.length() + 1];
  fromSerialRFID.toCharArray(fromSerialRFIDArray, fromSerialRFID.length() + 1);
  String fromSerialRFIDString = "";
  for (int i = 0; i < fromSerialRFID.length(); i++)
  {
    fromSerialRFIDString += fromSerialRFIDArray[i];
  }
  int index = fromSerialRFIDString.indexOf('\n');
  if (index != -1)
  {
    fromSerialRFIDString = fromSerialRFIDString.substring(0, index);
  }

  if (fromSerialRFIDString.length() != 0)
  {
    previousUID = fromSerialRFIDString;
  }
  return fromSerialRFIDString.length() != 0 ? fromSerialRFIDString : previousUID;
}

// function to read RFID from RFID reader
String readRFIDUID()
{
  String fromRFID = "";
  while (!card.PICC_IsNewCardPresent() || !card.PICC_ReadCardSerial())
  {
    return "0";
  }
  for (byte i = 0; i < card.uid.size; i++)
  {
    fromRFID += String(card.uid.uidByte[i] < 0x10 ? " 0" : " ");
    fromRFID += String(card.uid.uidByte[i], HEX);
  }
  fromRFID.replace(" ", "");
  char fromRFIDArray[fromRFID.length() + 1];
  fromRFID.toCharArray(fromRFIDArray, fromRFID.length() + 1);
  String fromRFIDString = "";
  for (int i = 0; i < fromRFID.length(); i++)
  {
    fromRFIDString += fromRFIDArray[i];
  }
  if (fromRFIDString.length() != 0)
  {
    previousRFIDUID = fromRFIDString;
  }
  return fromRFIDString.length() != 0 ? fromRFIDString : previousRFIDUID;
}

void moveForward()
{
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void pickItem()
{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(4000);
  for (int i = 0; i <= 150; i += 45)
  {
    myServo.write(i);
    delay(50);
  }
  for (int i = 150; i >= 0; i -= 45)
  {
    myServo.write(i);
    delay(50);
  }
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void makeStartupNoiseUsingServo()
{
  myServo.write(90);
  delay(100);
  myServo.write(0);
  delay(100);
  myServo.write(90);
  delay(100);
  myServo.write(0);
  delay(100);
}
