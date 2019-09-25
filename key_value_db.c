
/*
 * The MIT License
 *
 * Copyright 2019 Azeez Adewale <azeezadewale98@gmail.com>.
 *
 */
 
#ifdef _WIN32
	#define KVDB_API __declspec(dllexport)
#else
#if defined(_MSC_VER)
    //  Microsoft 
    #define KVDB_API __declspec(dllexport)
    #define KVDB_API __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define KVDB_API __attribute__((visibility("default")))
    #define KVDB_API
#else
    //  do nothing and hope for the best?
    #define KVDB_API
    #define KVDB_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

#ifndef key_value_db_H
#define key_value_db_H
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "key_value_object.c"

typedef int kvdb_bool ;
#define KVDB_TRUE 1
#define KVDB_FALSE 0

typedef struct key_value_db 
{
	char delimeter;
	char seperator; 
	kvdb_bool db_changed; 
	kvdb_bool is_case_sensitive; 
	kvdb_bool has_been_parsed; //do not mess with this field 
	int key_value_objects_index;
	char *string_value; 
	/* do not access the field 'string_value' directly use the key_value_db_to_string function. 
	If you are thinking of ignoring this warning please see a psychiatrist */
	key_value_object* key_value_objects[]; 
	
} key_value_db;

KVDB_API key_value_db* init_key_value_db();
KVDB_API key_value_db* init_key_value_db_1(char* kvdb_value);
key_value_db* key_value_db_parse(key_value_db* kvdb, char* kvdb_value, kvdb_bool case_sensitive, char delimeter, char seperator, kvdb_bool err_tolerance);
KVDB_API char* key_value_db_to_string(key_value_db* kvdb);

KVDB_API key_value_db* init_key_value_db() 
{
	key_value_db* kvdb = (key_value_db *) malloc(sizeof(key_value_db));
	return key_value_db_parse(kvdb, "", KVDB_TRUE, '=', '\n', KVDB_FALSE);
}

KVDB_API key_value_db* init_key_value_db_1(char* kvdb_value) 
{
	key_value_db* kvdb = (key_value_db *) malloc(sizeof(key_value_db));
	return key_value_db_parse(kvdb, kvdb_value, KVDB_TRUE, '=', '\n', KVDB_FALSE);
}

/*
	Do not call this function directly, it is referenced from within 
	the key value db object init functions. 
	Don't be an a-hole
*/
key_value_db* key_value_db_parse(key_value_db* kvdb, char* kvdb_value, kvdb_bool case_sensitive, char delimeter, char seperator, kvdb_bool err_tolerance) 
{
	kvdb_bool parse_key = KVDB_TRUE;
	int length = strlen(kvdb_value);
	char value[] = "\0" ;
	char key[] = "\0" ;
	int column = 0;
	int line = 1; 
	int index ; 
	
	if (kvdb == NULL) kvdb = (key_value_db *) malloc(sizeof(key_value_db));
	kvdb->delimeter = delimeter;
	kvdb->seperator = seperator;
	kvdb->key_value_objects_index = 0;
	kvdb->db_changed = KVDB_TRUE;
	kvdb->is_case_sensitive = case_sensitive;
	kvdb->has_been_parsed = KVDB_TRUE;
	
	for (index = 0;*kvdb_value != '\0'; kvdb_value++, index++) 
	{
		column++;
		if (*kvdb_value == '\r') 
		{ 
			index--;
			continue;
		}
		if (*kvdb_value == '\n') 
		{
			line++;
			column = 0 ;
		} 
		
		if (*kvdb_value == seperator) {
			if (strcmp(key, "") == 0 && strcmp(value, "") == 0) continue;
			if (parse_key == KVDB_TRUE && err_tolerance == KVDB_FALSE) 
			{
				printf("key_value_db ERROR: Invalid entry detected near Line %i:%i", line, column); 
				exit(0);
			}
			key_value_object* kvo1 = init_key_value_object_empty();
			printf("?%s \n", key);
			kvdb->key_value_objects[kvdb->key_value_objects_index] = kvo1;
			kvo1->key = (char*) malloc(sizeof (char) * strlen(key));
			kvo1->value = (char*) malloc(sizeof (char) * strlen(value));
			strcpy(kvo1->key, key);
			strcpy(kvo1->value, value);
			parse_key = KVDB_TRUE ;
			key[0] = '\0';
			value[0] = '\0';
			kvdb->key_value_objects_index++;
			continue;
		}
		if (*kvdb_value == delimeter) {
			if (strcmp(value, "") != 0 && err_tolerance == KVDB_FALSE) 
			{
				printf("key_value_db ERROR: The input is improperly separated near Line %i:%i. Check the separator", line, column); 
				exit(0);
			}
			parse_key = KVDB_FALSE ;
			continue;
		}
		if (parse_key == KVDB_TRUE) {
			int len = strlen(key);
			key[len] = ((case_sensitive == KVDB_FALSE)) ? ((*kvdb_value <= 'Z' && *kvdb_value >= 'A') ? *kvdb_value + 32 : *kvdb_value) : *kvdb_value;
			key[len+1] = '\0';
		} else {
			int len = strlen(value);
			value[len] = *kvdb_value;
			value[len+1] = '\0';
		}
		
	}
	if (strcmp(key, "") != 0 || strcmp(value, "") != 0) 
	{
		key_value_object* kvo1 = init_key_value_object_empty();
		kvdb->key_value_objects[kvdb->key_value_objects_index] = kvo1;
		kvo1->key = (char*)malloc(strlen(key));
		kvo1->value = (char*)malloc(strlen(value));
		strncpy(kvo1->key, key, strlen(key));
		strncpy(kvo1->value, value, strlen(value));
		kvdb->key_value_objects_index++;
	}
	
	return kvdb;
}

KVDB_API char* key_value_db_to_string(key_value_db* kvdb) 
{
	if (kvdb == NULL) return "" ;
	char d[2];
	if (kvdb->db_changed) 
	{
		kvdb->string_value = (char *) malloc (sizeof (char) * 10000);
		kvdb->string_value[0] = '\0';
		
		for (int i = 0; i < kvdb->key_value_objects_index; i++) 
		{
			strcat(kvdb->string_value, kvdb->key_value_objects[i]->key);
			snprintf(d, sizeof(d), "%c\0", kvdb->delimeter);
			d[2] = '\0' ;
			strcat(kvdb->string_value, d);
			strcat(kvdb->string_value, kvdb->key_value_objects[i]->value);
			if (i != (kvdb->key_value_objects_index - 1)) 
			{
				snprintf(d, sizeof(d), "%c\0", kvdb->seperator);
				d[2] = '\0' ;
				strcat(kvdb->string_value, d);
			}
		}
	}
	return kvdb->string_value ;
}

#endif