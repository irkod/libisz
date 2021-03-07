#ifndef ISZ_COMMON_COMMON_H
#define ISZ_COMMON_COMMON_H

typedef enum isz_orientation_t_
{
	isz_horizontal,
	isz_vertical,
	isz_orientation_count
} isz_orientation_t;

#define ISZ_ORIENTATION_OPPOSITE(v) (1 - (v))

typedef enum isz_direction_t_
{
	isz_backward,
	isz_forward,
	isz_direction_count
} isz_direction_t;

#define ISZ_DIRECTION_OPPOSITE(v) (1 - (v))

typedef enum isz_side_t_
{
	isz_side_none = 0,
	isz_up_left = 1,
	isz_up = 2,
	isz_up_right = 4,
	isz_right = 8,
	isz_down_right = 16,
	isz_down = 32,
	isz_down_left = 64,
	isz_left = 128,
	isz_all_up = isz_up_left + isz_up + isz_up_right,
	isz_all_right = isz_up_right + isz_right + isz_down_right,
	isz_all_down = isz_down_right + isz_down + isz_down_left,
	isz_all_left = isz_down_left + isz_left + isz_up_left,
	isz_side_all = isz_up_left + isz_up + isz_up_right + isz_right + isz_down_right + isz_down + isz_down_left + isz_left
} isz_side_t;
#endif /* !ISZ_COMMON_COMMON_H */
