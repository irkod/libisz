#include "grid.h"
#include "isz/common/common.h"
#include "isz/it/it.h"
#include "isz/i/grid_field.h"
#include "isz/i/grid_line.h"
#include "isz/i/sequence.h"
#include "isz/i/size.h"

ISZ_FAIL_FILE(isz_program_id);

void isz_grid_insert(isz_it_t *field, isz_it_t *left, isz_it_t *up, isz_it_t *down, isz_it_t *right, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	assert(field);
	assert(up);
	assert(left);
	assert(right);
	assert(down);

	isz_grid_field_i_t *field_i = ISZ_IT_GET_I(field, isz_grid_field);

	isz_it_t *lines[isz_orientation_count][isz_direction_count] = { { left, right }, { up, down }};
	
	int o;
	int d;
	
	for(o = 0; o < isz_orientation_count; o++)
		for(d = 0; d < isz_direction_count; d++)
		{
			isz_it_t *line = lines[o][d];

			field_i->set_line(field->obj, line, o, d, ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;

			isz_grid_line_i_t *line_i = ISZ_IT_GET_I(line, isz_grid_line);

			line_i->add_field(line->obj, field, ISZ_DIRECTION_OPPOSITE(d), ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;
		}

	return;
}

void isz_grid_traverse(isz_it_t *first_line, isz_it_t *last_line, isz_direction_t direction, isz_grid_traverse_functors_t *functors, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	isz_it_t *line;
	isz_grid_line_i_t *line_i;

	line = first_line;
	
	line_i = ISZ_IT_GET_I(line, isz_grid_line);
	
	isz_orientation_t orientation = line_i->get_orientation(line->obj, ISZ_FAIL);	
	ISZ_FAIL_RET_CALL_IF;
	
	orientation = ISZ_ORIENTATION_OPPOSITE(orientation);

	for(;;)
	{
		if(functors->line_functor)
		{
			functors->line_functor(line, functors->line_data, ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;
		}

		isz_it_t *list = line_i->get_fields(line->obj, direction, ISZ_FAIL);
		ISZ_FAIL_RET_CALL_IF;
		
		isz_sequence_i_t *list_sequence_i = ISZ_IT_GET_I(list, isz_sequence);

		list_sequence_i->reset(list->obj);

		for(;;)
		{
			isz_it_t *field;
			isz_grid_field_i_t *field_i;

			if(!list_sequence_i->get(list->obj, &field))
			{
				if(functors->back_line_functor)
				{
					functors->back_line_functor(line, functors->back_line_data, ISZ_FAIL);
					ISZ_FAIL_RET_CALL_IF;
				}

				isz_it_t *in_line = line_i->traverse_get_in_line(line->obj, ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;

				line_i->traverse_clear_in_line(line->obj, ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;

				line = in_line;

				if(!line)
					return;

				line_i = ISZ_IT_GET_I(line, isz_grid_line);

				list = line_i->get_fields(line->obj, direction, ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;

				isz_sequence_i_t *list_sequence_i = ISZ_IT_GET_I(list, isz_sequence);

				list_sequence_i->next(list->obj);
				continue;
			}
	
			if(functors->field_functor)
			{
				functors->field_functor(field, functors->field_data, ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;
			}

			field_i = ISZ_IT_GET_I(field, isz_grid_field);

		        isz_it_t *next_line = field_i->get_line(field->obj, orientation, direction, ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;

			isz_grid_line_i_t *next_line_i = ISZ_IT_GET_I(next_line, isz_grid_line);

			size_t count = next_line_i->traverse_get_in_fields_count(next_line->obj, ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;

			++count;

			assert(count);

			next_line_i->traverse_set_in_fields_count(next_line->obj, count, ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;

			isz_it_t *next_line_list = next_line_i->get_fields(next_line->obj, ISZ_DIRECTION_OPPOSITE(direction), ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;

			isz_size_i_t *next_line_list_size_i = ISZ_IT_GET_I(next_line_list, isz_size);

			if(count != next_line_list_size_i->get(next_line_list->obj))
			{
				list_sequence_i->next(list->obj);
				continue;
			}
			else
			{
				next_line_i->traverse_set_in_fields_count(next_line->obj, 0, ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;
				
				next_line_i->traverse_set_in_line(next_line->obj, line, ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;

				line = next_line;
				line_i = ISZ_IT_GET_I(line, isz_grid_line);

				break;
			}
		}
	}
}

