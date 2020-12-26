#include "uutil.h"

t_point3	rotate_x(t_point3 point, double degree)
{
	double		radian;
	t_point3	result;

	radian = degrees_to_radians(degree);
	result.x = point.x;
	result.y = point.y * cos(radian) + point.z * -sin(radian);
	result.z = point.y * sin(radian) + point.z * cos(radian);
	return (result);
}

t_point3	rotate_y(t_point3 point, double degree)
{
	double		radian;
	t_point3	result;

	radian = degrees_to_radians(degree);
	result.x = point.x * cos(radian) + point.z * sin(radian);
	result.y = point.y;
	result.z = point.x * -sin(radian) + point.z * cos(radian);
	return (result);
}

t_point3	rotate_z(t_point3 point, double degree)
{
	double		radian;
	t_point3	result;

	radian = degrees_to_radians(degree);
	result.x = point.x * cos(radian) + point.y * -sin(radian);
	result.y = point.x * sin(radian) + point.y * cos(radian);
	result.z = point.z;
	return (result);
}

void	rotate_v(t_point3 *point, t_rotate rotate) // rotate에 문제가 있는듯.
{
	*point = rotate_x(*point, rotate.x);
	*point = rotate_y(*point, rotate.y);
	*point = rotate_z(*point, rotate.z);
}

void	rotate_iv(t_point3 *point, t_rotate rotate)
{
	*point = rotate_z(*point, rotate.z);
	*point = rotate_y(*point, rotate.y);
	*point = rotate_x(*point, rotate.x);
}