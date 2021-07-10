#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "isz/isz.h"

const char *program_id = "main_list";
ISZ_FAIL_FILE(program_id);

void dump(struct isz_list *obj);
void dump2(struct isz_list *obj, ISZ_FAIL_PARAM);
void dump3(struct isz_it *t, ISZ_FAIL_PARAM);

int main()
{
	ISZ_FAIL_ROOT;
	ISZ_FAIL_NEXT_VAL(0);

	struct isz_list l;
	isz_list_init(&l);

	struct isz_text *t1 = isz_text_new(ISZ_FAIL);
	isz_text_init_copy(t1, "ala1", ISZ_FAIL);

	struct isz_text *t2 = isz_text_new(ISZ_FAIL);
	isz_text_init_copy(t2, "ala2", ISZ_FAIL);
	
	struct isz_text *t3 = isz_text_new(ISZ_FAIL);
	isz_text_init_copy(t3, "ala3", ISZ_FAIL);

	struct isz_node n1;
	isz_nodeinit(&n1, &t1->isz_it);

	struct isz_node n2;
	isz_nodeinit(&n2, &t2->isz_it);

	struct isz_node n3;
	isz_nodeinit(&n3, &t3->isz_it);


	isz_list_append(&l, &n1);
	dump3(&l.isz_it, ISZ_FAIL);
	
	isz_list_append(&l, &n2);
	dump3(&l.isz_it, ISZ_FAIL);
	
	isz_list_append(&l, &n3);
	dump3(&l.isz_it, ISZ_FAIL);

	isz_keeper_i_t *keeper_i = ISZ_OBJECT_GET_INTERFACE(&l, isz_keeper);
	keeper_i->clear(ISZ_IT_GET_OBJECT(&l.isz_it));

/*
	isz_noderemove(&n2);
	dump3(&l.isz_it);
	
	isz_noderemove(&n1);
	dump3(&l.isz_it);

	isz_noderemove(&n3);
	dump3(&l.isz_it);
*/
	ISZ_FAIL_PRINT(stdout);
	ISZ_FAIL_ROOT_FREE;
	return 0;	
}

void dump(struct isz_list *obj)
{
	struct isz_node *n = obj->first;


	printf ("{\n");

	while(n)
	{
		printf("%d %d %d\n", n->previous, n, n->next);
		n = n->next;
	}
	
	printf ("}\n");
}

void dump3(struct isz_it *t, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	isz_sequence_i_t *sequence_i = ISZ_IT_GET_INTERFACE(t, isz_sequence);
	sequence_i->reset(ISZ_IT_GET_OBJECT(t));

	
	isz_size_i_t *size_i = ISZ_IT_GET_INTERFACE(t, isz_size);
	printf("%d {\n", size_i->get(ISZ_IT_GET_OBJECT(t)));

	struct isz_it *it;

	while(sequence_i->peek(ISZ_IT_GET_OBJECT(t), &it))
	{
		isz_str_i_t *str_i = ISZ_IT_GET_INTERFACE(it, isz_str);
		printf("%s\n", str_i->get(ISZ_IT_GET_OBJECT(it)));
		sequence_i->next(ISZ_IT_GET_OBJECT(t));
	}

	printf ("}\n");
}
