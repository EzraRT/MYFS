//
// Created by Ezra on 8/11/2020.
//

#ifndef EASY_AES_COMMONFUNC_H
#define EASY_AES_COMMONFUNC_H

#include"aes_defs.h"

extern unsigned char w[AES_ROUNDS + 1][4][4];

//矩阵乘法操作，用于列混合操作中
unsigned char FFmul(unsigned char a, unsigned char b);

//密匙轮加
void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);

/*
 * 密匙拓展 使用给定的key(16个字节长)来拓展生成出每一轮需要使用的密匙矩阵
 * 在进行加密解密操作前要调用该函数来初始化密匙相关矩阵
 */
void KeyExpansion(const unsigned char *key, unsigned char kw[][4][4]);

//快速清空某数组 以0填充
void make_empty(unsigned char str[16], size_t size) ;

#endif //EASY_AES_COMMONFUNC_H
