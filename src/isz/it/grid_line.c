#include "isz/it/grid_line.h"
#include "isz/it/grid_field.h"
#include "isz/it/list.h"
#include "isz/it/text.h"
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
static struct isz_it *isz_dump_i_get(void *vobj, ISZ_FAIL_PARAM);
static enum isz_orientation isz_grid_line_i_get_orientation(void *vobj, ISZ_FAIL_PARAM);
static void isz_grid_line_i_add_field(void *vobj, struct isz_it *field, enum isz_direction direction, ISZ_FAIL_PARAM);
static struct isz_it *isz_grid_line_i_get_fields(void *vobj, enum isz_direction direction, ISZ_FAIL_PARAM);
static void isz_grid_line_i_traverse_set_in_fields_count(void *vobj, size_t count, ISZ_FAIL_PARAM);
static size_t isz_grid_line_i_traverse_get_in_fields_count(void *vobj, ISZ_FAIL_PARAM);
static void isz_grid_line_i_traverse_set_in_line(void *vobj, struct isz_it *line, ISZ_FAIL_PARAM);
static struct isz_it *isz_grid_line_i_traverse_get_in_line(void *vobj, ISZ_FAIL_PARAM);
static void isz_grid_line_i_traverse_clear_in_line(void *vobj, ISZ_FAIL_PARAM);
static void isz_grid_line_i_set_it(void *vobj, struct isz_it *it, ISZ_FAIL_PARAM);
static struct isz_it *isz_grid_line_i_get_it(void *vobj, ISZ_FAIL_PARAM);

static isz_id_i_t isz_id_interface_value =
{
	isz_id_i_set,
	isz_id_i_get
};

static isz_dump_i_t isz_dump_interface_value =
{
	isz_dump_i_get
};

static isz_grid_line_i_t isz_grid_line_interface_value =
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

ISZ_IT_INTERFACE_TABLE_BEGIN
	ISZ_IT_INTERFACE_TABLE_ENTRY(isz_grid_line)
	ISZ_IT_INTERFACE_TABLE_ENTRY(isz_id)
	ISZ_IT_INTERFACE_TABLE_ENTRY(isz_dump)
ISZ_IT_INTERFACE_TABLE_WITH_CLEAR_END(isz_grid_line);

ISZ_IT_NEW_DEFINE(isz_grid_line);

void isz_grid_line_init(struct isz_grid_line *obj, enum isz_orientation orientation)
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

	struct isz_grid_line *obj = vobj;
	isz_text_clear(&obj->id);
}

void isz_id_i_set(void *vobj, const char *id, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	assert(vobj);
	assert(id);

	struct isz_grid_field *obj = vobj;
	isz_str_owner_i_t *str_owner_i = ISZ_OBJECT_GET_INTERFACE(&obj->id, isz_str_owner);
	str_owner_i->copy(&obj->id, id, ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF;
}

const char *isz_id_i_get(void *vobj)
{
	assert(vobj);
	
	struct isz_grid_field *obj = vobj;
	isz_str_i_t *str_i = ISZ_OBJECT_GET_INTERFACE(&obj->id, isz_str);
	return str_i->get(&obj->id);
}

struct isz_it *isz_dump_i_get(void *vobj, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT_VAL(NULL);

	assert(vobj);

	struct isz_grid_line *obj = vobj;

	struct isz_text *text = isz_text_new(ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	const char *id = isz_id_i_get(obj);	
	isz_text_init_mprintf(text, ISZ_FAIL, "isz_grid_line{id=%s", id);
       	isz_str_owner_i_t *str_owner_i = ISZ_OBJECT_GET_INTERFACE(text, isz_str_owner);

	for(int d = 0; d < isz_direction_count; ++d)
	{
		str_owner_i->append(text, d == isz_direction_backward ? " backward={" : " forward={", ISZ_FAIL);
		ISZ_FAIL_RET_CALL_IF_VAL(NULL);

		struct isz_list *fields = &obj->fields[d];
		isz_sequence_i_t *sequence_i = ISZ_OBJECT_GET_INTERFACE(fields, isz_sequence);
		struct isz_it* field;

		int first = 1;

		for(sequence_i->reset(fields);
		    sequence_i->peek(fields, &field);
		    sequence_i->next(fields))
		{
			isz_id_i_t *id_i = ISZ_IT_GET_INTERFACE(field, isz_id);
			struct isz_text field_text;

			isz_text_init_mprintf(&field_text, ISZ_FAIL, first ? "%s" :",%s", id_i->get(ISZ_IT_GET_OBJECT(field)));

			isz_str_i_t *str_i = ISZ_OBJECT_GET_INTERFACE(&field_text, isz_str);
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

enum isz_orientation isz_grid_line_i_get_orientation(void *vobj, ISZ_FAIL_PARAM)
{
	assert(vobj);

	struct isz_grid_line *obj = vobj;
	
	return obj->orientation;
}

void isz_grid_line_i_add_field(void *vobj, struct isz_it *field, enum isz_direction direction, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	assert(vobj);
	assert(field);

	struct isz_grid_line *obj = vobj;

	isz_grid_field_i_t *field_i = ISZ_IT_GET_INTERFACE(field, isz_grid_field);

	isz_list_append(&obj->fields[direction], field_i->get_siblings_node(ISZ_IT_GET_OBJECT(field), obj->orientation, direction, ISZ_FAIL));
	ISZ_FAIL_RET_CALL_IF;
}

struct isz_it *isz_grid_line_i_get_fields(void *vobj, enum isz_direction direction, ISZ_FAIL_PARAM)
{
	assert(vobj);

	struct isz_grid_line *obj = vobj;

	return &obj->fields[direction].isz_it;
}

void isz_grid_line_i_traverse_set_in_fields_count(void *vobj, size_t count, ISZ_FAIL_PARAM)
{
	assert(vobj);
	
	struct isz_grid_line *obj = vobj;

	obj->traverse_in_fields_count = count;
}

size_t isz_grid_line_i_traverse_get_in_fields_count(void *vobj, ISZ_FAIL_PARAM)
{
	assert(vobj);
	
	struct isz_grid_line *obj = vobj;
	
	return obj->traverse_in_fields_count;
}

void isz_grid_line_i_traverse_set_in_line(void *vobj, struct isz_it *line, ISZ_FAIL_PARAM)
{
	assert(vobj);
	
	struct isz_grid_line *obj = vobj;
		
	obj->traverse_in_line = line;
}

struct isz_it *isz_grid_line_i_traverse_get_in_line(void *vobj, ISZ_FAIL_PARAM)
{
	assert(vobj);
	
	struct isz_grid_line *obj = vobj;
	
	return obj->traverse_in_line;
}

void isz_grid_line_i_traverse_clear_in_line(void *vobj, ISZ_FAIL_PARAM)
{
	assert(vobj);
	
	struct isz_grid_line *obj = vobj;
	
	obj->traverse_in_line = NULL;
}
