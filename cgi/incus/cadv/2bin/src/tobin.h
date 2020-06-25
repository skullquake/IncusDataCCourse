/*!@file: ./src/tobin.c
 * @brief: prints out binary representation of data
 *         note that endianness influences the order of members in bitfields in terms of distribution in memory
 */
#ifndef TOBIN_H
#define TOBIN_H
#include<stdio.h>
#ifdef __cplusplus
extern "C"{
#endif
/*!@brief converts data to binary string and writes to stream
 * @param data data
 * @param sz   data size
 * @param fp   stream to write to
 * @return     void
 */
extern void tobinstream(void*data,size_t sz,FILE*fp);
#endif
#ifdef __cplusplus
}
#endif
