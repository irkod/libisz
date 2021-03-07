#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "isz/isz.h"

const char *program_id = "main_list";
ISZ_FAIL_FILE(program_id);

void dump(isz_list_t *obj);
void dump2(isz_list_t *obj, ISZ_FAIL_PARAM);
void dump3(isz_it_t *t, ISZ_FAIL_PARAM);

int main()
{
	ISZ_FAIL_ROOT;
	ISZ_FAIL_NEXT_VAL(0);

	isz_list_t l;
	isz_list_init(&l);

	isz_text_t *t1 = isz_text_new(ISZ_FAIL);
	isz_text_init_copy(t1, "ala1", ISZ_FAIL);

	isz_text_t *t2 = isz_text_new(ISZ_FAIL);
	isz_text_init_copy(t2, "ala2", ISZ_FAIL);
	
	isz_text_t *t3 = isz_text_new(ISZ_FAIL);
	isz_text_init_copy(t3, "ala3", ISZ_FAIL);

	isz_node_t n1;
	isz_node_init(&n1, &t1->isz_it);

	isz_node_t n2;
	isz_node_init(&n2, &t2->isz_it);

	isz_node_t n3;
	isz_node_init(&n3, &t3->isz_it);


	isz_list_append(&l, &n1);
	dump3(&l.isz_it, ISZ_FAIL);
	
	isz_list_append(&l, &n2);
	dump3(&l.isz_it, ISZ_FAIL);
	
	isz_list_append(&l, &n3);
	dump3(&l.isz_it, ISZ_FAIL);

	isz_keeper_i_t *keeper_i = ISZ_OBJ_GET_I(&l, isz_keeper);
	keeper_i->clear(l.isz_it.obj);

/*
	isz_node_remove(&n2);
	dump3(&l.isz_it);
	
	isz_node_remove(&n1);
	dump3(&l.isz_it);

	isz_node_remove(&n3);
	dump3(&l.isz_it);
*/
	ISZ_FAIL_PRINT(stdout);
	ISZ_FAIL_ROOT_FREE;
	return 0;	
}

void dump(isz_list_t *obj)
{
	isz_node_t *n = obj->first;


	printf ("{\n");

	while(n)
	{
		printf("%d %d %d\n", n->previous, n, n->next);
		n = n->next;
	}
	
	printf ("}\n");
}

void dump3(isz_it_t *t, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	isz_sequence_i_t *sequence_i = ISZ_IT_GET_I(t, isz_sequence);
	sequence_i->reset(t->obj);

	
	isz_size_i_t *size_i = ISZ_IT_GET_I(t, isz_size);
	printf ("%d {\n", size_i->get(t->obj));

	isz_it_t *it;

	while(sequence_i->get(t->obj, &it))
	{
		isz_str_i_t *str_i = ISZ_IT_GET_I(it, isz_str);
		printf("%s\n", str_i->get(it->obj));
		sequence_i->next(t->obj);
	}

	printf ("}\n");
}
