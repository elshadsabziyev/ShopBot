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

#define servoPin 10
String previousUID = "0";
String previousRFIDUID = "0";
String fromSerialUID = "0";
String fromRFIDUID = "0";
String readSerialFlag = "0";
int printCounter = 0;
Servo myServo;
MFRC522 card(9, 8); // SDA, RST

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  card.PCD_Init();
  card.PCD_DumpVersionToSerial();
  myServo.attach(servoPin);
}

void loop()
{
  // fromSerialUID = readSerial(); once it readed and lenght of it > 0 never read again until flag readSerailFlag is 1
  if (readSerialFlag == "0")
  {
    fromSerialUID = readSerial();
    if (fromSerialUID != "0")
    {
      readSerialFlag = "1";
    }
  }
  delay(100);
  fromRFIDUID = readRFIDUID();
  delay(100);
  if (fromSerialUID == fromRFIDUID && fromSerialUID != "0" && fromRFIDUID != "0")
  {
    // pickItem();
    Serial.println("Going to pick item");
    pickItem();
    delay(500);
    // set flag to 0
    readSerialFlag = "0";
    previousUID = "0";
    previousRFIDUID = "0";
    Serial.println("Item picked and ready to get another RFID");
  }
  else if (fromSerialUID == "0")
  {
    if (printCounter % 11 == 0)
    {
      Serial.println("Waiting for RFID from DB");
    }
  }
  else if (fromRFIDUID == "0")
  {
    if (printCounter % 11 == 0)
    {
      Serial.println("Waiting for RFID from RFID reader");
    }
  }
  else
  {
    Serial.println("RFID from DB and RFID from RFID reader are not the same");
  }
  printCounter++;
}

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

void pickItem()
{
  myServo.write(90);
  delay(2000);
  myServo.write(0);
}

void lightUpOnBoardLED()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}