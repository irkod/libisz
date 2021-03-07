#include <assert.h>
#include <stddef.h>
#include "isz/it/list.h"
#include "isz/it/node.h"
#include "isz/i/sequence.h"
#include "isz/i/size.h"
#include "isz/i/keeper.h"
#include "isz/fail/fail.h"

ISZ_FAIL_FILE(isz_program_id);

static void isz_sequence_i_reset(void *vobj);
static int isz_sequence_i_get(void *vobj, isz_it_t **it);
static void isz_sequence_i_next(void *vobj);
static size_t isz_size_i_get(void *vobj);
static void isz_keeper_i_add(void *vobj, isz_node_t *node, ISZ_FAIL_PARAM);
static void isz_keeper_i_clear(void *vobj);

static isz_sequence_i_t isz_sequence_i_value =
{
	isz_sequence_i_reset,
	isz_sequence_i_get,
	isz_sequence_i_next
};

static isz_size_i_t isz_size_i_value =
{
	isz_size_i_get
};

static isz_keeper_i_t isz_keeper_i_value =
{
	isz_keeper_i_add,
	isz_keeper_i_clear
};

ISZ_I_TABLE_BEGIN
	ISZ_I_ENTRY(isz_sequence)
	ISZ_I_ENTRY(isz_size)
	ISZ_I_ENTRY(isz_keeper)
ISZ_I_TABLE_CLEARED_END(isz_list)

void isz_list_init(isz_list_t *obj)
{
	assert(obj);

	ISZ_IT_INIT(obj);
	obj->first = NULL;	
	obj->last = NULL;
	obj->sequence = NULL;
	obj->size = 0;	
}

void isz_list_clear(void *vobj)
{
	assert(vobj);

	isz_list_t *obj = vobj;

	while(obj->first)
		isz_node_remove(obj->first);
}

void isz_list_append(isz_list_t *obj, isz_node_t *node)
{
	assert(obj);
	assert(node);

	if(!obj->size)
	{
		assert(!obj->first);
		assert(!obj->last);

		obj->first = node;
		obj->last = node;
		node->list = obj;
		obj->size = 1;
	}
	else
	{
		assert(obj->first);
		assert(obj->last);

		isz_node_append(obj->last, node);
	}

	assert(obj->size);
}

size_t isz_list_da_get_size(isz_list_t *obj)
{
	assert(obj);

	return obj->size;
}

void isz_sequence_i_reset(void *vobj)
{
	assert(vobj);

	isz_list_t *obj = vobj;
	
	obj->sequence = obj->first;
}

int isz_sequence_i_get(void *vobj, isz_it_t **it)
{
	assert(vobj);
	
	isz_list_t *obj = vobj;

	if(!obj->sequence)
		return 0;
	
	*it = obj->sequence->it;
	return 1;
}

void isz_sequence_i_next(void *vobj)
{
	assert(vobj);

	isz_list_t *obj = vobj;

	if(obj->sequence)
		obj->sequence = obj->sequence->next;

}

size_t isz_size_i_get(void *vobj)
{
	assert(vobj);
	isz_list_t *obj = vobj;

	return obj->size;
}

void isz_keeper_i_add(void *vobj, isz_node_t *node, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	assert(vobj);
	assert(node);

	isz_it_t *it = isz_node_get_it(node);
	
	ISZ_IT_ATTACH(it, ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF;

	isz_list_t *obj = vobj;

	isz_list_append(obj, node);
}

void isz_keeper_i_clear(void *vobj)
{
	assert(vobj);

	isz_list_t *obj = vobj;

	while(obj->first)
	{
		isz_it_t *it = isz_node_remove(obj->first);
		
		assert(it);

		ISZ_IT_DETACH(it);
	}
}
