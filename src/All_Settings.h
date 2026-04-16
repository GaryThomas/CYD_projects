#include <Arduino.h>
//  Use the OpenWeather library: https://github.com/Bodmer/OpenWeather

//  The weather icons and fonts are in the sketch data folder, press Ctrl+K
//  to view.

// The ESP32 board support package 2.0.0 or later must be loaded in the
// Arduino boards manager to provide LittleFS support.

//            >>>       IMPORTANT TO PREVENT CRASHES      <<<
//>>>>>>  Set LittleFS to at least 1.5Mbytes before uploading files  <<<<<<

//            >>>           DON'T FORGET THIS             <<<
//  Upload the fonts and icons to LittleFS using the "Tools" menu option.

// You can change the "User_Setup.h" file inside the OpenWeather
// to shows the data stream from the server.

//////////////////////////////
// Settings defined below

// Enable API debug messages
// #define SERIAL_MESSAGES

// Forecast includes today (true) or the next 4 days (false)
#define FORECAST_INCLUDES_TODAY true

// Wi-Fi network name and password:
String wifiSSID = "Chez Thomas";
String wifiPassword = "2625426254";

// #define TIMEZONE UK // See NTP_Time.h tab for other "Zone references", UK, usMT etc
#define TIMEZONE usMT // US Mountain Time Zone (Denver, Colorado)

// Update every 15 minutes, up to 1000 request per day are free (viz average of ~40 per hour)
const int UPDATE_INTERVAL_SECS = 15UL * 60UL; // 15 minutes

// Pins for the TFT interface are defined in the User_Config.h file inside the TFT_eSPI library

// For units use "metric" or "imperial"
String units = "imperial"; // imperial = Fahrenheit, mph, inches Hg, metric = Celsius, m/s, hPa

// Sign up for a key and read API configuration info here:
// https://openweathermap.org/, change x's to your API key
const String api_key = "a1c3465d70f1aac3095135e01d9cd6d5";

// Set the forecast longitude and latitude to at least 4 decimal places

// Fort Collins, CO
// 40.5853, -105.0844
String latitude = "40.5853";
String longitude = "-105.0844";

// For language codes see https://openweathermap.org/current#multi
const String language = "en"; // Default language = en = English

// Short day of week abbreviations used in 4 day forecast (change to your language)
const String shortDOW[8] = {"???", "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

// Change the labels to your language here:
const char sunStr[] = "Sun";
const char cloudStr[] = "Cloud";
const char humidityStr[] = "Humidity";
const String moonPhase[8] = {"New", "Waxing", "1st qtr", "Waxing", "Full", "Waning", "Last qtr", "Waning"};

// End of user settings
//////////////////////////////
