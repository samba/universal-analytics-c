/******************************************************************************
* Dispatch layer for Universal Analytics for C 
* Copyright (c) 2013, Analytics Pros
* 
* This project is free software, distributed under the BSD license. 
* Analytics Pros offers consulting and integration services if your firm needs 
* assistance in strategy, implementation, or auditing existing work.
******************************************************************************/

#include "dispatcher.h"
#include "http.h"

HTTPRequest_t* prepareRequest(REQUEST_METHOD_T method){
	HTTPRequest_t* req = malloc(sizeof(HTTPRequest_t));
	memset(req, 0, sizeof(HTTPRequest_t));
	switch(method){
		case REQUEST_POST: 
			setRequestProperty(req, REQUEST_METHOD, "POST", 4);
			break;
		case REQUEST_GET:
			setRequestProperty(req, REQUEST_METHOD, "GET", 3);
	}
	
	return req;
}

int setRequestProperty(HTTPRequest_t* req, REQUEST_PROPERTY_T index, const char* value, unsigned int value_len){
	switch(index){
		case REQUEST_METHOD: 
			strncpy(req->request_method, value, value_len);
			req->request_method_len = value_len;
			return 0;
		case REQUEST_BODY:
			strncpy(req->request_body, value, value_len);
			req->request_body_len = value_len;
			return 0;
		case REQUEST_URI:
			strncpy(req->request_uri, value, value_len);
			req->request_uri_len = value_len;
			return 0;
		case REQUEST_USER_AGENT:
			strncpy(req->user_agent, value, value_len);
			req->user_agent_len = value_len;
			return 0;
	}
}

int teardownDispatcher(HTTPDispatcher_t* dispatcher){
	memset(dispatcher, 0, sizeof(HTTPDispatcher_t));
	free(dispatcher);
	return 0;
}

int destroyRequest(HTTPRequest_t* req){
	memset(req, 0, sizeof(HTTPRequest_t));
	free(req);
	return 0;
}

// At the moment this is a thin wrapper over our CURL abstraction
int setupDispatcher(HTTPDispatcher_t* dispatcher){
	memset(dispatcher, 0, sizeof(HTTPDispatcher_t));
	HTTPsetup(& dispatcher->queue);
	return 0;
}

// At the moment this is a thin wrapper over our CURL abstraction
int queueRequest(HTTPDispatcher_t* dispatcher, HTTPRequest_t* req){
	return HTTPenqueue(& dispatcher->queue, req->request_uri, req->user_agent, req->request_body, req->request_body_len);
}

int flushDispatchQueue(HTTPDispatcher_t* dispatcher){
	HTTPflush(& dispatcher->queue);
	return 0;
}