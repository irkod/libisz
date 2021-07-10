
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stddef.h>
#include <stdarg.h>
#include "isz/it/text.h"
#include "isz/it/it.h"
#include "isz/function/mprintf.h"
#include "isz/i/str.h"
#include "isz/i/str_owner.h"

ISZ_FAIL_FILE(isz_program_id);

static char *isz_str_i_get(void *vobj);
static int isz_str_owner_i_owns(void *vobj);
static void isz_str_owner_i_look(void *vobj, char *str);
static void isz_str_owner_i_take(void *vobj, char *str);
static void isz_str_owner_i_copy(void *vobj, const char *str, ISZ_FAIL_PARAM);
static void isz_str_owner_i_append(void *vobj, const char *str, ISZ_FAIL_PARAM);

static isz_str_i_t isz_str_interface_value =
{
	isz_str_i_get
};

static isz_str_owner_i_t isz_str_owner_interface_value =
{
	isz_str_owner_i_owns,
	isz_str_owner_i_look,
	isz_str_owner_i_take,
	isz_str_owner_i_copy,
	isz_str_owner_i_append
};

ISZ_IT_INTERFACE_TABLE_BEGIN
	ISZ_IT_INTERFACE_TABLE_ENTRY(isz_str)
	ISZ_IT_INTERFACE_TABLE_ENTRY(isz_str_owner)
ISZ_IT_INTERFACE_TABLE_WITH_CLEAR_END(isz_text);

ISZ_IT_NEW_DEFINE(isz_text);

void isz_text_init_look(struct isz_text *obj, char *str)
{
	assert(obj);
	assert(str);

	ISZ_IT_INIT(obj);
	obj->str = str;
	obj->owns = 0;
}

void isz_text_init_take(struct isz_text *obj, char *str)
{
	assert(obj);
	assert(str);

	ISZ_IT_INIT(obj);
	obj->str = str;
	obj->owns = 1;
}
void isz_text_init_copy(struct isz_text *obj, const char *str, ISZ_FAIL_PARAM)
{
	char *new_str;
	assert(obj);
	assert(str);

	ISZ_IT_INIT(obj);

	size_t size = strlen(str) + 1;

	assert(size);

	new_str = malloc(size);

	if(!new_str)
	{
		ISZ_FAIL_SET(isz_fail_malloc_failure());
		return;
	}

	strcpy(new_str, str);
	obj->str = new_str;
	obj->owns = 1;
}

void isz_text_init_mprintf(struct isz_text *obj, ISZ_FAIL_PARAM, const char *format, ...)
{
	assert(obj);
	assert(format);

	ISZ_IT_INIT(obj);

	va_list ap;
	char *str;
	size_t size;
	
	va_start(ap, format);
	size = isz_vmprintf_size(format, ap);
	va_end(ap);		

	va_start(ap, format);
	str = isz_vmprintf_str(format, size, ap);
	va_end(ap);		

	if(!str)
	{
		ISZ_FAIL_SET(isz_fail_malloc_failure());
		return;
	}	

	isz_text_init_take(obj, str);
}

void isz_text_clear(void *vobj)
{
	assert(vobj);

	struct isz_text *obj = vobj;

	if(obj->owns)
	{
		free(obj->str);
		obj->owns = 0;
	}
	
	obj->str = "";
}

char *isz_str_i_get(void *vobj)
{
	assert(vobj);

	struct isz_text *obj = vobj;

	return obj->str;
}

int isz_str_owner_i_owns(void *vobj)
{
	assert(vobj);

	struct isz_text *obj = vobj;
	return obj->owns;
}

void isz_str_owner_i_look(void *vobj, char *str)
{
	assert(vobj);
	assert(str);

	struct isz_text *obj = vobj;
	
	if(obj->owns)
		free(obj->str);

	isz_text_init_look(obj, str);
}
void isz_str_owner_i_take(void *vobj, char *str)
{
	assert(vobj);
	assert(str);

	struct isz_text *obj = vobj;
	
	if(obj->owns)
		free(obj->str);

	isz_text_init_take(obj, str);
}

void isz_str_owner_i_copy(void *vobj, const char *str, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	assert(vobj);
	assert(str);

	struct isz_text *obj = vobj;
	
	if(obj->owns)
		free(obj->str);

	isz_text_init_copy(obj, str, ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF;
}

void isz_str_owner_i_append(void *vobj, const char *str, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	assert(vobj);
	assert(str);

	struct isz_text *obj = vobj;

	size_t my_size = strlen(obj->str);
	size_t str_size = strlen(str);

	if((size_t)-2 - my_size < str_size)
	{
		ISZ_FAIL_SET(isz_fail_malloc_failure());
		return;
	}

	char *new_str = malloc(my_size + str_size + 1);

	if(!new_str)
	{
		ISZ_FAIL_SET(isz_fail_malloc_failure());
		return;
	}

	strcpy(new_str, obj->str);
	strcat(new_str, str);

	if(obj->owns)
		free(obj->str);

	obj->str = new_str;
	obj->owns = 1;
}
