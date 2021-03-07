#ifndef ISZ_IT_NODE_H
#define ISZ_IT_NODE_H

#include "isz/it/it.h"

struct isz_list_t_;

typedef struct isz_node_t_
{
	struct isz_node_t_ *next;
	struct isz_node_t_ *previous;
	struct isz_list_t_ *list;
	isz_it_t *it;
} isz_node_t;

void isz_node_init(isz_node_t *obj, isz_it_t *it);
isz_it_t *isz_node_get_it(const isz_node_t *obj);
void isz_node_append(isz_node_t *obj, isz_node_t *next);
isz_it_t *isz_node_remove(isz_node_t *obj);

#endif /* !ISZ_IT_NODE_H */
