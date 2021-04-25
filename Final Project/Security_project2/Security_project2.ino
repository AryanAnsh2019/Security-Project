#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "IFTTTWebhook.h"
#define WIFI_SSID "Ktayal"
#define  WIFI_PASSWORD "1357924680"
#define IFTTT_API_KEY "dXcKO63ZXO7vFJbcjr5Rwq"
#define IFTTT_EVENT_NAME "intruder"
#define timeSeconds 10
LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4;
const byte COLS = 4;
long now=millis(), lastTrigger=0;
boolean startTimer=false;
int inputpin = 23, wait = 0;
boolean check;
int buzzer=15;
int i = 0, ind;
char code[4] = {}, password[4] = {'1', '7', '5', '3'};
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {13, 12, 27, 26};
byte colPins[COLS] = {2, 5, 18, 19};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void detectsMovement()
{
  Serial.println("Motion detected");
  digitalWrite(buzzer, HIGH);
  startTimer=true;
  lastTrigger=millis();
}
void setup()
{
  Serial.begin(9600);
  //  lcd.init();
  //  lcd.backlight();
  //  lcd.setCursor(0, 0);
  pinMode(buzzer, OUTPUT);
  //pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(inputpin, INPUT_PULLUP);
  WiFi.mode(WIFI_STA);
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin("Ktayal", "1357924680");
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  attachInterrupt(digitalPinToInterrupt(inputpin), detectsMovement, RISING);
}
//char enteredpassword[4] = {};
//int currentindex = 0;
//int keyPadState()
//{
//  char key = keypad.getKey();
//  boolean check = false;
//  int keyPadState = 0; //0 In progress, 1=Validate, 2=invalidated, 3 firstkeyentered, 4 nothingentered
//  if (key)
//  {
//    lcd.print(key);
//    digitalWrite(15, HIGH);
//    delay(50);
//    digitalWrite(15, LOW);
//    delay(50);
//    enteredpassword[currentindex] = key;
//    currentindex++;
//    lcd.setCursor(currentindex - 1, 1);
//    Serial.print(key);
//    delay(200);
//    lcd.setCursor(currentindex - 1, 1);
//    lcd.print("*");
//    if (currentindex > 3)
//    {
//      check = true;
//      for (currentindex = 0; currentindex < 4; currentindex++)
//      {
//        if (password[currentindex] != enteredpassword[currentindex])
//        {
//          check = false;
//          currentindex = 0;
//          break;
//        }
//      }
//      if (check == false)
//      {
//        keyPadState = 2;
//        return keyPadState;
//      }
//      else
//      {
//        keyPadState = 1;
//        return keyPadState;
//      }
//    }
//  }
//  else
//  {
//    wait = millis();
//    Serial.println(wait);
//    delay(200);
//    if (wait >= 200000)
//    {
//      keyPadState = 4;
//      return keyPadState;
//    }
//  }
//}
void loop()
{
  now = millis();
  if(startTimer && (now - lastTrigger > (timeSeconds*1000)))
  {
    Serial.println("Motion stopped...");
    digitalWrite(buzzer, LOW);
    startTimer = false;
//  int pinstate = digitalRead(inputpin);
//  if (pinstate == 1)
//  {
//    Serial.print("Presence detected");
//    lcd.setCursor(0, 0);
//    Serial.print("Enter password : ");
//    int isCodeCorrect;
//    Serial.println("a");
//    isCodeCorrect = keyPadState();
//    if (isCodeCorrect == 0)
//    {
//    }
//    if (isCodeCorrect == 1 || isCodeCorrect == 5)
//    {
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      Serial.print("Acess Granted");
//      while (isCodeCorrect == 1 || isCodeCorrect == 5)
//      {
//        digitalWrite(25, HIGH);
//        delay(50);
//        digitalWrite(25, LOW);
//        delay(50);
//      }
//      Serial.println("Acess granted");
//    }
//    if (isCodeCorrect == 2)
//    {
//      IFTTTWebhook wh(IFTTT_API_KEY, IFTTT_EVENT_NAME);
//      wh.trigger();
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      lcd.print("Wrong Password!");
//      while (isCodeCorrect == 2)
//      {
//        digitalWrite(15, HIGH);
//        digitalWrite(23, HIGH);
//        delay(50);
//        digitalWrite(15, LOW);
//        digitalWrite(23, LOW);
//        delay(50);
//        Serial.println("Acess denied");
//      }
//    }
//    if (isCodeCorrect == 3)
//    {
//    }
//    if (isCodeCorrect == 4)
//    {
//      //IFTTTWebhook wh(IFTTT_API_KEY, IFTTT_EVENT_NAME);
//      //wh.trigger();
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      lcd.print("No Password!");
//      while (isCodeCorrect == 4)
//      {
//        digitalWrite(15, HIGH);
//        digitalWrite(23, HIGH);
//        delay(50);
//        digitalWrite(15, LOW);
//        digitalWrite(23, LOW);
//        delay(50);
//        Serial.println("Acess denied");
//      }
//    }
  }
}
