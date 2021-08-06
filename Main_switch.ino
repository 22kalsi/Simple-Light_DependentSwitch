
//Simple_NightOrDay_Sensor
//With the help of arduino nano and the ldr.

#include <LiquidCrystal.h>
#include "DHT.h"

int RELAY =  11;  // for first relay 
int RELAY1 =  10; // for second relay with different turn on instance
int ON =  A1;  // Green Led
int CALIBRATE = A2; // potentiometer for changing on/off timming.
int LDR = A0;  // input 
int OFF = A0;  // Red Led
//int LM35 =  9;  // temprature sensor
#define DHTPIN 9  // temprature sensor

byte termometru[8] = // special character
{
  B00100,
  B01010,
  B01010,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110
};

const int numReadings = 10;

#define DHTTYPE DHT11
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int BL = 12;           // the pin that the LED is attached to

LiquidCrystal lcd(7, 6, 5, 4, 3, 2 );

String readString;
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
  //analogReference(INTERNAL);

  lcd.begin(16, 2);
  pinMode(BL, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(LDR, INPUT);
  // pinMode(LM35, INPUT);

  lcd.clear();
  lcd.createChar(1, termometru);

  // -- do some delay: some time I've got broken visualization
  delay(100);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  lcd.setCursor(0, 0);
  lcd.print("Initializing....");
  lcd.setCursor(0, 1);
  delay(500);
  lcd.print("Sensors.     -  ");
  lcd.setCursor(0, 0);
  lcd.print("Initializing....");
  lcd.setCursor(0, 1);
  delay(500);
  lcd.print("Sensors.     \  ");
            lcd.setCursor(0, 0);
            lcd.print("Initializing....");
            lcd.setCursor(0, 1);
            delay(500);
            lcd.print("Sensors.     |  ");
            lcd.setCursor(0, 0);
            lcd.print("Initializing....");
            lcd.setCursor(0, 1);
            delay(500);
            lcd.print("Sensors.     /  ");
            lcd.setCursor(0, 0);
            lcd.print("Initializing....");
            lcd.setCursor(0, 1);
            delay(500);
            lcd.print("Sensors.     -  ");
            lcd.setCursor(0, 0);
            lcd.print("Initializing....");
            lcd.setCursor(0, 1);
            delay(500);
            lcd.print("  Backlight ON  ");
            lcd.setCursor(0, 0);
            lcd.print("Initializing....");
            analogWrite(BL, 150);
            lcd.setCursor(0, 1);
            delay(500);
            lcd.print("Sensors.     \  ");
            lcd.setCursor(0, 0);
            lcd.print("Initializing....");
            lcd.setCursor(0, 1);
            delay(500);
            lcd.print("Sensors.     |  ");
            lcd.setCursor(0, 0);
            lcd.print("Initializing....");
            lcd.setCursor(0, 1);
            delay(500);
            lcd.print("Sensors.     /  ");
            lcd.setCursor(0, 0);
            lcd.print("Initializing....");
            lcd.setCursor(0, 1);
            delay(500);
            //lcd.print("AT\r");
            lcd.clear();
            lcd.print("    ALL SET!    ");
            delay(1000);
            lcd.clear();

          }

            void loop() {

            // float temperature = ((475 * average1 ) / 1024.0);
            //Filter for LM35--------------------------------------------
            total = total - readings[readIndex];
            // read from the sensor:
            readings[readIndex] = analogRead(LDR);
            // add the reading to the total:
            total = total + readings[readIndex];
            // advance to the next position in the array:
            readIndex = readIndex + 1;

            // if we're at the end of the array...
            if (readIndex >= numReadings) {
            // ...wrap around to the beginning:
            readIndex = 0;
          }
            // calculate the average:
            average = total / numReadings;
            //-----------------------------------------------

            //---------------------------------------------------------
            lcd.setCursor(0, 0);
            lcd.print("        ");
            lcd.setCursor(0, 0);
            lcd.print("LDR-");
            lcd.print(average);
            if (average >= 80) {
            lcd.setCursor(0, 1);
            lcd.print("        ");
            lcd.setCursor(0, 1);
            lcd.print("L1- OFF");
            digitalWrite (RELAY1 , LOW);
          }
          if (average <= 20) {
            lcd.setCursor(0, 1);
            lcd.print("        ");
            lcd.setCursor(0, 1);
            lcd.print("L1- ON");
            digitalWrite (RELAY1 , HIGH);
          }
          if (average <= 60) {
          lcd.setCursor(9, 1);
            lcd.print("       ");
            lcd.setCursor(9, 1);
            lcd.print("L2- ON");
            digitalWrite (RELAY , HIGH);
          }
          if (average >= 80) {
            lcd.setCursor(9, 1);
            lcd.print("        ");
            lcd.setCursor(9, 1);
            lcd.print("L2- OFF");
            
            digitalWrite (RELAY , LOW);
          }
            lcd.setCursor(0, 0);
            lcd.print("        ");
            lcd.setCursor(0, 0);
            lcd.print("LDR-");
            lcd.print(average);
            



            //Filter for LM35--------------------------------------------
            float h = dht.readHumidity();
            // Read temperature as Celsius (the default)
            float t = dht.readTemperature();
            // Read temperature as Fahrenheit (isFahrenheit = true)
            float f = dht.readTemperature(true);

            // Check if any reads failed and exit early (to try again).
            if (isnan(h) || isnan(t) || isnan(f)) {
            Serial.println("Failed to read from DHT sensor!");
            return;
            
          }

            // Compute heat index in Fahrenheit (the default)
            float hif = dht.computeHeatIndex(f, h);
            // Compute heat index in Celsius (isFahreheit = false)
            float hic = dht.computeHeatIndex(t, h, false);

            Serial.print("Humidity: ");
            Serial.print(h);
            Serial.print(" %\t");
            Serial.print("Temperature: ");
            Serial.print(t);
            Serial.print(" *C ");
            Serial.print(f);
            Serial.print(" *F\t");
            Serial.print("Heat index: ");
            Serial.print(hic);
            Serial.print(" *C ");
            Serial.print(hif);
            Serial.println(" *F");
            lcd.setCursor(9, 0);
            lcd.print("       ");
            lcd.setCursor(9, 0);
            lcd.write(1);
            lcd.setCursor(11, 0);
            lcd.print(t, 0); // print temperature
            lcd.print((char)223);
            lcd.print("C");
           
          }
            
