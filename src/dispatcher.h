/******************************************************************************
* Dispatch layer for Universal Analytics for C 
* Copyright (c) 2013, Analytics Pros
* 
* This project is free software, distributed under the BSD license. 
* Analytics Pros offers consulting and integration services if your firm needs 
* assistance in strategy, implementation, or auditing existing work.
******************************************************************************/

#ifndef DISPATCH_H
#define DISPATCH_H 1

#define DISPATCH_MAXIMUM_QUEUE_LEN 1000
#define DISPATCH_REQUEST_QUERY_LEN 2048
#define DISPATCH_REQUEST_BODY_LEN 8192
#define DISPATCH_USER_AGENT_LEN 1024

#include <string.h>
#include "http.h"

typedef struct HTTPRequest {
	unsigned int timestamp;
	unsigned int session_id;
	int request_uri_len;
	char request_uri[DISPATCH_REQUEST_QUERY_LEN];
	int request_method_len;
	char request_method[5];
	int request_body_len;
	char request_body[DISPATCH_REQUEST_BODY_LEN];
	int user_agent_len;
	char user_agent[DISPATCH_USER_AGENT_LEN];
} HTTPRequest_t;

typedef struct HTTPDispatcher {
	struct HTTPQueue_t queue;
	struct HTTPRequest_t* request[DISPATCH_MAXIMUM_QUEUE_LEN];
} HTTPDispatcher_t;


typedef enum {
	REQUEST_METHOD = 0,
	REQUEST_BODY,
	REQUEST_URI,
	REQUEST_USER_AGENT
} REQUEST_PROPERTY_T;

typedef enum {
	REQUEST_POST = 0,
	REQUEST_GET
} REQUEST_METHOD_T;

int setupDispatcher(HTTPDispatcher_t* dispatcher);
int teardownDispatcher(HTTPDispatcher_t* dispatcher);
int queueRequest(HTTPDispatcher_t* dispatcher, HTTPRequest_t* req);
int destroyRequest(HTTPRequest_t* req);
int flushDispatchQueue(HTTPDispatcher_t* dispatcher);
int setRequestProperty(HTTPRequest_t* request, REQUEST_PROPERTY_T index, const char* value, unsigned int value_len);

HTTPRequest_t* prepareRequest(REQUEST_METHOD_T method);


#endif /* DISPATCH_H */