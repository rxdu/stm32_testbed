/* 
 * ringbuf.c
 * 
 * Created on: Dec 08, 2019 22:22
 * Description: 
 * 
 * Implementation details:
 * 
 * - Initial state (empty)
 * [0][1][2][3]...[N]
 *  ^
 * R/W
 * 
 * - Add one element
 * [D][1][2][3]...[N]
 *  ^  ^
 *  R  W
 * 
 * - Buffer gets full when last element X is inserted
 * [X][D][D][D]...[D]
 *     ^
 *    W/R (W>R)
 * 
 * - Buffer data overwritten by new element Y after getting full
 * [X][Y][D][D]...[D]
 *        ^
 *       W/R (W>R)
 * 
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#include "ringbuf/ringbuf.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>

// #include "segger/jlink_rtt.h"

#define IsEmpty(buff) (buff->read_index == buff->write_index)
#define OccupiedSpaceSize(buff) (buff->write_index - buff->read_index)

// The most fundamental operations to the ring buffer
static inline size_t RingbufWriteOne(Ringbuf *buff, buf_data_t new_data);
static inline size_t RingbufReadOne(Ringbuf *buff, buf_data_t *data);
static inline size_t RingbufPeekOne(Ringbuf *buff, buf_data_t *data, size_t n);
// Get the last nth element: returns the lastest byte written to buffer when n = 0
static inline size_t RingbufGetLastNthWrittenElement(Ringbuf *buff, buf_data_t *data, size_t n);

/************************** Init/Reset Functions **************************/

void RingbufInit(Ringbuf *buff, buf_data_t *data_ptr, size_t size)
{
    assert(buff != NULL && data_ptr != NULL && size != 0);

    // assert size is a power of 2
    assert((size != 0) && ((size & (size - 1)) == 0));

    buff->size = size;
    buff->size_mask = size - 1;
    buff->data = data_ptr;
    buff->write_index = 0;
    buff->read_index = 0;
#ifdef ENABLE_OVERWRITE
    buff->expect_overflow = false;
#endif
}

void RingbufReset(Ringbuf *buff)
{
    assert(buff != NULL && buff->data != NULL && buff->size != 0);

    buff->write_index = 0;
    buff->read_index = 0;
#ifdef ENABLE_OVERWRITE
    buff->expect_overflow = false;
#endif
}

/************************ Status Checking Functions ***********************/

bool RingbufIsEmpty(Ringbuf *buff)
{
    // return buff->read_index == buff->write_index;
    return IsEmpty(buff);
}

bool RingbufIsFull(Ringbuf *buff)
{
    return OccupiedSpaceSize(buff) == buff->size;
}

size_t RingbufGetFreeSpaceSize(Ringbuf *buff)
{
    return buff->size - OccupiedSpaceSize(buff);
}

size_t RingbufGetOccupiedSpaceSize(Ringbuf *buff)
{
    // return buff->write_index - buff->read_index;
    return OccupiedSpaceSize(buff);
}

/**************************** Write functions *****************************/

size_t RingbufWriteOne(Ringbuf *buff, buf_data_t new_data)
{
#ifdef ENABLE_OVERWRITE
    size_t w_idx = buff->write_index & buff->size_mask;
    buff->data[w_idx] = new_data;

    if (buff->expect_overflow)
    {
        ++buff->write_index;
        ++buff->read_index;
        buff->expect_overflow = false;
        // DPrintf(0, "!!!!!!!!!!!!!!!!!!!! Overflow occurred !!!!!!!!!!!!!!!!!!!!\n", 0);
    }
    else
    {
        ++buff->write_index;
    }

    if ((buff->write_index & buff->size_mask) == (buff->read_index & buff->size_mask))
    {
        // ++buff->read_index;
        // printf("overflow occurred\n");
        buff->expect_overflow = true;
        // printf("expecting overflow\n");
    }

    return 1;
#else
    if (OccupiedSpaceSize(buff) == buff->size)
        return 0;
    buff->data[(buff->write_index++) & buff->size_mask] = new_data;
    
    return 1;
#endif
}

size_t RingbufWrite(Ringbuf *buff, const buf_data_t new_data[], size_t btw)
{
    for (int i = 0; i < btw; ++i)
    {
        if(RingbufWriteOne(buff, new_data[i]) == 0)
            return i;
    }
    return btw;
}

size_t RingbufGetLastNthWrittenElement(Ringbuf *buff, buf_data_t *data, size_t n)
{
    if (n >= OccupiedSpaceSize(buff))
        return 0;

    *data = buff->data[(buff->write_index - (n + 1)) & buff->size_mask];
    return 1;
}

/***************************** Read functions *****************************/

size_t RingbufReadOne(Ringbuf *buff, buf_data_t *data)
{
    if (IsEmpty(buff))
        return 0;

    *data = buff->data[buff->read_index++ & buff->size_mask];

#ifdef ENABLE_OVERWRITE
    buff->expect_overflow = false;
#endif

    return 1;
}

size_t RingbufRead(Ringbuf *buff, buf_data_t data[], size_t btr)
{
    for (int i = 0; i < btr; ++i)
    {
        if (RingbufReadOne(buff, &data[i]) == 0)
            return i;
    }
    return btr;
}

size_t RingbufPeekOne(Ringbuf *buff, buf_data_t *data, size_t n)
{
    if (n >= OccupiedSpaceSize(buff))
        return 0;

    *data = buff->data[(buff->read_index + n) & buff->size_mask];
    return 1;
}

size_t RingbufPeek(Ringbuf *buff, buf_data_t data[], size_t btp)
{
    for (int i = 0; i < btp; ++i)
    {
        if (RingbufPeekOne(buff, &data[i], i) == 0)
            return i;
    }
    return btp;
}

/**************************************************************************/