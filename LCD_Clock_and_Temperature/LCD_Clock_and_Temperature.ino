// Component used:
// - Arduino Nano
// - DHT11
// - DS1302
// - i2c LCD
// - potentiometer 10k optional for lcd brightness

#include <Wire.h> //
#include <LiquidCrystal_I2C.h> 
#include <virtuabotixRTC.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11

// For katakana
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

// Creation of the Real Time Clock Object
// myRTC(CE, IO, CLK)
// SCLK / CLK - D6
// IO / DATA - D7 (1K resistor in between)
// CE / RST - D8
virtuabotixRTC myRTC(6, 7, 8);

// set the LCD address to 0x27 for a 16 chars and 2 line display
// SCL is connected to A4 
// SDA is connected to A5
// Potentiometer 10k is connected at the back of i2c to control brightness
LiquidCrystal_I2C lcd(0x27, 20, 4);

// DHT11 is connected to D2
DHT dht(DHTPIN, DHTTYPE);
float humidity, temp, heatIndex;

void setup()
{
  Serial.begin(9600);

  // initialize DHT and lcd
  dht.begin();
  lcd.init(); 
  lcd.backlight();
  
  printSplashLCD();
  delay(5000);
  lcd.clear();
}

void loop()
{
  myRTC.updateTime();
  humidity = dht.readHumidity();
  temp = dht.readTemperature();
  heatIndex = dht.computeHeatIndex(temp, humidity, false); // Compute heat index in Celsius
  SerialPrintLoop();

  lcd.setCursor(0, 0);

  // show 0 before the value. 01 02
  if (myRTC.dayofmonth < 10) {
    lcd.print("0");
    lcd.print(myRTC.dayofmonth);
  } else {
    lcd.print(myRTC.dayofmonth);
  }
  lcd.print("-");

  // get Month in letters
  lcd.print(getMonthString(myRTC.month));
  lcd.print("  ");

  if (myRTC.hours < 10) { // Hours, show 0 before the value. 01 02
    lcd.print("0");
    lcd.print(myRTC.hours);
  } else if (myRTC.hours == 0) {
    lcd.print("00");
  } else {
    lcd.print(myRTC.hours);
  }

  lcd.print(":");
  if (myRTC.minutes < 10) { // Minutes, show 0 before the value. 01 02
    lcd.print("0");
    lcd.print(myRTC.minutes);
  } else if (myRTC.minutes == 0) {
    lcd.print("00");
  } else {
    lcd.print(myRTC.minutes);
  }
  lcd.print(":");
  
  if (myRTC.seconds  < 10) {  // Seconds, show 0 before the value. 01 02
    lcd.print("0");
    lcd.print(myRTC.seconds);
  } else if ( myRTC.seconds == 0 ) {
    lcd.print("00");
  } else {
    lcd.print(myRTC.seconds);
  }

  lcd.setCursor(0, 1);
  printToggle();

  // Delay so the program doesn't print non-stop                                                           //|
  delay( 1000);
}

void printToggle() {
  lcd.setCursor(0, 1);
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temp)) {
    lcd.print("DHT sensor error!");
    return;
  }

  // Change every 10 sec ((sec/10) % 10) % 2
  if ( (int)((myRTC.seconds / 10) % 10) == 3) { // at 30 sec
    // Print Temperature
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("% ");
  } else if ( (int)(((myRTC.seconds / 10) % 10) % 2) ) { // at even 20 , 40
    lcd.print("RealFeel:");
    lcd.print(heatIndex);
    lcd.print((char)223);
    lcd.print("C");
  } else { // 0 , 10, 50,
    lcd.print("RealTemp:");
    lcd.print(temp);
    lcd.print((char)223);
    lcd.print("C   ");
  }
}

String getMonthString(int monthNumber) {
  switch (monthNumber) {
    case 1:
      return "Jan";
      break;
    case 2:
      return "Feb";
      break;
    case 3:
      return "Mar";
      break;
    case 4:
      return "Apr";
      break;
    case 5:
      return "May";
      break;
    case 6:
      return "Jun";
      break;
    case 7:
      return "Jul";
      break;
    case 8:
      return "Aug";
      break;
    case 9:
      return "Sep";
      break;
    case 10:
      return "Oct";
      break;
    case 11:
      return "Nov";
      break;
    case 12:
      return "Dec";
      break;
    default:
      return (String)monthNumber;
  }
}

void printSplashLCD() {
  // Japanese Bytes
  // 160 175 -> A0 B0
  // 176 191 -> B0 C0
  // 192 207 -> C0 D0
  // 208 223 -> D0 E0

  lcd.setCursor(0, 0);
  lcd.print("  NICO NICO NI  ");
  lcd.setCursor(0, 1);
  lcd.print(" ");
  lcd.printByte(198);
  lcd.printByte(186);
  lcd.printByte(198);
  lcd.printByte(186);
  lcd.printByte(198);
  lcd.print(" ");
  lcd.printByte(198);
  lcd.printByte(186);
  lcd.printByte(198);
  lcd.printByte(186);
  lcd.printByte(198);
  lcd.printByte(186);
  lcd.print(" ");
  lcd.printByte(198);
}

void SerialPrintLoop() {
  // Start printing elements as individuals
  Serial.print("Current Date / Time: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temp);
  Serial.print(F("°C "));
  Serial.print(F(" Heat index: "));
  Serial.print(heatIndex);
  Serial.println(F("°C "));
}
