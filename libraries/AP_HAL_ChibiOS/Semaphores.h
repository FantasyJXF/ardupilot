/*
 * This file is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Code by Andrew Tridgell and Siddharth Bharat Purohit
 */
#pragma once

#include <AP_HAL/AP_HAL_Boards.h>

#if CONFIG_HAL_BOARD == HAL_BOARD_CHIBIOS
#include "AP_HAL_ChibiOS.h"

class ChibiOS::Semaphore : public AP_HAL::Semaphore {
public:
    Semaphore() {
        chMtxObjectInit(&_lock);
    }
    bool give();
    bool take(uint32_t timeout_ms);
    bool take_nonblocking();
    bool check_owner(void) {
        return _lock.owner == chThdGetSelfX();
    }
    void assert_owner(void) {
        osalDbgAssert(check_owner(), "owner");
    }
private:
    mutex_t _lock;
};
#endif // CONFIG_HAL_BOARD
