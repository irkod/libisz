#ifndef ISZ_IT_LIST_H
#define ISZ_IT_LIST_H

#include <stddef.h>
#include "isz/it/node.h"
#include "isz/it/it.h"

typedef struct isz_list_t_
{
	isz_node_t *first;
	isz_node_t *last;
	isz_node_t *sequence;
	size_t size;
	ISZ_IT_MEMBER;
} isz_list_t;

void isz_list_init(isz_list_t *obj);
void isz_list_append(isz_list_t *obj, isz_node_t *node);
size_t isz_list_get_size(isz_list_t *obj);
void isz_list_clear(void *vobj);
ISZ_IT_NEW_DECL(isz_list);

#endif /* ISZ_IT_LIST_H */
