#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"

Adafruit_LiquidCrystal lcd(0);
int sensorPin = A0;//joystick dir 1
int sensorPin1 = A1; //joystick dir 2
int sensorPin2 = A2; //output one of radiation sensor=
int sensorPin3 = A3; //output two of rad sensor
int sensorValue = 0;
int sensorValue2 = 0;
int sensorValue1 = 0;
int sensorValue3 = 0;
const int buttonPin = 7;     // the number of the pushbutton pin
int buttonState = 1;
int currentmenu = 6; //between 0-8
int dicenum = 1;
bool diechange = false;
bool Ranonce = true;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 400;  //the value is a number of milliseconds

void setup() {
  // set up the LCD's number of rows and columns:
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  Serial.begin(9600);
  // Print a message to the LCD.
  pinMode(buttonPin, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  lcd.print(dicenum);
  lcd.setCursor(8, 0);
  lcd.print(dicenum);
  lcd.print("d20");
  startMillis = millis();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(10, 0);
  sensorValue = analogRead(sensorPin);
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  currentMillis = millis();  //get the current time
  unsigned long seed = seedOut(31);
  // now show sequence
  randomSeed(seed);
  lcd.clear();
  lcd.setCursor(8, 0);
  int x;
  //random requires exact lower and one higher than upper bound
  for (x = 0; x < 10000; x++) {
    long randNumber = random(1, 21);
    lcd.print(x);
    lcd.clear();
    lcd.setCursor(8, 0);
    Serial.println(randNumber);
    delay(50);
  }
}

void loop() {
  lcd.print("Beep Beep");

  delay(10000);
}

void updatemenu() {
  lcd.clear();
  lcd.setCursor(8, 0);
  switch (currentmenu) {
    case 0:
      lcd.print(dicenum);
      lcd.print("d2");
      break;
    case 1:
      lcd.print(dicenum);
      lcd.print("d4");
      break;
    case 2:
      lcd.print(dicenum);
      lcd.print("d6");
      break;
    case 3:
      lcd.print(dicenum);
      lcd.print("d8");
      break;
    case 4:
      lcd.print(dicenum);
      lcd.print("d10");
      break;
    case 5:
      lcd.print(dicenum);
      lcd.print("d12");
      break;
    case 6:
      lcd.print(dicenum);
      lcd.print("d20");
      break;
    case 7:
      lcd.print(dicenum);
      lcd.print("d100");
      break;
    case 8:
      lcd.print(dicenum);
      lcd.print("d10000");
      break;
    default:
      lcd.print(dicenum);
      lcd.print("d20");
  }
}


void rolldice() {
  int randoana = analogRead(sensorPin2) + analogRead(6) + analogRead(3);
  //Serial.print(analogRead(sensorPin2));
  //Serial.print(" + ");
  //Serial.print(analogRead(6));
  //Serial.print(" + ");
  //Serial.print(analogRead(3));
  //Serial.print(" = ");
  //Serial.print(randoana);
  //Serial.println();
  //randomSeed(randoana);
  unsigned long seed = seedOut(31);
  // now show sequence
  randomSeed(seed);

  lcd.clear();
  updatemenu();
  lcd.setCursor(8, 1);
  long total = 0;
  int x;
  //random requires exact lower and one higher than upper bound
  switch (currentmenu) {
    case 0:
      for (x = 0; x < dicenum; x++) {
        long randNumber = random(1, 3);
        total = total + randNumber;
      }
      lcd.print(total);
      break;
    case 1:
      for (x = 0; x < dicenum; x++) {
        long randNumber = random(1, 5);
        total = total + randNumber;
      }
      lcd.print(total);
      break;
    case 2:
      for (x = 0; x < dicenum; x++) {
        long randNumber = random(1, 7);
        total = total + randNumber;
      }
      lcd.print(total);
      break;
    case 3:
      for (x = 0; x < dicenum; x++) {
        long randNumber = random(1, 9);
        total = total + randNumber;
      }
      lcd.print(total);
      break;
    case 4:
      for (x = 0; x < dicenum; x++) {
        long randNumber = random(1, 11);
        total = total + randNumber;
      }
      lcd.print(total);
      break;
    case 5:
      for (x = 0; x < dicenum; x++) {
        long randNumber = random(1, 13);
        total = total + randNumber;
      }
      lcd.print(total);
      break;
    case 6:
      //a d20 is special, with crit fails and crit success, and with advantage and disadvantage
      if (dicenum == 2) {
        lcd.print(random(1, 21));
        lcd.print("  ");
        lcd.print(random(1, 21));
      }
      else {
        for (x = 0; x < dicenum; x++) {
          long randNumber = random(1, 21);
          total = total + randNumber;
          lcd.print(total);
        }
      }

      if (dicenum == 1 && total == 20) {
        lcd.print(" WIN!");
      }
      if (dicenum == 1 && total == 1) {
        lcd.print(" FAIL!");
      }
      break;
    case 7:
      for (x = 0; x < dicenum; x++) {
        long randNumber = random(1, 101);
        total = total + randNumber;
      }
      lcd.print(total);
      break;
    case 8:
      for (x = 0; x < dicenum; x++) {
        long randNumber = random(1, 10001);
        total = total + randNumber;
      }
      lcd.print(total);
      break;
    default:
      lcd.print("Uh Oh");
  }

  lcd.setCursor(8, 0);


}


unsigned int bitOut(void)
{
  static unsigned long firstTime = 1, prev = 0;
  unsigned long bit1 = 0, bit0 = 0, x = 0, port = 0, limit = 99;
  if (firstTime)
  {
    firstTime = 0;
    prev = analogRead(2);
  }
  while (limit--)
  {
    x = analogRead(2);
    bit1 = (prev != x ? 1 : 0);
    prev = x;
    x = analogRead(2);
    bit0 = (prev != x ? 1 : 0);
    prev = x;
    if (bit1 != bit0)
      break;
  }
  return bit1;
}

unsigned long seedOut(unsigned int noOfBits)
{
  // return value with 'noOfBits' random bits set
  unsigned long seed = 0;
  for (int i = 0; i < noOfBits; ++i)
    seed = (seed << 1) | bitOut();
  return seed;
}

