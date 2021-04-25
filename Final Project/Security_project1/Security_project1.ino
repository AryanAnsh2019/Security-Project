#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include "IFTTTWebhook.h"
#define WIFI_SSID "dnmgiot2017"
#define WIFI_PASSWORD "dnmgiot2017"
#define IFTTT_API_KEY "dXcKO63ZXO7vFJbcjr5Rwq"
#define IFTTT_EVENT_NAME "intruder"
LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4;
const byte COLS = 4;
int inputpin = 32, pinstate = 0;
boolean check = true, last;
int i = 0, ind, j;
char code[4] = {}, secret[4] = {'1', '7', '5', '3'};
char keys[ROWS][COLS] =
{
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'},
};
byte rowPins[ROWS] = {4, 5, 18, 19};
byte colPins[COLS] = {13, 12, 27, 26};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  pinMode(15, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(inputpin, INPUT);
//  WiFi.mode(WIFI_STA);
//  if (WiFi.status() != WL_CONNECTED)
//  {
//    Serial.print("Attempting to connect to SSID: ");
//    Serial.println(WIFI_SSID);
//    while (WiFi.status() != WL_CONNECTED)
//    {
//      WiFi.begin("dnmgiot2018", "dnmgio2018");
//      Serial.print(".");
//      delay(5000);
//    }
//    Serial.println("\nConnected.");
//  }
}
void loop()
{
  pinstate = digitalRead(inputpin);
  Serial.print(pinstate);
  if (pinstate == 1)
  {
    Serial.print("a");
    lcd.setCursor(0, 0);
    lcd.print("Enter password");
    char key = keypad.getKey();
    if (key)
    {
      Serial.print("b");
      code[i] = key;
      i++;
      if (i > 3)
      {
        char b = keypad.getKey();
        i = 0;
        Serial.print("c");
        for (ind = 0; ind < 4; ind++)
        {
          Serial.print("d");
          if (secret[i] != code[i] )
          {
              check = false;
              break;
          }
          else
          {
            
          }
        }
        if (check == true)
        {
          IFTTTWebhook wh(IFTTT_API_KEY, IFTTT_EVENT_NAME);
          wh.trigger();
          Serial.print("f");
          lcd.setCursor(0, 0);
          lcd.print("Wrong Password!");
          while (check == false)
          {
            Serial.print("g");
            digitalWrite(15, HIGH);
            digitalWrite(25, HIGH);
            delay(50);
            digitalWrite(15, LOW);
            digitalWrite(25, LOW);
            delay(50);
          }
        }
        else
        {
          Serial.print("h");
          lcd.setCursor(0, 0);
          lcd.print("Acess Granted");
          while (check == true)
          {
            Serial.print("i");
            digitalWrite(23, HIGH);
            delay(50);
            digitalWrite(23, LOW);
            delay(50);
          }
        }
      }
    }
  }
}
