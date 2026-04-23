// Bare bones skeleton - nothing more than a serial port
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    
    Serial.println("\n\nThe time has come, the walrus said, to talk of many things...");
}

void loop() {}
