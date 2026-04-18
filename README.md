Modified version of A Weather application for the CYD (Cheap Yellow Display).

Adapted from the Medium article [Create an Internet Weather Station with 3 days Forecast on an ESP32 Cheap Yellow Display (“CYD”)](https://medium.com/@androidcrypto/create-an-internet-weather-station-with-3-days-forecast-on-an-esp32-cheap-yellow-display-cyd-15eb5c353b1d) by AndroidCrypto, with the following changes:
- Set up platformio build environment for the CYD, including LittleFS support
- Updated to use the latest TFT_eSPI library and its LittleFS support, removing the need for SPIFFS
- Added SD card support for location settings and user supplied splash screen

Note: the URL for the repo in the Medium article is incorrect, check the code for the one I found.

