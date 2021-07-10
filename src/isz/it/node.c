#include <assert.h>
#include <stddef.h>
#include "isz/it/node.h"
#include "isz/it/list.h"

void isz_nodeinit(struct isz_node *obj, struct isz_it *it)
{
	assert(obj);
	assert(it);

	obj->next = NULL;
	obj->previous = NULL;
	obj->list = NULL;
	obj->it = it;
}

struct isz_it *isz_nodeget_it(const struct isz_node *obj)
	
{
	assert(obj);
	assert(obj->it);

	return obj->it;
}

void isz_nodeappend(struct isz_node *obj, struct isz_node *next)
{
	assert(obj);
	assert(!obj->next);
	assert(obj->list);
	assert(obj->list->last == obj);

	if(!obj->previous)
	{
		assert(obj->list->first == obj);
	}

	assert(next);
	assert(!next->previous);
	assert(!next->list);

	obj->next = next;
	next->previous = obj;
	next->list = obj->list;

	obj->list->last = next;
	++obj->list->size;

	assert(obj->list->size);
}

struct isz_it *isz_noderemove(struct isz_node *obj)
{
	assert(obj);
	assert(obj->list);

	if(!obj->previous && !obj->next)
	{
		assert(obj->list->size == 1);
	}

	if(!obj->previous)
	{
		assert(obj->list->first == obj);
		
		obj->list->first = obj->next;
	}
	else
		assert(obj->list->first != obj);

	if(!obj->next)	
	{
		assert(obj->list->last == obj);
		
		obj->list->last = obj->previous;
	}
	else
		assert(obj->list->last != obj);

	if(obj->previous)
	{
		assert(obj->previous->next == obj);
		assert(obj->previous->list == obj->list);
		
		obj->previous->next = obj->next;
	}

	if(obj->next)
	{
		assert(obj->next->previous == obj);
		assert(obj->next->list == obj->list);
	
		obj->next->previous = obj->previous;
	}
	
	obj->previous = NULL;
	obj->next = NULL;

	--obj->list->size;

	obj->list = NULL;
	return obj->it;
}

