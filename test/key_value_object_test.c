
/*
 * The MIT License
 *
 * Copyright 2019 Adewale Azeez <azeezadewale98@gmail.com>.
 *
 */
 
#include <stdlib.h>
#include <stdio.h>
#include "../key_value_object.c"

int main() {
	key_value_object* kvo1 = init_key_value_object("Greetings", "Hello world from thecarisma");
	printf("%s", key_value_object_to_string(kvo1));
	return 0;
}