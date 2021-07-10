#include <stdlib.h>
#include "isz/fail/fail.h"
#include "it.h"

ISZ_FAIL_FILE(isz_program_id);

void 
isz_it_attach(struct isz_it *it, ISZ_FAIL_PARAM) 
{ 
	assert(it); 

	size_t count = it->attach_count + 1;

	if(!count) 
	{ 
		ISZ_FAIL_SET(isz_fail_attach_count_too_big_failure()); 
		return; 
	} 

	it->attach_count = count;
}

void 
isz_it_detach(struct isz_it *it) 
{ 
	assert(it); 
	assert(it->attach_count); 

	if(!--it->attach_count) 
	{ 
		if(it->data->clear)
			it->data->clear(it->object);

		free(it->object); 
	}
}

size_t 
isz_it_get_attach_count(const struct isz_it *it)
{ 
	assert(it); 

	return it->attach_count;
}

void *isz_it_get_interface(struct isz_it *it, isz_it_interface_id_t *id)
{
	assert(it);
	assert(id);

	struct isz_it_interface_table_entry *entry = it->data->interface_table;

	while(entry->id)
	{
		if(entry->id == id)
			return entry->interface;
		++entry;
	}

	fprintf(stderr, "Type %s does not implement %s interface\n", it->data->type_name, *id);
	abort();
}
