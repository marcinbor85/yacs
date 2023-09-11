/*
The MIT License (MIT)

Copyright (c) 2023 Marcin Borowicz <marcinbor85@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

#ifndef COBS_TYPES_H
#define COBS_TYPES_H

#include <stdint.h>
#include <stddef.h>

struct cobs;

typedef void (*cobs_data_callback_t)(struct cobs *self, uint8_t *data, size_t size);

typedef enum {
        COBS_DECODE_STATE_WAIT_FOR_TAG,
        COBS_DECODE_STATE_COLLECT_DATA_IN_GROUP,
        COBS_DECODE_STATE_COLLECT_DATA_IN_GROUP_NO_EOF,
} cobs_decode_state_t;

struct cobs {
        cobs_decode_state_t decode_state;
        uint8_t tag;
        uint8_t *rx_buf;
        size_t rx_buf_size;
        size_t rx_buf_index;
};

#endif /* COBS_TYPES_H*/
