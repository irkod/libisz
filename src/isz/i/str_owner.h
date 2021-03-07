#ifndef ISZ_I_STR_OWNER_H
#define ISZ_I_STR_OWNER_H

#include "isz/it/it.h"

struct isz_fail_node_t_;

extern isz_i_id_t isz_str_owner_i_id;

typedef struct isz_str_owner_i_t_
{
	int (*owns)(void *vobj);
	void (*look)(void *vobj, char *str);
	void (*take)(void *vobj, char *str);
	void (*copy)(void *vobj, const char *str, struct isz_fail_node_t_ *isz_fail_node);
	void (*append)(void *vobj, const char *str, struct isz_fail_node_t_ *isz_fail_node);
} isz_str_owner_i_t;

#endif /* !ISZ_I_STR_OWNER_H */
