// To set the RTC in DS1302

#include <virtuabotixRTC.h>   // https://github.com/chrisfryer78/ArduinoRTClibrary

// Creation of the Real Time Clock Object
// myRTC(CE, IO, CLK)
// SCLK / CLK - 6 
// IO / DATA - 7
// CE / RST - 8
virtuabotixRTC myRTC(6, 7, 8);

// Change this to update the DS1302 Time
int seconds = 40;
int minutes = 52;
int hours = 13;
int dayOfTheWeek = 7;
int dayOfTheMonth = 22;
int monthh = 11;
int yearr = 2020; 

void setup()  {      
  Serial.begin(9600);
  Serial.print("Setting the clock in RTC to ->> ");
  Serial.print(dayOfTheMonth);
  Serial.print("/");
  Serial.print(monthh);
  Serial.print("/");
  Serial.print(yearr);
  Serial.print("  ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);

  // Set the current date, and time in the following format:
  // setDS1302Time(seconds, minutes, hours, day of the week, day of the month, month, year);
  myRTC.setDS1302Time(seconds, minutes, hours, dayOfTheWeek, dayOfTheMonth, monthh, yearr);
  myRTC.updateTime();
  
  Serial.println("Attemp to set the clock in RTC Completed.");
  Serial.println(" ");
  if (CheckClockAfterSet()){
    Serial.println("Sucess! Setting up of RTC Completed.");
  } else {
    Serial.println("Failed!");
  }
}

void loop(){
  myRTC.updateTime();  

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

  // Delay so the program doesn't print non-stop
  delay( 1000 );
} 

// setDS1302Time() is void
// The only way to check if the RTC is updated is do to manually.
boolean CheckClockAfterSet(){
  if (myRTC.seconds == seconds &&
      myRTC.minutes == minutes &&
      myRTC.hours == hours &&
      myRTC.dayofmonth == dayOfTheMonth && 
      myRTC.month == monthh &&
      myRTC.year == yearr){
          return true;
        } else {
          return false;
        }
}  
