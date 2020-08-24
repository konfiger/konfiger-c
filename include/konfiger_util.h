
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 24 August 2020
    \file konfiger_util.h
*/


#ifndef KONFIGER_UTIL_H
#define KONFIGER_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

/** 
    The inline keyword to optimize the function. In 
    C89 and C90 the inline keyword semantic is 
    different from current C standard semantic hence 
    for compilation targeting C89 or C99 the inline 
    keyword is ommited.
*/
#ifdef __STDC_VERSION__
    #define __KONFIGER_STDC_VERSION__ __STDC_VERSION__
#else
    #ifdef __cplusplus
        #if __cplusplus > 199711L
            #define __KONFIGER_STDC_VERSION__ __cplusplus
        #endif
    #endif
#endif
#ifndef __KONFIGER_STDC_VERSION__
    #define __KONFIGER_INLINE__ 
    #define __KONFIGER_LONG_LONG__ long
    #define __FUNCTION__ "<unknown>"
#else 
    #define __KONFIGER_INLINE__ inline
    #define __KONFIGER_LONG_LONG__ long long
    #define __FUNCTION__ __func__
#endif

char __KONFIGER_INLINE__ *escape_string(const char *value, char extra_escape[]) {
    char *final_value = malloc(sizeof(char) * (strlen(value))); // WARN inefficient
    unsigned index = 0, index2 = 0, index3 = 0;
    int es_len = (sizeof(extra_escape) / sizeof(extra_escape[0]));
    while (value[index++] != '\0') {
        if (es_len > 0 && extra_escape != NULL) {
            for (index2 = 0; index2 < es_len; ++index2) {
                if (value[index-1] == extra_escape[index2]) {
                    final_value[index3] = '^';
                    ++index3;
                    break;
                }
            }
        }
        final_value[index3] = value[index-1];
        ++index3;
    }
    final_value[index3] = '\0';
    return final_value;
}

char __KONFIGER_INLINE__ *un_escape_string(const char *value, char extra_escape[]) {
    char c;
    char *final_value = malloc(sizeof(char) * (strlen(value))); // WARN inefficient
    unsigned index = 0, index2 = 0, index3 = 0, continua = 0;
    int es_len = (sizeof(extra_escape) / sizeof(extra_escape[0]));
    while (value[index++] != '\0') {
        c = value[index-1];
        if (c == '^') {
            if (value[index] == '\0') {
                final_value[index3] = c;
                break;
            }
            if (es_len > 0 && extra_escape != NULL) {
                continua = 0;
                for (index2 = 0; index2 < es_len; ++index2) {
                    if (value[index] == extra_escape[index2]) {
                        continua = 1;
                        break;
                    }
                }
                if (continua == 1) {
                    continue;
                }
            }
            final_value[++index3] = '^';
            final_value[++index3] = value[index];
            continue;
        }
        final_value[index3] = c;
        ++index3;
    }
    final_value[index3] = '\0';
    return final_value;
}

#ifdef __cplusplus
}
#endif


#endif