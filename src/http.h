/******************************************************************************
* HTTP wrapper for Universal Analytics library in C
* Copyright (c) 2013, Analytics Pros
* 
* This project is free software, distributed under the BSD license. 
* Analytics Pros offers consulting and integration services if your firm needs 
* assistance in strategy, implementation, or auditing existing work.
******************************************************************************/

/* This module provides an abstraction over CURL for HTTP handling.
 * Currently we rely on CURL to process HTTP requests to Google's servers,
 * however its dependencies may not be practical to support in some systems,
 * so this abstraction will hopefully make it simpler to support alternative
 * HTTP libraries in the future. */

/* Header guard, prevent multiple definition */
#ifndef HTTP_H
#define HTTP_H 1

#include <stdlib.h>
#include <curl/curl.h>
#include <libssl.h>

#define UA_MAX_QUERY_LEN 4096
#define UA_MAX_QUERY_QUEUE 10
#define HTTP_STATUS_MESSAGE_LEN 32

/* Callback types */
typedef void* (*UAGenericCallback)(void*);
typedef int (*UAEventCallback)(char*, void*);
typedef int (*UAHTTPPOSTProcessor)(char*, char*, char*);
typedef char* (*UAURLEncoder)(char*);



typedef struct HTTPQueue_t {

  unsigned int count;
  CURLM* handler;
  CURL* requests[ UA_MAX_QUERY_QUEUE ];

} HTTPQueue_t;


void HTTPcleanup(HTTPQueue_t* queue);
void HTTPsetup(HTTPQueue_t* queue);
void HTTPflush(HTTPQueue_t* queue);

typedef struct HTTPResponse_t {
	int response_code;
	char response_message[HTTP_STATUS_MESSAGE_LEN +1];
} HTTPResponse_t;

typedef enum HTTPMethod {
	HTTP_GET = 0,
	HTTP_POST = 1
} HTTPMethod_t;

typedef struct HTTPSocket_t {

} HTTPSocket_t;

HTTPResponse_t HTTPrequest(HTTPMethod_t method, char* request)



int HTTPenqueue(HTTPQueue_t* queue, const char* endpoint, const char* useragent, const char* query, unsigned int query_len);

#endif /* HTTP_H */
