
/*
 * The MIT License
 *
 * Copyright 2019 Adewale Azeez <azeezadewale98@gmail.com>.
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

#ifndef key_value_object_H
#define key_value_object_H
#include <string.h>

typedef struct key_value_object 
{
	char *key;
	char *value; 
	
} key_value_object;

KVDB_API key_value_object* init_key_value_object_empty();
KVDB_API key_value_object* init_key_value_object(char* key, char* value);
KVDB_API char* key_value_object_get_key(key_value_object* kvo);
KVDB_API char* key_value_object_get_value(key_value_object* kvo);
KVDB_API void key_value_object_set_key(key_value_object* kvo, char* key);
KVDB_API void key_value_object_set_value(key_value_object* kvo, char* value);
KVDB_API char* key_value_object_to_string(key_value_object* kvo);

KVDB_API key_value_object* init_key_value_object_empty() 
{
	key_value_object* kvo = (key_value_object *) malloc(sizeof(key_value_object));
	
	return kvo;
}

KVDB_API key_value_object* init_key_value_object(char* key, char* value) 
{
	key_value_object* kvo = (key_value_object *) malloc(sizeof(key_value_object));
	kvo->key = key;
	kvo->value = value;
	
	return kvo;
}

KVDB_API char* key_value_object_get_key(key_value_object* kvo) 
{
	if (kvo == NULL) return "" ;
	return kvo->key;
}

KVDB_API char* key_value_object_get_value(key_value_object* kvo) 
{
	if (kvo == NULL) return "" ;
	return kvo->value;
}

KVDB_API void key_value_object_set_key(key_value_object* kvo, char* key) 
{
	if (kvo == NULL) return ;
	kvo->key = key;
}

KVDB_API void key_value_object_set_value(key_value_object* kvo, char* value) 
{
	if (kvo == NULL) return ;
	kvo->value = value;
}

KVDB_API char* key_value_object_to_string(key_value_object* kvo) 
{
	if (kvo == NULL) return "" ;
	char * string_value = (char *) malloc (sizeof (char) * 100);

	string_value[0]='\0';
    strcat(string_value, "key_value_object:");
    strcat(string_value, "Key=");
    strcat(string_value, kvo->key);
    strcat(string_value, ":");
    strcat(string_value, "Value=");
    strcat(string_value, kvo->value);
	return string_value ;
}

#endif
