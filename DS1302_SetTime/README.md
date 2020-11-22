# DS1302_SetTime
To set time in DS1302 using [virtuabotixRTC](https://github.com/chrisfryer78/ArduinoRTClibrary)

1- Create virtuabotixRTC
```
// Creation of the Real Time Clock Object
// myRTC(CE, IO, CLK)
// SCLK / CLK - 6 
// IO / DATA - 7
// CE / RST - 8
virtuabotixRTC myRTC(6, 7, 8);
```

2- Change the values 
```
// Change this to update the DS1302 Time
int seconds = 40;
int minutes = 52;
int hours = 13;
int dayOfTheWeek = 7;
int dayOfTheMonth = 22;
int monthh = 11;
int yearr = 2020; 
```

3- Update 
```
myRTC.setDS1302Time(seconds, minutes, hours, dayOfTheWeek, dayOfTheMonth, monthh, yearr);
```
