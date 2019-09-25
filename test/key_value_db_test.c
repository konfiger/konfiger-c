
/*
 * The MIT License
 *
 * Copyright 2019 Azeez Adewale <azeezadewale98@gmail.com>.
 *
 */
 
#include <stdlib.h>
#include <stdio.h>
#include "../key_value_db.c"

int main() {
	key_value_db* kvo1 = init_key_value_db_1("Threes=3333\nVersion=1.0.1\nDate=Today\nTime=Now\nOS=Windows");
	printf("%s", key_value_db_to_string(kvo1));
	return 0;
}