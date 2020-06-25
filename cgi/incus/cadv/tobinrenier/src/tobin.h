/*!@file  tobin.h
*  @brief Conversion to Binary Specification
*/
#if !defined HD85FA5D83C6746A194F0F4AF60E27DE5
    #define  HD85FA5D83C6746A194F0F4AF60E27DE5
#if defined __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*!@brief Convert to Binary
*
* @param dest Destination buffer. Caller must ensure enough space.
* @param num Number to convert.
* @param len Padding length, if necessary.
*
* @return dest
*/
extern const char* tobin (char* dest, uint64_t num, int len);

#if defined __cplusplus
}
#endif
#endif
