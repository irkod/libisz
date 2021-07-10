#ifndef ISZ_COMMON_COMMON_H
#define ISZ_COMMON_COMMON_H

enum isz_orientation
{
	isz_orientation_horizontal,
	isz_orientation_vertical,
	isz_orientation_count
};

#define ISZ_ORIENTATION_OPPOSITE(v) (1 - (v))

enum isz_direction
{
	isz_direction_backward,
	isz_direction_forward,
	isz_direction_count
};

#define ISZ_DIRECTION_OPPOSITE(v) (1 - (v))

enum isz_side
{
	isz_side_none = 0,
	isz_side_up_left = 1,
	isz_side_up = 2,
	isz_side_up_right = 4,
	isz_side_right = 8,
	isz_side_down_right = 16,
	isz_side_down = 32,
	isz_side_down_left = 64,
	isz_side_left = 128,
	isz_side_all_up = isz_side_up_left + isz_side_up + isz_side_up_right,
	isz_side_all_right = isz_side_up_right + isz_side_right + isz_side_down_right,
	isz_side_all_down = isz_side_down_right + isz_side_down + isz_side_down_left,
	isz_side_all_left = isz_side_down_left + isz_side_left + isz_side_up_left,
	isz_side_all = isz_side_up_left + isz_side_up + isz_side_up_right +
	       	       isz_side_right + isz_side_down_right + isz_side_down + isz_side_down_left + isz_side_left
};

#endif /* !ISZ_COMMON_COMMON_H */
