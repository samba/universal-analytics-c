

#ifndef DATALAYER_MAX_LEN
#define DATALAYER_MAX_LEN 50
#endif

#define DATALAYER_MAX_ATTRIBUTE_LEN 25

typedef struct DataLayer_Pair {
	char* name;
	char* value;
} DataLayer_Pair_t;

typedef DataLayer_Event {
	char* event_name;
	DataLayer_Pair_t* attributes[DATALAYER_MAX_ATTRIBUTE_LEN];
} DataLayer_Event_t;

typedef struct DataLayer_Queue {
	DataLayer_Event_t* stack[DATALAYER_MAX_LEN];
} DataLayer_Queue_t;
