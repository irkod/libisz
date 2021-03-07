#include "isz/it/grid_line.h"
#include "isz/it/grid_field.h"
#include "isz/it/list.h"
#include "isz/it/it.h"
#include "isz/i/id.h"
#include "isz/i/dump.h"
#include "isz/i/grid_field.h"
#include "isz/i/grid_line.h"
#include "isz/i/str.h"
#include "isz/i/str_owner.h"
#include "isz/i/sequence.h"
#include <stddef.h>
#include <assert.h>

ISZ_FAIL_FILE(isz_program_id);

static void isz_id_i_set(void *vobj, const char *id, ISZ_FAIL_PARAM);
static const char *isz_id_i_get(void *vobj);
static isz_it_t *isz_dump_i_get(void *vobj, ISZ_FAIL_PARAM);
static isz_orientation_t isz_grid_line_i_get_orientation(void *vobj, ISZ_FAIL_PARAM);
static void isz_grid_line_i_add_field(void *vobj, isz_it_t *field, isz_direction_t direction, ISZ_FAIL_PARAM);
static isz_it_t *isz_grid_line_i_get_fields(void *vobj, isz_direction_t direction, ISZ_FAIL_PARAM);
static void isz_grid_line_i_traverse_set_in_fields_count(void *vobj, size_t count, ISZ_FAIL_PARAM);
static size_t isz_grid_line_i_traverse_get_in_fields_count(void *vobj, ISZ_FAIL_PARAM);
static void isz_grid_line_i_traverse_set_in_line(void *vobj, isz_it_t *line, ISZ_FAIL_PARAM);
static isz_it_t *isz_grid_line_i_traverse_get_in_line(void *vobj, ISZ_FAIL_PARAM);
static void isz_grid_line_i_traverse_clear_in_line(void *vobj, ISZ_FAIL_PARAM);
static void isz_grid_line_i_set_it(void *vobj, isz_it_t *it, ISZ_FAIL_PARAM);
static isz_it_t *isz_grid_line_i_get_it(void *vobj, ISZ_FAIL_PARAM);

static isz_id_i_t isz_id_i_value =
{
	isz_id_i_set,
	isz_id_i_get
};

static isz_dump_i_t isz_dump_i_value =
{
	isz_dump_i_get
};

static isz_grid_line_i_t isz_grid_line_i_value =
{
	isz_grid_line_i_get_orientation,
	isz_grid_line_i_add_field,
	isz_grid_line_i_get_fields,
	isz_grid_line_i_traverse_set_in_fields_count,
	isz_grid_line_i_traverse_get_in_fields_count,
	isz_grid_line_i_traverse_set_in_line,
	isz_grid_line_i_traverse_get_in_line,
	isz_grid_line_i_traverse_clear_in_line,
};

ISZ_I_TABLE_BEGIN
	ISZ_I_ENTRY(isz_grid_line)
	ISZ_I_ENTRY(isz_id)
	ISZ_I_ENTRY(isz_dump)
ISZ_I_TABLE_CLEARED_END(isz_grid_line)

ISZ_IT_NEW_DEF(isz_grid_line);

void isz_grid_line_init(isz_grid_line_t *obj, isz_orientation_t orientation)
{
	assert(obj);

	ISZ_IT_INIT(obj);

	isz_text_init_look(&obj->id, "");
	obj->orientation = orientation;

	int i;

	for(i = 0; i < isz_direction_count; i++)
		isz_list_init(&obj->fields[i]);

	obj->traverse_in_fields_count = 0;
	obj->traverse_in_line = NULL;
}

void isz_grid_line_clear(void *vobj)
{
	assert(vobj);

	isz_grid_line_t *obj = vobj;
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

	isz_grid_line_t *obj = vobj;

	isz_text_t *text = isz_text_new(ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	const char *id = isz_id_i_get(obj);	
	isz_text_init_mprintf(text, ISZ_FAIL, "isz_grid_line{id=%s", id);
       	isz_str_owner_i_t *str_owner_i = ISZ_OBJ_GET_I(text, isz_str_owner);

	for(int d = 0; d < isz_direction_count; ++d)
	{
		str_owner_i->append(text, d == isz_backward ? " backward={" : " forward={", ISZ_FAIL);
		ISZ_FAIL_RET_CALL_IF_VAL(NULL);

		isz_list_t *fields = &obj->fields[d];
		isz_sequence_i_t *sequence_i = ISZ_OBJ_GET_I(fields, isz_sequence);
		isz_it_t* field;

		int first = 1;

		for(sequence_i->reset(fields);
		    sequence_i->peek(fields, &field);
		    sequence_i->next(fields))
		{
			isz_id_i_t *id_i = ISZ_IT_GET_I(field, isz_id);
			isz_text_t field_text;

			isz_text_init_mprintf(&field_text, ISZ_FAIL, first ? "%s" :",%s", id_i->get(ISZ_OBJ(field)));

			isz_str_i_t *str_i = ISZ_OBJ_GET_I(&field_text, isz_str);
			str_owner_i->append(text, str_i->get(&field_text), ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF_VAL(NULL);

			isz_text_clear(&field_text);
			first = 0;
		}
		
		str_owner_i->append(text, "}", ISZ_FAIL);
		ISZ_FAIL_RET_CALL_IF_VAL(NULL);
	}

	str_owner_i->append(text, "}", ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	return ISZ_IT(text);
}

isz_orientation_t isz_grid_line_i_get_orientation(void *vobj, ISZ_FAIL_PARAM)
{
	assert(vobj);

	isz_grid_line_t *obj = vobj;
	
	return obj->orientation;
}

void isz_grid_line_i_add_field(void *vobj, isz_it_t *field, isz_direction_t direction, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	assert(vobj);
	assert(field);

	isz_grid_line_t *obj = vobj;

	isz_grid_field_i_t *field_i = ISZ_IT_GET_I(field, isz_grid_field);

	isz_list_append(&obj->fields[direction], field_i->get_siblings_node(ISZ_OBJ(field), obj->orientation, direction, ISZ_FAIL));
	ISZ_FAIL_RET_CALL_IF;
}

isz_it_t *isz_grid_line_i_get_fields(void *vobj, isz_direction_t direction, ISZ_FAIL_PARAM)
{
	assert(vobj);

	isz_grid_line_t *obj = vobj;

	return &obj->fields[direction].isz_it;
}

void isz_grid_line_i_traverse_set_in_fields_count(void *vobj, size_t count, ISZ_FAIL_PARAM)
{
	assert(vobj);
	
	isz_grid_line_t *obj = vobj;

	obj->traverse_in_fields_count = count;
}

size_t isz_grid_line_i_traverse_get_in_fields_count(void *vobj, ISZ_FAIL_PARAM)
{
	assert(vobj);
	
	isz_grid_line_t *obj = vobj;
	
	return obj->traverse_in_fields_count;
}

void isz_grid_line_i_traverse_set_in_line(void *vobj, isz_it_t *line, ISZ_FAIL_PARAM)
{
	assert(vobj);
	
	isz_grid_line_t *obj = vobj;
		
	obj->traverse_in_line = line;
}

isz_it_t *isz_grid_line_i_traverse_get_in_line(void *vobj, ISZ_FAIL_PARAM)
{
	assert(vobj);
	
	isz_grid_line_t *obj = vobj;
	
	return obj->traverse_in_line;
}

void isz_grid_line_i_traverse_clear_in_line(void *vobj, ISZ_FAIL_PARAM)
{
	assert(vobj);
	
	isz_grid_line_t *obj = vobj;
	
	obj->traverse_in_line = NULL;
}
