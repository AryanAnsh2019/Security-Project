#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(4, DHT11);
int mypin = 23;
void setup()
{
  Serial.begin(115200);
  dht.begin();
  pinMode(15, OUTPUT);
  //pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(mypin, INPUT);
}
void loop()
{
  bool isDetected = digitalRead(mypin);
  if (isDetected)
  {
    float t = dht.readTemperature();
     
    float h = dht.readHumidity();
    if (isnan(h) || isnan(t))
    {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    Serial.print("Humidity:");
    Serial.print(h);
    Serial.println("%");
    Serial.print("Temp.:");
    Serial.print(t);
    Serial.print("C");
    Serial.println("Prsence detected");
    digitalWrite(15, HIGH);
    //digitalWrite(23, HIGH);
    digitalWrite(25, HIGH);
    delay(100);
    digitalWrite(15, LOW);
    //digitalWrite(23, LOW);
    digitalWrite(25, LOW);
    delay(100);
  }
  delay(50);
}
