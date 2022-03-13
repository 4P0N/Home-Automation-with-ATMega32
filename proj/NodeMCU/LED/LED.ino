/*#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#define TRIGGERPIN D1

#define ECHOPIN D2

// You should get Auth Token in the Blynk App. // Go to the Project Settings (nut icon). char auth[] = "Your auth token";

// Your WiFi credentials. // Set password to "" for open networks.

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "TJyL-ePbQL8OKpX3BvDobPd2cxN8HnVy";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SWH-110";
char pass[] = "15161617"; 

WidgetLCD lcd(V1);
double distance;
double duration;

void setup() {

// Debug console

Serial.begin(9600);

pinMode(TRIGGERPIN, OUTPUT);

pinMode(ECHOPIN, INPUT);

Blynk.begin(auth, ssid, pass);

// You can also specify server: //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442); //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

lcd.clear(); //Use it to clear the LCD Widget

lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print") // Please use timed events when LCD printintg in void loop to avoid sending too many commands // It will cause a FLOOD Error, and connection will be dropped }
}

void loop() {

lcd.clear();

lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print") long duration, distance;

digitalWrite(TRIGGERPIN, LOW);

delayMicroseconds(3);

digitalWrite(TRIGGERPIN, HIGH);

delayMicroseconds(12);

digitalWrite(TRIGGERPIN, LOW);

duration = pulseIn(ECHOPIN, HIGH);

distance = (duration/2) / 29.1;

Serial.print(distance);

Serial.println("Cm");

lcd.print(7, 1, distance);

Blynk.run();

delay(3500);

}
*/










#define BLYNK_PRINT Serial
 
#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#define PIN_UPTIME V5

// You should get Auth Token in the Blynk App.

// Go to the Project Settings (nut icon).


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "TJyL-ePbQL8OKpX3BvDobPd2cxN8HnVy";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Beast";
char pass[] = "asdfghjkl"; 

int light = D0; // Define LED as an Integer (whole numbers) and pin D8 on Wemos D1 Mini Pro
int lightAuto = D1;

int fan = D2;
int fanAuto = D3;
int sensorData;

// This function tells Arduino what to do if there is a Widget
// which is requesting data for Virtual Pin (5)
BLYNK_READ(PIN_UPTIME)
{
  // This command writes Arduino's uptime in seconds to Virtual Pin (5)
  sensorData = analogRead(A0);
  sensorData /= 4;
  Blynk.virtualWrite(PIN_UPTIME, sensorData);
}


void setup()
{
  Serial.begin(9600);
  // Debug console
  //Serial.begin(115200);
  pinMode(light, OUTPUT);
  pinMode(lightAuto, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(fanAuto, OUTPUT);
  Blynk.begin(auth, ssid, pass);

}

void loop()
{
  Blynk.run();
}

// This function will be called every time button Widget
// in Blynk app writes values to the Virtual Pin V3
BLYNK_WRITE(V1) {
 int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
 if (pinValue == 1) {
    digitalWrite(light, HIGH); // Turn LED on.
 } else {
    digitalWrite(light, LOW); // Turn LED off.
 }
}

BLYNK_WRITE(V2) {
 int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
 if (pinValue == 1) {
    digitalWrite(lightAuto, HIGH); // Turn LED on.
 } else {
    digitalWrite(lightAuto, LOW); // Turn LED off.
 }
}

BLYNK_WRITE(V3) {
 int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
 if (pinValue == 1) {
    digitalWrite(fan, HIGH); // Turn LED on.
 } else {
    digitalWrite(fan, LOW); // Turn LED off.
 }
}

BLYNK_WRITE(V4) {
 int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
 if (pinValue == 1) {
    digitalWrite(fanAuto, HIGH); // Turn LED on.
 } else {
    digitalWrite(fanAuto, LOW); // Turn LED off.
 }
}
