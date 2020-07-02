/*!@file macros/logging.h
 * @brief Various logging macros
 */
#ifndef MACROS_LOGGING_H
#define MACROS_LOGGING_H

#include<stdio.h>
#include<stdbool.h>

/* debug variable */
#if !defined NDEBUG
   #define DBGVAR(v,f)                          \
      fprintf(stderr, #v " = %" #f "(%s:%d)\n", \
         v, __FILE__, __LINE__)
#else
   #define DBGVAR(v,f)
#endif

/* debug msg */
#if !defined NDEBUG
   #define DBGLOG(n,m)                  \
      fprintf(stderr,#n":"#m"\n")
#else
   #define DBGLOG(v,f)
#endif

/* debug msg to file/socket/http
 * todo: implement source and header for this along with macro
 */

#endif
