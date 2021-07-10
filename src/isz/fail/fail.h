#ifndef ISZ_FAIL_FAIL_H
#define ISZ_FAIL_FAIL_H

#include <stdio.h>
#include <assert.h>
#include "isz/it/it.h"

typedef const char *isz_fail_program_id_t;

typedef struct isz_fail_file_t_
{
	isz_fail_program_id_t *program_id;
	const char *file_name;
} isz_fail_file_t;

typedef struct isz_fail_failure_t_
{
	const char *id;
	const char *message;
} isz_fail_failure_t;

typedef struct isz_fail_failure_and_details_t_
{
	isz_fail_failure_t *failure;
	struct isz_it *details;
} isz_fail_failure_and_details_t;

typedef struct isz_fail_node_t_ isz_fail_node_t;

struct isz_fail_node_t_{
	isz_fail_file_t *file;
	const char *function_name;
	int line;
	isz_fail_failure_t *failure;
	struct isz_it *details;
	isz_fail_node_t *next;
};

void isz_fail_node_init(isz_fail_node_t *obj);
void isz_fail_node_erase(isz_fail_node_t *obj);
void isz_fail_set(isz_fail_node_t *obj, isz_fail_file_t *file, const char *function_name, int line, isz_fail_failure_and_details_t fad);
int isz_fail_node_append(isz_fail_node_t *obj);
void isz_fail_node_clear(isz_fail_node_t *obj);
void isz_fail_nodes_clear(isz_fail_node_t *obj);
void isz_fail_nodes_free(isz_fail_node_t *obj);
void isz_fail_nodes_print(isz_fail_node_t *obj, FILE *file);

extern isz_fail_program_id_t isz_program_id;

#define ISZ_FAIL_PARAM isz_fail_node_t *isz_fail_node

#define ISZ_FAIL isz_fail_node->next

#define ISZ_FAIL_FILE(program_id) \
static isz_fail_file_t isz_fail_file = \
	{ &program_id, __FILE__ }

#define ISZ_FAIL_FAILURE(name, id, message) \
static isz_fail_failure_t isz_fail_local_ ## name ## _failure = \
	{ id, message }

#define ISZ_FAIL_NEXT \
do \
{ \
	assert(isz_fail_node); \
\
	if(!isz_fail_node->next) \
		if(!isz_fail_node_append(isz_fail_node)) \
			return; \
} while(0)

#define ISZ_FAIL_NEXT_VAL(val) \
do \
{ \
	assert(isz_fail_node); \
\
	if(!isz_fail_node->next) \
		if(!isz_fail_node_append(isz_fail_node)) \
			return (val); \
} while(0)

#define ISZ_FAIL_ROOT \
isz_fail_node_t isz_fail_root_node; \
isz_fail_node_t *isz_fail_node = &isz_fail_root_node; \
isz_fail_node_init(isz_fail_node)

#define ISZ_FAIL_ROOT_FREE \
isz_fail_nodes_free(isz_fail_root_node.next)

#define ISZ_FAIL_IF \
	if(isz_fail_node->next->file) 

#define ISZ_FAIL_SET(fad) \
	isz_fail_set(isz_fail_node, &isz_fail_file, __func__, __LINE__, fad) 

#define ISZ_FAIL_SET_CALL_IF \
do \
{ \
	assert(isz_fail_node); \
\
	if(isz_fail_node->next->file) \
	{ \
		ISZ_FAIL_SET(isz_fail_call_failure()); \
	} \
} while(0)

#define ISZ_FAIL_RET_CALL_IF \
do \
{ \
	assert(isz_fail_node); \
\
	if(isz_fail_node->next->file) \
	{ \
		ISZ_FAIL_SET(isz_fail_call_failure()); \
		return; \
	} \
} while(0)

#define ISZ_FAIL_RET_CALL_IF_VAL(r) \
do \
{ \
	assert(isz_fail_node); \
\
	if(isz_fail_node->next->file) \
	{ \
		ISZ_FAIL_SET(isz_fail_call_failure()); \
		return (r); \
	} \
} while(0)


#define ISZ_FAIL_PRINT(file) \
isz_fail_nodes_print(isz_fail_node, file)

#define ISZ_FAIL_CLEAR \
isz_fail_nodes_clear(isz_fail_node)

isz_fail_failure_and_details_t isz_fail_call_failure();
isz_fail_failure_and_details_t isz_fail_malloc_failure();
isz_fail_failure_and_details_t isz_fail_errno_failure(int error);
isz_fail_failure_and_details_t isz_fail_attach_count_too_big_failure();
isz_fail_failure_and_details_t isz_fail_mb_failure();
isz_fail_failure_and_details_t isz_fail_mb_cur_max_failure();
isz_fail_failure_and_details_t isz_fail_no_interface_failure(isz_it_interface_id_t *id);

#endif /* !ISZ_FAIL_FAIL_H */
