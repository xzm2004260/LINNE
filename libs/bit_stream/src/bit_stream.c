#include "bit_stream.h"
#include <stdint.h>

/* 下位ビットを取り出すマスク 32bitまで */
const uint32_t g_bitstream_lower_bits_mask[33] = {
    0x00000000UL,
    0x00000001UL, 0x00000003UL, 0x00000007UL, 0x0000000FUL,
    0x0000001FUL, 0x0000003FUL, 0x0000007FUL, 0x000000FFUL,
    0x000001FFUL, 0x000003FFUL, 0x000007FFUL, 0x00000FFFUL,
    0x00001FFFUL, 0x00003FFFUL, 0x00007FFFUL, 0x0000FFFFUL,
    0x0001FFFFUL, 0x0003FFFFUL, 0x0007FFFFUL, 0x000FFFFFUL,
    0x001FFFFFUL, 0x000FFFFFUL, 0x007FFFFFUL, 0x00FFFFFFUL,
    0x01FFFFFFUL, 0x03FFFFFFUL, 0x07FFFFFFUL, 0x0FFFFFFFUL,
    0x1FFFFFFFUL, 0x3FFFFFFFUL, 0x7FFFFFFFUL, 0xFFFFFFFFUL
};

/* 0のラン長パターンテーブル（注意：上位ビットからのラン長） */
const uint32_t g_bitstream_zerobit_runlength_table[256] = {
    8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};