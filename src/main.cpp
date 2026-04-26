// Bare bones skeleton - nothing more than a serial port
#include <Arduino.h>
#include "BoardCfg.h"

BoardCfg boardCfg;

void setup() {
    Serial.begin(115200);

    sleep(5);
    Serial.println("\n\nThe time has come, the walrus said, to talk of many things...");

    boardCfg.begin(); // Generate new config if not found, or load existing config if valid
    boardCfg.dump("Base configuration:");
    // Update the device name and save it to NVS if not set
    boardCfg.end(); // Clean up resources
    sleep(5);

    Serial.print("Reset? (y/n): ");
    while (!Serial.available()) {
        delay(100);
    }
    char response = Serial.read();
    if (response == 'y' || response == 'Y') {
        boardCfg.begin(); // Start again to show reset functionality
        boardCfg.reset(); // Reset config to defaults (generates new GUID)
        boardCfg.dump("Reset configuration:");
        boardCfg.end();
    }
    ESP.restart(); // Restart to show that reset config is retained across resets
}

void loop() {}
