#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include "isz/isz.h"
//#include "pri/pri.h"

const char *main_text_program_id = "main_text";
ISZ_FAIL_FILE(main_text_program_id);

void print_field(isz_it_t *it, void *data, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	//isz_id_i_t *id = ISZ_IT_GET_I(it, isz_id, ISZ_FAIL);
	printf("pole\n");
}

void print_line(isz_it_t *it, void *data, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	//isz_id_i_t *id = it->i->get_i(it->obj, &isz_id_i_id, ISZ_FAIL);
	printf("linia\n");
}

void print_back_line(isz_it_t *it, void *data, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	//isz_id_i_t *id = it->i->get_i(it->obj, &isz_id_i_id, ISZ_FAIL);
	printf("powrot\n");
}
/*
typedef struct expand_data_t_
{
	isz_orientation_t o;
	isz_direction_t d;
} expand_data_t;

typedef struct paint_data_t_
{
	isz_it_t *canvas;
} paint_data_t;

void expand_field(isz_it_t *it, void *data, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	expand_data_t *ed = data;
	
	isz_grid_field_i_t *grid_field_i = ISZ_IT_GET_I(it, isz_grid_field, ISZ_FAIL);
	isz_it_t *pri_field_it = grid_field_i->get_it(ISZ_OBJ(it), ISZ_FAIL);

	pri_field_i_t *pri_field_i = ISZ_IT_GET_I(pri_field_it, pri_field, ISZ_FAIL)		
	pri_field_i->expand(ISZ_OBJ(pri_field_it), ed->o, ed->d, ISZ_FAIL);
}
void paint_field(isz_it_t *it, void *data, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	paint_data_t *pd = data;
	
	pri_field_i_t *field_i = ISZ_IT_GET_I(it, pri_field, ISZ_FAIL);
	field_i->paint(ISZ_OBJ(it), pd->canvas, ISZ_FAIL);
}
isz_grid_traverse_functors_t ff = 
{
	print_field, NULL,
	print_line, NULL,
	print_back_line, NULL
};

expand_data_t edh = { isz_horizontal, isz_forward };
expand_data_t edv = { isz_vertical, isz_forward };

isz_grid_traverse_functors_t ff2 = 
{
	expand_field, &edh,
	NULL, NULL,
	NULL, NULL
};
isz_grid_traverse_functors_t ff3 = 
{
	expand_field, &edv,
	NULL, NULL,
	NULL, NULL
};
*/

isz_grid_line_t *line_new(isz_orientation_t o, char *s, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT_VAL(NULL);

	isz_grid_line_t *line = isz_grid_line_new(ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	isz_grid_line_init(line, o);
	isz_id_i_t *id_i = ISZ_OBJ_GET_I(line, isz_id);
	id_i->set(line, s, ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	return line;
}
isz_grid_field_t *field_new(char *s, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT_VAL(NULL);

	isz_grid_field_t *field = isz_grid_field_new(ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	isz_grid_field_init(field);
	isz_id_i_t *id_i = ISZ_OBJ_GET_I(field, isz_id);
	id_i->set(field, s, ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	return field;
}

void dump(isz_it_t *it, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	isz_dump_i_t *isz_dump_i = ISZ_IT_GET_I(it, isz_dump);
	isz_it_t* dump = isz_dump_i->get(ISZ_OBJ(it), ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF;

	isz_str_i_t *isz_str_i = ISZ_IT_GET_I(dump, isz_str);
	printf("%s\n", isz_str_i->get(ISZ_OBJ(dump)));
	ISZ_IT_DETACH(dump);

}
int main()
{
	ISZ_FAIL_ROOT;
	ISZ_FAIL_NEXT_VAL(0);

	//setlocale(LC_ALL, "");
	//printf("%d, mbrlen = %d\n", MB_CUR_MAX, mblen("ą", 10));

	isz_grid_line_t *l_u, *l_l, *l_r, *l_d, *l_h1, *l_h2, *l_h3, *l_v1, *l_v2;

	l_u = line_new(isz_horizontal, "l_u", ISZ_FAIL);
	l_h1 = line_new(isz_horizontal, "l_h1", ISZ_FAIL);
	l_h2 = line_new(isz_horizontal, "l_h2", ISZ_FAIL);
	l_h3 = line_new(isz_horizontal, "l_h3", ISZ_FAIL);
	l_d = line_new(isz_horizontal, "l_d", ISZ_FAIL);

	l_l = line_new(isz_vertical, "l_l", ISZ_FAIL);
	l_v1 = line_new(isz_vertical, "l_v1", ISZ_FAIL);
	l_v2 = line_new(isz_vertical, "l_v2", ISZ_FAIL);
	l_r = line_new(isz_vertical, "l_r", ISZ_FAIL);

	isz_grid_field_t *f_a, *f_b, *f_c, *f_d, *f_e, *f_f;
	
	f_a = field_new("f_a", ISZ_FAIL);
	f_b = field_new("f_b", ISZ_FAIL);
	f_c = field_new("f_c", ISZ_FAIL);
	f_d = field_new("f_d", ISZ_FAIL);
	f_e = field_new("f_e", ISZ_FAIL);
	f_f = field_new("f_f", ISZ_FAIL);

	isz_grid_insert(ISZ_IT(f_a), ISZ_IT(l_l),  ISZ_IT(l_u),  ISZ_IT(l_h1), ISZ_IT(l_v1), ISZ_FAIL);
	isz_grid_insert(ISZ_IT(f_b), ISZ_IT(l_v1), ISZ_IT(l_u),  ISZ_IT(l_h1), ISZ_IT(l_v2), ISZ_FAIL);
	isz_grid_insert(ISZ_IT(f_c), ISZ_IT(l_l),  ISZ_IT(l_h1), ISZ_IT(l_h2), ISZ_IT(l_v2), ISZ_FAIL);
	isz_grid_insert(ISZ_IT(f_d), ISZ_IT(l_l),  ISZ_IT(l_h2), ISZ_IT(l_d),  ISZ_IT(l_v2), ISZ_FAIL);
	isz_grid_insert(ISZ_IT(f_e), ISZ_IT(l_v2), ISZ_IT(l_u),  ISZ_IT(l_h3), ISZ_IT(l_r),  ISZ_FAIL);
	isz_grid_insert(ISZ_IT(f_f), ISZ_IT(l_v2), ISZ_IT(l_h3), ISZ_IT(l_d),  ISZ_IT(l_r),  ISZ_FAIL);
	
	/*
	printf("UD\n");
	isz_grid_traverse(ISZ_IT(l_u), ISZ_IT(l_d), isz_forward, &ff, ISZ_FAIL);
	printf("DU\n");
	isz_grid_traverse(ISZ_IT(l_d), ISZ_IT(l_u), isz_backward, &ff, ISZ_FAIL);
	printf("LR\n");
	isz_grid_traverse(ISZ_IT(l_l), ISZ_IT(l_r), isz_forward, &ff, ISZ_FAIL);
	printf("RL\n");
	isz_grid_traverse(ISZ_IT(l_r), ISZ_IT(l_l), isz_backward, &ff, ISZ_FAIL);

	isz_grid_traverse(ISZ_IT(l_l), ISZ_IT(l_r), isz_forward, &ff2, ISZ_FAIL);
	*/


	dump(ISZ_IT(f_a), ISZ_FAIL);
	dump(ISZ_IT(f_b), ISZ_FAIL);
	dump(ISZ_IT(f_c), ISZ_FAIL);
	dump(ISZ_IT(f_d), ISZ_FAIL);
	dump(ISZ_IT(f_e), ISZ_FAIL);
	dump(ISZ_IT(f_f), ISZ_FAIL);

	dump(ISZ_IT(l_u), ISZ_FAIL);
	dump(ISZ_IT(l_h1), ISZ_FAIL);
	dump(ISZ_IT(l_h2), ISZ_FAIL);
	dump(ISZ_IT(l_h3), ISZ_FAIL);
	dump(ISZ_IT(l_d), ISZ_FAIL);
	
	dump(ISZ_IT(l_l), ISZ_FAIL);
	dump(ISZ_IT(l_v1), ISZ_FAIL);
	dump(ISZ_IT(l_v2), ISZ_FAIL);
	dump(ISZ_IT(l_r), ISZ_FAIL);

	ISZ_OBJ_DETACH(l_u);
	ISZ_OBJ_DETACH(l_h1);
	ISZ_OBJ_DETACH(l_h2);
	ISZ_OBJ_DETACH(l_h3);
	ISZ_OBJ_DETACH(l_d);
	ISZ_OBJ_DETACH(l_l);
	ISZ_OBJ_DETACH(l_v1);
	ISZ_OBJ_DETACH(l_v2);
	ISZ_OBJ_DETACH(l_r);
	ISZ_OBJ_DETACH(f_a);
	ISZ_OBJ_DETACH(f_b);
	ISZ_OBJ_DETACH(f_c);
	ISZ_OBJ_DETACH(f_d);
	ISZ_OBJ_DETACH(f_e);
	ISZ_OBJ_DETACH(f_f);
	ISZ_FAIL_PRINT(stdout);
	
	ISZ_FAIL_ROOT_FREE;
	return 0;
}
