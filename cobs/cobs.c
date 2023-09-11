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

#include "cobs.h"

#define COBS_EOF_BYTE           0x00
#define COBS_NO_EOF_BYTE        0xFF

void cobs_init(struct cobs *self, uint8_t *rx_buf, size_t rx_buf_size)
{
        self->rx_buf = rx_buf;
        self->rx_buf_size = rx_buf_size;
        self->rx_buf_index = 0;
        self->tag = 0;
        self->decode_state = COBS_DECODE_STATE_WAIT_FOR_TAG;
}

void cobs_decode(struct cobs *self, uint8_t *data, size_t size, cobs_data_callback_t decode_cb)
{
        while (size-- > 0) {
                uint8_t b = *data++;

                switch (self->decode_state) {
                case COBS_DECODE_STATE_WAIT_FOR_TAG:
                        switch (b) {
                        case COBS_EOF_BYTE:
                                continue;

                        case COBS_NO_EOF_BYTE:
                                self->decode_state = COBS_DECODE_STATE_COLLECT_DATA_IN_GROUP_NO_EOF;
                                break;

                        default:
                                self->decode_state = COBS_DECODE_STATE_COLLECT_DATA_IN_GROUP;
                                break;
                        }
                        self->tag = b;
                        self->rx_buf_index = 0;
                        break;

                case COBS_DECODE_STATE_COLLECT_DATA_IN_GROUP:
                case COBS_DECODE_STATE_COLLECT_DATA_IN_GROUP_NO_EOF:
                        self->tag--;

                        if (self->tag == COBS_EOF_BYTE) {
                                switch (b) {
                                case COBS_EOF_BYTE:
                                        decode_cb(self, self->rx_buf, self->rx_buf_index);

                                        self->decode_state = COBS_DECODE_STATE_WAIT_FOR_TAG;
                                        continue;

                                case COBS_NO_EOF_BYTE:
                                        if (self->decode_state == COBS_DECODE_STATE_COLLECT_DATA_IN_GROUP) {
                                                if (self->rx_buf_index >= self->rx_buf_size) {
                                                        self->decode_state = COBS_DECODE_STATE_WAIT_FOR_TAG;
                                                        self->rx_buf_index = 0;
                                                        continue;
                                                }
                                                self->rx_buf[self->rx_buf_index++] = COBS_EOF_BYTE;
                                        }

                                        self->decode_state = COBS_DECODE_STATE_COLLECT_DATA_IN_GROUP_NO_EOF;
                                        break;

                                default:
                                        if (self->decode_state == COBS_DECODE_STATE_COLLECT_DATA_IN_GROUP) {
                                                if (self->rx_buf_index >= self->rx_buf_size) {
                                                        self->decode_state = COBS_DECODE_STATE_WAIT_FOR_TAG;
                                                        self->rx_buf_index = 0;
                                                        continue;
                                                }
                                                self->rx_buf[self->rx_buf_index++] = COBS_EOF_BYTE;
                                        }

                                        self->decode_state = COBS_DECODE_STATE_COLLECT_DATA_IN_GROUP;
                                        break;
                                }
                                self->tag = b;
                        } else {
                                switch (b) {
                                case COBS_EOF_BYTE:
                                        self->decode_state = COBS_DECODE_STATE_WAIT_FOR_TAG;
                                        continue;

                                default:
                                        if (self->rx_buf_index >= self->rx_buf_size) {
                                                self->decode_state = COBS_DECODE_STATE_WAIT_FOR_TAG;
                                                self->rx_buf_index = 0;
                                                continue;
                                        }
                                        self->rx_buf[self->rx_buf_index++] = b;
                                        break;
                                }
                        }
                        break;

                default:
                        break;
                }
        }
}

void cobs_encode(struct cobs *self, uint8_t *data, size_t size)
{
        // TODO
}
