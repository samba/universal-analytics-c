#include "../src/string/string.h"
#include "../src/string/encode.h"
#include <stdio.h>
#include <stdlib.h>

#define test_hexadecimal_representation 1
#define test_concatenation 0
#define test_encoding 0
#define test_hexdigest 1


int print_char_codes(char* value, unsigned int length){
	unsigned int i;
	printf("Character codes for: '%s'\n", value);
	printf("> ");
	for(i = 0; i < length; i++){
		printf("%u ", value[i]);
	}
	printf("\n");
	return i;
}


int main(int argc, char* argv[]){



	if(test_concatenation){
		UAString h = string("(hebrew) [סֶאבױ].");
		UAString q = string("Man muss oft üben wenn er echt Deutsch lernen würde. ");
		UAString p = string("I'm testing concatenation.\n");


		UAString result = char_concat(q->value, p->value);

		printf("Concatenating two strings: \"%s\", and \"%s\"\n", q->value, p->value);
		printf("Test: '%s'\n", result->value);


		UAString z = concat(h, concat(q, p));

		printf("Result value: \"%s\"\n", z->value);
		printf("Result length (stored): %lu\n", z->length);
		printf("Result length (detected): %lu\n", strlen(z->value));


		freestr(p);
		freestr(q);
		freestr(z);
	}

	if(test_encoding){

		char script[] = "function(a){ pizza }";
		char* x = urlencode(script);
		printf("Encoded result: '%s'\n", x);

		char hebrew[] = "[סֶאבױ]";
		char* y = urlencode(hebrew);
		printf("Encoded result: '%s'\n", y);

		free(x);
		free(y);

	}

	if(test_hexdigest){
		char md5_result[33] = {0};
		unsigned char md5_binary[16] = {94, 182, 59, 187, 224, 30, 238, 208, 147, 203, 34, 187, 143, 90, 205, 195}; // hash of "hello world"
		hexdigest(md5_result, md5_binary, 16);
		printf("MD5 hexdigest: %s\n", md5_result);
	}
	

	return 0;
}

