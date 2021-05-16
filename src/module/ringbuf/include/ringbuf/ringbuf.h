/* 
 * ringbuf.h
 * 
 * Created on: Dec 08, 2019 22:22
 * Description: 
 * 
 * Requirements:
 *  1. Size of buffer must be a power of 2
 *  2. Maximum buffer size is 2^(number_of_bits_of(size_t)-1)
 * 
 * Default behaviors:
 *  1. Oldest data will be overwritten if buffer is full
 * 
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef RINGBUF_H
#define RINGBUF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// #define ENABLE_OVERWRITE

#ifndef buf_data_t
#define buf_data_t uint8_t
#endif

typedef struct
{
    buf_data_t *data;   // pointer to the buffer memory
    size_t size;        // size of allocated memory area
    size_t size_mask;   // for internal indexing management
    size_t write_index; // place new data to be written
    size_t read_index;  // place earliest written data to be read from 
#ifdef ENABLE_OVERWRITE
    bool expect_overflow;   // flag set when next write will overwrite the data which the current read index points to
#endif
} Ringbuf;

// Init buffer
void RingbufInit(Ringbuf *buff, buf_data_t *data_ptr, size_t size);
void RingbufReset(Ringbuf *buff);

/* Buffer size information */
bool RingbufIsEmpty(Ringbuf *buff);
bool RingbufIsFull(Ringbuf *buff);

size_t RingbufGetFreeSpaceSize(Ringbuf *buff);
size_t RingbufGetOccupiedSpaceSize(Ringbuf *buff);

// Read/Write functions
size_t RingbufWrite(Ringbuf *buff, const buf_data_t new_data[], size_t btw);
size_t RingbufRead(Ringbuf *buff, buf_data_t data[], size_t btr);
size_t RingbufPeek(Ringbuf *buff, buf_data_t data[], size_t btp);

#ifdef __cplusplus
}
#endif

#endif /* RINGBUF_H */
