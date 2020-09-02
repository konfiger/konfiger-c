
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 24 August 2020
    \file konfiger_stream.h
*/


#ifndef KONFIGER_STREAM_H
#define KONFIGER_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

struct konfiger_entry {
    char *key;
    char *value;
};

struct konfiger_stream {
    unsigned err_tolerance:1;
    unsigned is_file:1;
    unsigned trimming_key:1;
    unsigned trimming_value:1;
    char delimeter;
    char seperator;
    char continuation_char;
    char *comment_prefix;
    void *stream_obj;
};

typedef struct konfiger_entry KonfigerEntry;
typedef struct konfiger_stream KonfigerStream;

enum konfiger_stat {
    KONFIGER_OK,
    KONFIGER_ERR
};

enum konfiger_stat          ks_init(KonfigerStream **out);
unsigned                    ks_is_trimming_key(KonfigerStream *stream);
void                        ks_set_trimming_key(KonfigerStream *stream, unsigned new_value);
unsigned                    ks_is_trimming_value(KonfigerStream *stream);
void                        ks_set_trimming_value(KonfigerStream *stream, unsigned new_value);
char*                       ks_get_comment_prefix(KonfigerStream *stream);
void                        ks_set_comment_prefix(KonfigerStream *stream, char *new_value);
char                        ks_get_continuation_char(KonfigerStream *stream);
void                        ks_set_continuation_char(KonfigerStream *stream, char new_value);
unsigned                    ks_is_error_tolerant(KonfigerStream *stream);
void                        ks_error_tolerance(KonfigerStream *stream, unsigned new_value);
unsigned                    ks_has_next(KonfigerStream *stream);
enum konfiger_stat          ks_next(KonfigerStream *stream, KonfigerEntry **out);

#ifdef __cplusplus
}
#endif


#endif