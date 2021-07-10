#ifndef ISZ_IT_LIST_H
#define ISZ_IT_LIST_H

#include <stddef.h>
#include "isz/it/node.h"
#include "isz/it/it.h"

struct isz_list
{
	struct isz_node *first;
	struct isz_node *last;
	struct isz_node *sequence;
	size_t size;
	ISZ_IT_MEMBER;
};

void isz_list_init(struct isz_list *obj);
void isz_list_append(struct isz_list *obj, struct isz_node *node);
size_t isz_list_get_size(struct isz_list *obj);
void isz_list_clear(void *vobj);
ISZ_IT_NEW_DECLARE(isz_list);

#endif /* ISZ_IT_LIST_H */
