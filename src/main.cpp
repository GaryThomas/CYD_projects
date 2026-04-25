// Bare bones skeleton - nothing more than a serial port
#include <Arduino.h>
#include "BoardCfg.h"

BoardCfg boardCfg;

void setup() {
    Serial.begin(115200);
    
    Serial.println("\n\nThe time has come, the walrus said, to talk of many things...");

    boardCfg.begin(); // Generate new config if not found, or load existing config if valid
    Serial.println("BoardCfg valid: " + String(boardCfg.valid));
    Serial.println("BoardCfg GUID: " + String(boardCfg.guid));
    boardCfg.dump();
}

void loop() {}
