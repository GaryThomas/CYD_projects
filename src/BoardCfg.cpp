// Copyright 2015-2021 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "BoardCfg.h"
#include "UUID7.h"
#include <Preferences.h>

#include <nvs.h>
#include <nvs_flash.h>

// const char *nvs_errors[] = {"OTHER",         "NOT_INITIALIZED",  "NOT_FOUND",    "TYPE_MISMATCH",
//                             "READ_ONLY",     "NOT_ENOUGH_SPACE", "INVALID_NAME", "INVALID_HANDLE",
//                             "REMOVE_FAILED", "KEY_TOO_LONG",     "PAGE_FULL",    "INVALID_STATE",
//                             "INVALID_LENGTH"};
// #define nvs_error(e) (((e) > ESP_ERR_NVS_BASE) ? nvs_errors[(e) & ~(ESP_ERR_NVS_BASE)] : nvs_errors[0])

BoardCfg::BoardCfg() : _handle(0), _started(false), _readOnly(false) {}

BoardCfg::~BoardCfg() { end(); }

bool BoardCfg::begin() {
    UUID7 uuid;
    Preferences prefs;
    if (_started) {
        return false;
    }
    valid = false;
    _readOnly = false;
    // Look for existing config in NVS
    prefs.begin("board_cfg", false);
    _loaded = false;
    if (prefs.isKey("guid") && prefs.getBool("_valid", true)) {
        String guidStr = prefs.getString("guid", "");
        if (guidStr.length() == 36) {
            guidStr.toCharArray(guid, sizeof(guid));
            prefs.end();
            _started = true;
            _loaded = true;
            prefs.end();
            valid = true;
            return true;
        } else {
            Serial.println("Invalid GUID found in NVS, generating a new one");
        }
    } else {
        Serial.println("No existing GUID found in NVS, generating a new one");
    }
    prefs.end();
    // Generate a new configuration and save it to NVS
    _started = true;
    if (uuid.generate()) {
        uuid.toString(guid, sizeof(guid));
    } else {
        Serial.println("Failed to generate UUID for BoardCfg");
        guid[0] = '\0';
        return false;
    }
    update();
    return true;
}

void BoardCfg::end() {
    if (!_started) {
        return;
    }
    nvs_close(_handle);
    _started = false;
}

void BoardCfg::dump() {
    if (!_started) {
        return;
    }
    Serial.println("BoardCfg Dump:");
    Serial.println("GUID: " + String(guid));}

void BoardCfg::reset() {
    if (!_started) {
        return;
    }
    nvs_erase_all(_handle);
    nvs_commit(_handle);
    Serial.println("BoardCfg reset to defaults");
}

void BoardCfg::update() {
    if (!_started) {
        return;
    }
    if (_readOnly) {
        Serial.println("BoardCfg is read-only, cannot update");
        return;
    }
    Preferences prefs;
    prefs.begin("board_cfg", false);
    prefs.putBool("_valid", true); // Add a version key to detect valid config
    prefs.putString("guid", guid);
    prefs.end();
    Serial.println("BoardCfg updated in NVS");
}
