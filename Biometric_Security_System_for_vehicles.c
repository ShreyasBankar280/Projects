
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int temp;


#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;
#include <EEPROM.h>

#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);
 
  
#include <SoftwareSerial.h>
SoftwareSerial fingerPrint(2, 3);

int Status;

#include <Adafruit_Fingerprint.h>
uint8_t id;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);

#define enroll 14
#define del 15
#define up 16
#define down 17

#define r1 6
#define bz 7
int st;

void setup() 
{
  
    pinMode(enroll, INPUT);
    pinMode(up, INPUT); 
    pinMode(down, INPUT); 
    pinMode(del, INPUT); 
    pinMode(r1, OUTPUT);
    pinMode(bz, OUTPUT);
   
     EEPROM.write(0,1);
    lcd.begin(16,2);
    lcd.print("Biometric_Authe");
    lcd.setCursor(0,1);
    lcd.print("for vehicle ");
    delay(2000);
    lcd.clear();

    lcd.print("Peoject By");
    
delay(1000);
    lcd.clear();
    lcd.print("aditya,vishvajit");
 lcd.setCursor(0,1);
   lcd.print("shreyash,vaibhav");
    finger.begin(57600);
    Serial.begin(9600);
    lcd.clear();
    lcd.print("Finding Module");
    lcd.setCursor(0,1);
    delay(1000);
    if (finger.verifyPassword()) 
    {
      Serial.println("Found fingerprint sensor!");
      lcd.clear();
      lcd.print("Found Module ");
      delay(1000);
    } 
    else 
    {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.clear();
    lcd.print("module not Found");
    lcd.setCursor(0,1);
    lcd.print("Check Connections");
    while (1);
    }
}

void loop() 
{
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();

   temp =sensors.getTempCByIndex(0);
   delay(100);

  lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Press UP/Down ");
  Serial.println("Press UP/Down");
 lcd.setCursor(0,1);
 lcd.print("to start System");
 delay(1000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Voltage:");
 lcd.print(busvoltage);
 lcd.setCursor(0,1);
 lcd.print("Temp:");
 lcd.print(temp);
 delay(1000);
 Serial.println("start system");
// digitalWrite(closeLight, HIGH);
 if(digitalRead(up)==0 || digitalRead(down)==0)
 {
  for(int i=0;i<5;i++)
  {
    lcd.clear();
    lcd.print("Place Finger");
    delay(2000);
    int result=getFingerprintIDez();
    if(result>=0)
    {
       // digitalWrite(openLight, HIGH);
      //  digitalWrite(closeLight, LOW);
        lcd.clear();
        lcd.print("Access Allowed");
        lcd.setCursor(0,1);
        digitalWrite(r1, HIGH);


     }
   }
smsoff();
 }
 checkKeys();
 delay(1000);
}

void checkKeys()
{
   if(digitalRead(enroll) == 0)
   {
    lcd.clear();
    lcd.print("Please Wait");
    delay(1000);
    while(digitalRead(enroll) == 0);
    Enroll();
   }

   else if(digitalRead(del) == 0)
   {
    lcd.clear();
    lcd.print("Please Wait");
    delay(1000);
    delet();
   }  
}

void Enroll()
{
   int count=0;
   lcd.clear();
   lcd.print("Enroll Finger    ");
   lcd.setCursor(0,1);
   lcd.print("Location:");
   while(1)
   {
     lcd.setCursor(9,1);
     lcd.print(count);
     if(digitalRead(up) == 0)
     {
       count++;
       if(count>4)
       count=0;
       delay(500);
     }

     else if(digitalRead(down) == 0)
     {
       count--;
       if(count<0)
       count=4;
       delay(500);
     }
     else if(digitalRead(del) == 0)
     {
          id=count;
          getFingerprintEnroll();
          return;
     }

       else if(digitalRead(enroll) == 0)
     {        
          return;
     }
 }
}

void delet()
{
   int count=0;
   lcd.clear();
   lcd.print("Delete Finger    ");
   lcd.setCursor(0,1);
   lcd.print("Location:");
   while(1)
   {
     lcd.setCursor(9,1);
     lcd.print(count);
     if(digitalRead(up) == 0)
     {
       count++;
       if(count>25)
       count=0;
       delay(500);
     }

     else if(digitalRead(down) == 0)
     {
       count--;
       if(count<0)
       count=25;
       delay(500);
     }
     else if(digitalRead(del) == 0)
     {
          id=count;
          deleteFingerprint(id);
          return;
     }

       else if(digitalRead(enroll) == 0)
     {        
          return;
     }
 }
}

uint8_t getFingerprintEnroll() 
{
  int p = -1;
  lcd.clear();
  lcd.print("finger ID:");
  lcd.print(id);
  lcd.setCursor(0,1);
  lcd.print("Place Finger");
  delay(2000);
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p)
    {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      lcd.clear();
      lcd.print("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No Finger");
      lcd.clear();
      lcd.print("No Finger");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.clear();
      lcd.print("Comm Error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      lcd.clear();
      lcd.print("Imaging Error");
      break;
    default:
      Serial.println("Unknown error");
       lcd.clear();
      lcd.print("Unknown Error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.clear();
      lcd.print("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
       lcd.clear();
       lcd.print("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.clear();
      lcd.print("Comm Error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Feature Not Found");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Feature Not Found");
      return p;
    default:
      Serial.println("Unknown error");
      lcd.clear();
      lcd.print("Unknown Error");
      return p;
  }
  
  Serial.println("Remove finger");
  lcd.clear();
  lcd.print("Remove Finger");
  delay(2000);
 
  while (p != FINGERPRINT_NOFINGER) {
    
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
   lcd.clear();
      lcd.print("Place Finger");
      lcd.setCursor(0,1);
      lcd.print("   Again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      return;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    lcd.clear();
    lcd.print("Stored!");
    delay(2000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  }
  else {
    Serial.println("Unknown error");
    return p;
  }   
}

int getFingerprintIDez()
{
  uint8_t p = finger.getImage();
  
  if (p != FINGERPRINT_OK)  
  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  
  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
  {
   lcd.clear();
   lcd.print("Finger Not Found");
   lcd.setCursor(0,1);
   lcd.print("Try Later");
   delay(2000);  
  return -1;
  }
  // found a match!
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID); 
  return finger.fingerID; 
}

uint8_t deleteFingerprint(uint8_t id) 
{
  uint8_t p = 0;  
  lcd.clear();
  lcd.print("Please wait");
  p = finger.deleteModel(id);
  if (p == FINGERPRINT_OK) 
  {
    Serial.println("Deleted!");
    lcd.clear();
    lcd.print("Figer Deleted");
    lcd.setCursor(0,1);
    lcd.print("Successfully");
    delay(1000);
  } 
  
  else 
  {
    Serial.print("Something Wrong"); 
    lcd.clear();
    lcd.print("Something Wrong");
    lcd.setCursor(0,1);
    lcd.print("Try Again Later");
    delay(2000);
    return p;
  }   
}

void smson(){
 
    Serial.println();
    Serial.print("AT+CMGS=");     // Send the SMS number. To whome message to send.
  //Serial.print("\"+918788414717\"");
   Serial.print("\"+919890552509\"");
    Serial.println();
    delay(1000);
    Serial.print("vehicle On"); // SMS-Message body
     
}
void smsoff(){
 
   
    Serial.print("AT+CMGS=");     // Send the SMS number. To whome message to send.
    //Serial.print("\"+918788414717\"");
      Serial.print("\"+919890552509\"");
    Serial.println();
    delay(1000);
    Serial.print("Alert! Someone trying to start Vehicle"); // SMS-Message body
  
}

