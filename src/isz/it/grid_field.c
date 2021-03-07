#include <stddef.h>
#include <assert.h>
#include "isz/it/grid_field.h"
#include "isz/it/it.h"
#include "isz/it/node.h"
#include "isz/it/text.h"
#include "isz/fail/fail.h"
#include "isz/i/id.h"
#include "isz/i/dump.h"
#include "isz/i/str.h"
#include "isz/i/str_owner.h"
#include "isz/i/grid_field.h"

ISZ_FAIL_FILE(isz_program_id);

static void isz_id_i_set(void *vobj, const char *id, ISZ_FAIL_PARAM);
static const char *isz_id_i_get(void *vobj);
static isz_it_t *isz_dump_i_get(void *vobj, ISZ_FAIL_PARAM);
static void isz_grid_field_i_set_line(void *vobj, isz_it_t *line, isz_orientation_t orientation, isz_direction_t direction, ISZ_FAIL_PARAM);
static isz_it_t *isz_grid_field_i_get_line(void *vobj, isz_orientation_t orientation, isz_direction_t direction, ISZ_FAIL_PARAM);
static isz_node_t *isz_grid_field_i_get_siblings_node(void *vobj, isz_orientation_t orientation, isz_direction_t direction, ISZ_FAIL_PARAM);
static void isz_grid_field_i_set_it(void *vobj, isz_it_t *it, ISZ_FAIL_PARAM);
static isz_it_t *isz_grid_field_i_get_it(void *vobj, ISZ_FAIL_PARAM);

static isz_id_i_t isz_id_i_value =
{
	isz_id_i_set,
	isz_id_i_get
};

static isz_dump_i_t isz_dump_i_value =
{
	isz_dump_i_get
};

static isz_grid_field_i_t isz_grid_field_i_value =
{
	isz_grid_field_i_set_line,
	isz_grid_field_i_get_line,
	isz_grid_field_i_get_siblings_node,
};

ISZ_I_TABLE_BEGIN
	ISZ_I_ENTRY(isz_grid_field)
	ISZ_I_ENTRY(isz_id)
	ISZ_I_ENTRY(isz_dump)
ISZ_I_TABLE_CLEARED_END(isz_grid_field)

ISZ_IT_NEW_DEF(isz_grid_field);

void isz_grid_field_init(isz_grid_field_t *obj)
{
	assert(obj);

	ISZ_IT_INIT(obj);

	int o;
	int d;

	isz_text_init_look(&obj->id, "");

	for(o = 0; o < isz_orientation_count; o++)
		for(d = 0; d < isz_direction_count; d++)
		{
			obj->line[o][d] = NULL;
			isz_node_init(&obj->siblings_node[o][d], &obj->isz_it);
		}
}

void isz_grid_field_clear(void *vobj)
{
	assert(vobj);

	isz_grid_field_t *obj = vobj;
	isz_text_clear(&obj->id);
}

void isz_id_i_set(void *vobj, const char *id, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	assert(vobj);
	assert(id);

	isz_grid_field_t *obj = vobj;
	isz_str_owner_i_t *str_owner_i = ISZ_OBJ_GET_I(&obj->id, isz_str_owner);
	str_owner_i->copy(&obj->id, id, ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF;
}
const char *isz_id_i_get(void *vobj)
{
	assert(vobj);
	
	isz_grid_field_t *obj = vobj;
	isz_str_i_t *str_i = ISZ_OBJ_GET_I(&obj->id, isz_str);
	return str_i->get(&obj->id);
}

isz_it_t *isz_dump_i_get(void *vobj, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT_VAL(NULL);

	assert(vobj);

	isz_grid_field_t *obj = vobj;

	isz_text_t *text = isz_text_new(ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	isz_str_i_t *str_i;

	const char *line_id[isz_orientation_count][isz_direction_count];

	for(int o = 0; o < isz_orientation_count; ++o)
		for(int d = 0; d < isz_direction_count; ++d)
		{
			isz_it_t *line = obj->line[o][d];
			isz_id_i_t *id_i = ISZ_IT_GET_I(line, isz_id);
			line_id[o][d] = id_i->get(ISZ_OBJ(line));
		}

	const char *id = isz_id_i_get(obj);
	
	isz_text_init_mprintf(text, ISZ_FAIL, 
		"isz_grid_field{id=%s left=%s up=%s down=%s right=%s}",
       		id, 
		line_id[isz_horizontal][isz_backward],
		line_id[isz_vertical][isz_backward],
		line_id[isz_vertical][isz_forward],
		line_id[isz_horizontal][isz_forward]);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	return ISZ_IT(text);
}
static void isz_grid_field_i_set_line(void *vobj, isz_it_t *line, isz_orientation_t orientation, isz_direction_t direction, ISZ_FAIL_PARAM)
{
	assert(vobj);

	isz_grid_field_t *obj = vobj;
	
	obj->line[orientation][direction] = line;
}


isz_it_t *isz_grid_field_i_get_line(void *vobj, isz_orientation_t orientation, isz_direction_t direction, ISZ_FAIL_PARAM)
{
	assert(vobj);

	isz_grid_field_t *obj = vobj;
	
	return obj->line[orientation][direction];
}

isz_node_t *isz_grid_field_i_get_siblings_node(void *vobj, isz_orientation_t orientation, isz_direction_t direction, ISZ_FAIL_PARAM)
{
	assert(vobj);

	isz_grid_field_t *obj = vobj;
	
	return &obj->siblings_node[orientation][direction];
}
