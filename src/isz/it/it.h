#ifndef ISZ_IT_THING_H
#define ISZ_IT_THING_H

#include <malloc.h>
#include <stddef.h>

struct isz_fail_node_t_;

typedef const char *isz_i_id_t;

typedef struct isz_i_table_entry_t_
{
	isz_i_id_t *id;
	void *i;
} isz_i_table_entry_t;

typedef struct isz_it_data_t_
{
	const char *type_name;
	isz_i_table_entry_t *i_table;
	void (*clear)(void *obj);
} isz_it_data_t;

typedef struct isz_it_t_
{
	void *obj;
	isz_it_data_t *data; 
	size_t attach_count; 
} isz_it_t;

void isz_it_attach(isz_it_t *it, struct isz_fail_node_t_ *isz_fail_node);
void isz_it_detach(isz_it_t *it);
size_t isz_it_get_attach_count(const isz_it_t *it);
void *isz_it_get_i(isz_it_t *it, isz_i_id_t *id);

typedef void (*isz_it_functor_t)(isz_it_t *it, void *data, struct isz_fail_node_t_ *isz_fail_node);

#define ISZ_IT_MEMBER \
	isz_it_t isz_it

#define ISZ_IT(object) \
(&(object)->isz_it)	

#define ISZ_OBJ(it) \
((it)->obj)	

#define ISZ_I_ID_DECL(interface) \
extern isz_i_id_t interface ## _i_id

#define ISZ_I_ID_DEF(interface) \
isz_i_id_t interface ## _i_id = #interface

#define ISZ_I_TABLE_BEGIN \
static isz_i_table_entry_t isz_i_table[] = \
{

#define ISZ_I_ENTRY(interface) \
{ &interface ## _i_id, &interface ## _i_value },

#define ISZ_I_TABLE_END(type) \
{ NULL, NULL } \
}; \
\
static isz_it_data_t isz_it_data_value = { #type, isz_i_table, NULL };

#define ISZ_I_TABLE_CLEARED_END(type) \
{ NULL, NULL } \
}; \
\
static isz_it_data_t isz_it_data_value = { #type, isz_i_table, type ## _clear };

#define ISZ_IT_GET_I(it, interface) \
isz_it_get_i(it, &interface ## _i_id); \

#define ISZ_OBJ_GET_I(object, interface) \
ISZ_IT_GET_I(&(object)->isz_it, interface)

#define ISZ_IT_ATTACH(it, fail) \
isz_it_attach(it, fail)

#define ISZ_OBJ_ATTACH(object, fail) \
ISZ_IT_ATTACH(&(object)->isz_it, fail)

#define ISZ_IT_DETACH(it) \
isz_it_detach(it)

#define ISZ_OBJ_DETACH(object) \
ISZ_IT_DETACH(&(object)->isz_it)

#define ISZ_IT_NEW_DECL(t) \
t ## _t *t ## _new(struct isz_fail_node_t_ *isz_fail_node)

#define ISZ_IT_NEW_DEF(t) \
t ## _t *t ## _new(ISZ_FAIL_PARAM) \
{ \
	ISZ_FAIL_NEXT_VAL(NULL); \
\
	t ## _t *obj = malloc(sizeof(t ## _t)); \
\
	if(!obj) \
	{ \
		ISZ_FAIL_SET(isz_malloc_failure()); \
		return NULL; \
	} \
\
	obj->isz_it.attach_count = 1; \
	return obj; \
}

#define ISZ_IT_INIT(obj) \
do \
{ \
	obj->isz_it.obj = obj; \
	obj->isz_it.data = &isz_it_data_value; \
} while(0);


#endif /* !ISZ_IT_THING_H */
