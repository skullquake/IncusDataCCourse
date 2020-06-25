/*!@file: ./src/tobin.c
 * @brief: prints out binary representation of data
 *         note that endianness influences the order of members in bitfields in terms of distribution in memory
 */
#ifndef TOBIN_H
#define TOBIN_H
#include<stdio.h>
extern void tobinstream(void*data,size_t sz,FILE*fp);
#endif
