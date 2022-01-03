//
// Created by Ezra on 8/11/2020.
//

#include "commonfunc.h"
#include "cstring"

extern unsigned char sBox[256];

unsigned char w[AES_ROUNDS + 1][4][4];

unsigned char FFmul(unsigned char a, unsigned char b)
{
    unsigned char bw[4];
    unsigned char res = 0;
    int i;
    bw[0] = b;
    for (i = 1; i < 4; i++) {
        bw[i] = bw[i - 1] << 1;
        if (bw[i - 1] & 0x80) {
            bw[i] ^= 0x1b;
        }
    }
    for (i = 0; i < 4; i++) {
        if ((a >> i) & 0x01) {
            res ^= bw[i];
        }
    }
    return res;
}

//轮密匙加
void AddRoundKey(unsigned char state[][4], unsigned char k[][4])
{
    int r, c;
    for (c = 0; c < 4; c++) {
        for (r = 0; r < 4; r++) {
            state[r][c] ^= k[r][c];
        }
    }
}

void KeyExpansion(const unsigned char* key, unsigned char kw[][4][4])
{
    int i, j, r, c;
    unsigned char rc[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };
    for (r = 0; r < 4; r++) {
        for (c = 0; c < 4; c++) {
            kw[0][r][c] = key[r + c * 4];
        }
    }
    for (i = 1; i <= 10; i++) {
        for (j = 0; j < 4; j++) {
            unsigned char t[4];
            for (r = 0; r < 4; r++) {
                t[r] = j ? kw[i][r][j - 1] : kw[i - 1][r][3];
            }
            if (j == 0) {
                unsigned char temp = t[0];
                for (r = 0; r < 3; r++) {
                    t[r] = sBox[t[(r + 1) % 4]];
                }
                t[3] = sBox[temp];
                t[0] ^= rc[i - 1];
            }
            for (r = 0; r < 4; r++) {
                kw[i][r][j] = kw[i - 1][r][j] ^ t[r];
            }
        }
    }
}

void make_empty(unsigned char str[16], size_t size)
{
    std::memset(str, 0, sizeof(unsigned char) * size);
}