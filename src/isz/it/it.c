#include <stdlib.h>
#include "isz/fail/fail.h"
#include "it.h"

ISZ_FAIL_FILE(isz_program_id);

void 
isz_it_attach(isz_it_t *it, ISZ_FAIL_PARAM) 
{ 
	assert(it); 

	size_t count = it->attach_count + 1;

	if(!count) 
	{ 
		ISZ_FAIL_SET(isz_attach_count_too_big_failure()); 
		return; 
	} 

	it->attach_count = count;
}

void 
isz_it_detach(isz_it_t *it) 
{ 
	assert(it); 
	assert(it->attach_count); 

	if(!--it->attach_count) 
	{ 
		if(it->data->clear)
			it->data->clear(it->obj);

		free(it->obj); 
	}
}

size_t 
isz_it_get_attach_count(const isz_it_t *it)
{ 
	assert(it); 

	return it->attach_count;
}

void *isz_it_get_i(isz_it_t *it, isz_i_id_t *id)
{
	assert(it);
	assert(id);

	isz_i_table_entry_t *entry = it->data->i_table;

	while(entry->id)
	{
		if(entry->id == id)
			return entry->i;
		++entry;
	}

	fprintf(stderr, "Type %s does not implement %s interface\n", it->data->type_name, *id);
	abort();
}
