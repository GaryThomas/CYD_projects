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

#include <nvs.h>
#include <nvs_flash.h>

const char *nvs_errors[] = {"OTHER",         "NOT_INITIALIZED",  "NOT_FOUND",    "TYPE_MISMATCH",
                            "READ_ONLY",     "NOT_ENOUGH_SPACE", "INVALID_NAME", "INVALID_HANDLE",
                            "REMOVE_FAILED", "KEY_TOO_LONG",     "PAGE_FULL",    "INVALID_STATE",
                            "INVALID_LENGTH"};
#define nvs_error(e) (((e) > ESP_ERR_NVS_BASE) ? nvs_errors[(e) & ~(ESP_ERR_NVS_BASE)] : nvs_errors[0])

BoardCfg::BoardCfg() : _handle(0), _started(false), _readOnly(false) {}

BoardCfg::~BoardCfg() { end(); }

bool BoardCfg::begin(const char *name, bool readOnly, const char *partition_label) {
    if (_started) {
        return false;
    }
    _readOnly = readOnly;
    esp_err_t err = ESP_OK;
    if (partition_label != NULL) {
        err = nvs_flash_init_partition(partition_label);
        if (err) {
            log_e("nvs_flash_init_partition failed: %s", nvs_error(err));
            return false;
        }
        err = nvs_open_from_partition(partition_label, name, readOnly ? NVS_READONLY : NVS_READWRITE, &_handle);
    } else {
        err = nvs_open(name, readOnly ? NVS_READONLY : NVS_READWRITE, &_handle);
    }
    if (err) {
        log_e("nvs_open failed: %s", nvs_error(err));
        return false;
    }
    _started = true;
    return true;
}

void BoardCfg::end() {
    if (!_started) {
        return;
    }
    nvs_close(_handle);
    _started = false;
}
