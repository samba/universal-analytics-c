/* Strings library for simplifying handling in Universal Analytics kit */

#ifndef UA_STRING_H
#define UA_STRING_H

#include <string.h>
#include <stdlib.h>

typedef struct UAString_t {
	unsigned long int length;
	char* value;
} UAString_t;


typedef struct UAString_t* UAString;

void wipe(UAString_t* string);
void freestr(UAString_t* string);

UAString_t* concat(UAString_t* a, UAString_t* b);
UAString_t* string(char* value);
UAString_t* string_nocopy(char* value, unsigned long int length);

UAString_t* char_concat(char* a, char* b);

#endif /* UA_STRING_H */
