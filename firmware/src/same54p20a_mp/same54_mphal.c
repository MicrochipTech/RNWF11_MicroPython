/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <string.h>
#include "py/stream.h"
#include "py/mphal.h"
#include "board.h"
#include "definitions.h"

static int interrupt_char;

void mp_hal_init(void) {
    MP_STATE_PORT(keyboard_interrupt_obj) = mp_obj_new_exception(&mp_type_KeyboardInterrupt);
}

mp_uint_t mp_hal_ticks_ms(void) {
  
    return xTaskGetTickCount();
}

void mp_hal_delay_ms(mp_uint_t ms) {
    
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

void mp_hal_delay_us(mp_uint_t us) {
    
}

void mp_hal_delay_ns(mp_uint_t ns) {

}

mp_uint_t mp_hal_ticks_us(){
    return 0;
}

mp_uint_t mp_hal_ticks_ns(){
    return 0;
}

mp_uint_t mp_hal_ticks_cpu()
{
    return 0;
}

uint64_t mp_hal_time_ns()
{
    return 0;
}
void mp_hal_set_interrupt_char(int c) {
    interrupt_char = c;
}


int mp_hal_stdin_rx_chr(void) {
    
    char new_c;
    
    for (;;) {
        if (SYS_CONSOLE_Read(SYS_CONSOLE_DEFAULT_INSTANCE, &new_c, 1) > 0 )
        {
         //   SYS_CONSOLE_MESSAGE(&new_c);
            return new_c;
        }
    }
}

void mp_hal_stdout_tx_str(const char *str) {
    
   // SYS_CONSOLE_MESSAGE(str);
    mp_hal_stdout_tx_strn(str, strlen(str));
}

void mp_hal_stdout_tx_strn(const char *str, size_t len) {
    for (; len > 0; --len) {
        SYS_CONSOLE_PRINT("%c", *str);
        str++;
    }
}

void mp_hal_stdout_tx_strn_cooked(const char *str, size_t len) {
    for (; len > 0; --len) {
        if (*str == '\n') {
            SYS_CONSOLE_MESSAGE("\r");
        }
        SYS_CONSOLE_PRINT("%c", *str);
        str++;
    }
}
