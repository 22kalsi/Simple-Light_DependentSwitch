#include <LiquidCrystal.h>
#include <LcdBarGraph.h>
#include <NewPing.h>


#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 125 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


byte lcdNumCols = 16; // -- number of columns in the LCD

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // -- creating LCD instance
LcdBarGraph lbg(&lcd, lcdNumCols);  // -- creating
const int numReadings = 100;
const int numReadingst = 50;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int readingst[numReadings];      // the readings from the analog input
int readIndext = 0;              // the index of the current reading
int totalt = 0;                  // the running total
int averaget = 0;

void setup() {
  //analogReference(INTERNAL);
  Serial.begin(9600);// -- initializing the LCD
  lcd.begin(2, lcdNumCols);
  lcd.clear();
  pinMode(8, OUTPUT);
  delay(100); // -- do some delay: some time I've got broken visualization

  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;
  for (int thisReadingt = 0; thisReadingt < numReadingst; thisReadingt++)
    readingst[thisReadingt] = 0;
}

void loop()
{

  delay(10);
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = (sonar.ping_cm());
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings)
    // ...wrap around to the beginning:
    readIndex = 0;

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits

  delay(50);
  //Serial.println(average);
  delay(50);
  lbg.drawValue (117 - (average - 4), 117);
  delay(100);

  totalt = totalt - readingst[readIndext];
  // read from the sensor:
  readingst[readIndext] = analogRead(A2);
  // add the reading to the total:
  totalt = totalt + readingst[readIndext];
  // advance to the next position in the array:
  readIndext = readIndext + 1;

  // if we're at the end of the array...
  if (readIndext >= numReadingst)
    // ...wrap around to the beginning:
    readIndext = 0;

  // calculate the average:
  averaget = totalt / numReadingst;
  // send it to the computer as ASCII digits


  float temperature = (500 * averaget ) / 1024.0;  //This is the simplest way without any library we can mesure temprature using lm35.
  lcd.setCursor(0, 1);
  lcd.print("F-");
  lcd.setCursor(2, 1);
  lcd.print("     ");
  lcd.setCursor(2, 1);
  lcd.print(117 - average);
  lcd.print("CM");
  lcd.setCursor(11, 1);
  lcd.print("     ");
  lcd.setCursor(8, 1);
  lcd.print("S-");
  lcd.setCursor(10, 1);
  lcd.print(sonar.ping_cm());
  lcd.print("CM");
  lcd.setCursor(15, 1);
  lcd.print("     ");
  lcd.setCursor(16, 0);
  lcd.print("L-");
  lcd.setCursor(18, 0);
  lcd.print((50 * (117 - average)));
  lcd.print("L");
  lcd.setCursor(24, 0);
  lcd.print("         ");
  lcd.setCursor(24, 0);
  lcd.print("T-");
  lcd.print(temperature, 1); // print temperature
  //lcd.setCursor(29, 0);
  lcd.print((char)223);
  lcd.print("C");
  Serial.println(analogRead(0));
  Serial.println(averaget);

}

