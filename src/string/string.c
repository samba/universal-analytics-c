

#include "string.h"


unsigned long int char_concat_explicit(char** result_in, char* a, unsigned long int a_len, char* b, unsigned long int b_len){
	unsigned long int result_len;
	char* result = NULL;

	// Ignore terminating null
	if(a[a_len -1] == '\0'){
		while(a[a_len--] == '\0'){
			// do nothing
		}
	}

	// Ignore terminating null
	if(b[b_len -1] == '\0'){
		while(b[b_len--] == '\0'){
			// do nothing
		}
	}

	result_len = (a_len + b_len) +1;
	result = malloc(sizeof(char) * result_len);

	memset(result, 0, result_len);
	strncpy(result, a, a_len);
	strncpy(result + a_len, b, b_len);

	(*result_in) = result;
	return (unsigned long int)(result_len);
}


UAString_t* char_concat(char* a, char* b){
	UAString_t* result = malloc(sizeof(UAString_t));
	result->length = char_concat_explicit(&(result->value), a, strlen(a), b, strlen(b));
	return result;
}


UAString_t* string_nocopy(char* value, unsigned long int length){
	UAString_t* newstring = malloc(sizeof(UAString_t));
	newstring->value = value;
	newstring->length = length;
	return newstring;
}

UAString_t* string_copy(char* value, unsigned long int length){
	unsigned long int i = 0;
	UAString_t* newstring = malloc(sizeof(UAString_t));
	newstring->value = malloc(sizeof(char) * length +1);
	newstring->length = 0;
	memset(newstring->value, 0, length);

	if(value != NULL){

		for(i = 0; i < length; i++){
			if(value[i] == '\0'){
				length = i++;
				break;
			}
		}

		strncpy(newstring->value, value, length);
		newstring->length = length;
	}
	return newstring;
}

UAString_t* string(char* value){
	unsigned long int newlen = (value == NULL) ? 0 : strlen(value) +1;
	return string_copy(value, newlen);
}

void wipe(UAString_t* string){
	memset(string->value, 0, string->length);
}

void freestr(UAString_t* string){
	wipe(string);
	free(string->value);
	free(string);
}


UAString_t* concat(UAString_t* a, UAString_t* b){
	UAString_t* result = malloc(sizeof(UAString_t));
	result->length = char_concat_explicit(&(result->value), a->value, a->length, b->value, b->length);
	return result;
}