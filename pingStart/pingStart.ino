#include <jsonlite.h>
#include <SPI.h>
#include <WiFi.h>
#include "M2XStreamClient.h"

char ssid[] = "NorthHackUp";
//char pass[] = "";
int status = WL_IDLE_STATUS;
//int status = WL_IDLE_STATUS;
//char feedId[] = "inch";
char deviceId[] = "2bc378dbef32666c1ff6cc9303607dbc"; 
char streamName[] = "inch";
char streamName2[] = "carCount";
char m2xKey[] = "e11ca108f8b1a036397b8d2920529b5f";
WiFiClient client;
M2XStreamClient m2xClient(&client, m2xKey);

const int outPin = 2; // Using FAST_IO
const int inPin = 3; // Using FAST_IO
#define PIR_MOTION_SENSOR 4

void setup() {
    Serial.begin(115200);
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    while (true);
  }
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid);
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

  pinMode(outPin, OUTPUT_FAST);
  pinMode(inPin, INPUT_FAST);
  pinsInit();
}

int carCount = 0;
void loop()
{
  

    if(isPeopleDetected())//if it detects the moving people?
    sonic();
  else{}
  
}
void printWifiStatus()
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void sonic(){

  long duration, inches, cm;

  fastDigitalWrite(outPin, LOW);
  waitMicros(2);
  fastDigitalWrite(outPin, HIGH);
  waitMicros(10);
  fastDigitalWrite(outPin, LOW);

  duration = pulseIn(inPin, HIGH); // calls fastGpioPciDigitalRead

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  if (inches<=8){
    carCount +=1;
  }
  int response = m2xClient.updateStreamValue(deviceId, streamName, inches);
  Serial.print("M2x client response code: ");
  Serial.println(response);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  Serial.print("car count: ");
  Serial.println(carCount);
  int response2 = m2xClient.updateStreamValue(deviceId, streamName2, carCount); 
  delay(100);
}
boolean isPeopleDetected()
{
  int sensorValue = digitalRead(PIR_MOTION_SENSOR);
  if(sensorValue == HIGH)//if the sensor value is HIGH?
  {
    return true;//yes,return true
  }
  else
  {
    return false;//no,return false
  }
}
void waitMicros(int val)
{
  unsigned long a = micros();
  unsigned long b = micros();
  while((b-a) < val)
  {
    b = micros();
    if(a>b)
    {
      break;
    }
  }
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void pinsInit()
{
  pinMode(PIR_MOTION_SENSOR, INPUT);
}


