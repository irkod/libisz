#include "grid.h"
#include "isz/common/common.h"
#include "isz/it/it.h"
#include "isz/i/grid_field.h"
#include "isz/i/grid_line.h"
#include "isz/i/sequence.h"
#include "isz/i/size.h"

ISZ_FAIL_FILE(isz_program_id);

void isz_grid_insert(struct isz_it *field, struct isz_it *left, struct isz_it *up, struct isz_it *down, struct isz_it *right, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	assert(field);
	assert(up);
	assert(left);
	assert(right);
	assert(down);

	isz_grid_field_i_t *field_i = ISZ_IT_GET_INTERFACE(field, isz_grid_field);

	struct isz_it *lines[isz_orientation_count][isz_direction_count] = { { left, right }, { up, down }};
	
	int o;
	int d;
	
	for(o = 0; o < isz_orientation_count; o++)
		for(d = 0; d < isz_direction_count; d++)
		{
			struct isz_it *line = lines[o][d];

			field_i->set_line(ISZ_IT_GET_OBJECT(field), line, o, d, ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;

			isz_grid_line_i_t *line_i = ISZ_IT_GET_INTERFACE(line, isz_grid_line);

			line_i->add_field(ISZ_IT_GET_OBJECT(line), field, ISZ_DIRECTION_OPPOSITE(d), ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;
		}

	return;
}

void isz_grid_traverse(struct isz_it *first_line, struct isz_it *last_line,
	               enum isz_direction direction, isz_grid_traverse_functors_t *functors, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	struct isz_it *line;
	isz_grid_line_i_t *line_i;

	line = first_line;
	
	line_i = ISZ_IT_GET_INTERFACE(line, isz_grid_line);
	
	enum isz_orientation orientation = line_i->get_orientation(ISZ_IT_GET_OBJECT(line), ISZ_FAIL);	
	ISZ_FAIL_RET_CALL_IF;
	
	orientation = ISZ_ORIENTATION_OPPOSITE(orientation);

	for(;;)
	{
		if(functors->line_functor)
		{
			functors->line_functor(line, functors->line_data, ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;
		}

		struct isz_it *list = line_i->get_fields(ISZ_IT_GET_OBJECT(line), direction, ISZ_FAIL);
		ISZ_FAIL_RET_CALL_IF;
		
		isz_sequence_i_t *list_sequence_i = ISZ_IT_GET_INTERFACE(list, isz_sequence);

		list_sequence_i->reset(ISZ_IT_GET_OBJECT(list));

		for(;;)
		{
			struct isz_it *field;
			isz_grid_field_i_t *field_i;

			if(!list_sequence_i->peek(ISZ_IT_GET_OBJECT(list), &field))
			{
				if(functors->back_line_functor)
				{
					functors->back_line_functor(line, functors->back_line_data, ISZ_FAIL);
					ISZ_FAIL_RET_CALL_IF;
				}

				struct isz_it *in_line = line_i->traverse_get_in_line(ISZ_IT_GET_OBJECT(line), ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;

				line_i->traverse_clear_in_line(ISZ_IT_GET_OBJECT(line), ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;

				line = in_line;

				if(!line)
					return;

				line_i = ISZ_IT_GET_INTERFACE(line, isz_grid_line);

				list = line_i->get_fields(ISZ_IT_GET_OBJECT(line), direction, ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;

				isz_sequence_i_t *list_sequence_i = ISZ_IT_GET_INTERFACE(list, isz_sequence);

				list_sequence_i->next(ISZ_IT_GET_OBJECT(list));
				continue;
			}
	
			if(functors->field_functor)
			{
				functors->field_functor(field, functors->field_data, ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;
			}

			field_i = ISZ_IT_GET_INTERFACE(field, isz_grid_field);

		        struct isz_it *next_line = field_i->get_line(ISZ_IT_GET_OBJECT(field), orientation, direction, ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;

			isz_grid_line_i_t *next_line_i = ISZ_IT_GET_INTERFACE(next_line, isz_grid_line);

			size_t count = next_line_i->traverse_get_in_fields_count(ISZ_IT_GET_OBJECT(next_line), ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;

			++count;

			assert(count);

			next_line_i->traverse_set_in_fields_count(ISZ_IT_GET_OBJECT(next_line), count, ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;

			struct isz_it *next_line_list = next_line_i->get_fields(ISZ_IT_GET_OBJECT(next_line), ISZ_DIRECTION_OPPOSITE(direction), ISZ_FAIL);
			ISZ_FAIL_RET_CALL_IF;

			isz_size_i_t *next_line_list_size_i = ISZ_IT_GET_INTERFACE(next_line_list, isz_size);

			if(count != next_line_list_size_i->get(ISZ_IT_GET_OBJECT(next_line_list)))
			{
				list_sequence_i->next(ISZ_IT_GET_OBJECT(list));
				continue;
			}
			else
			{
				next_line_i->traverse_set_in_fields_count(ISZ_IT_GET_OBJECT(next_line), 0, ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;
				
				next_line_i->traverse_set_in_line(ISZ_IT_GET_OBJECT(next_line), line, ISZ_FAIL);
				ISZ_FAIL_RET_CALL_IF;

				line = next_line;
				line_i = ISZ_IT_GET_INTERFACE(line, isz_grid_line);

				break;
			}
		}
	}
}

