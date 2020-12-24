#include "uutil.h"

t_point3	rotate_x(t_point3 point, double degree)
{
	double	radian;

	radian = degrees_to_radians(degree);
	point.y = point.y * cos(radian) + point.z * -sin(radian);
	point.z = point.y * sin(radian) + point.z * cos(radian);
	return (point);
}

t_point3	rotate_y(t_point3 point, double degree)
{
	double	radian;

	radian = degrees_to_radians(degree);
	point.x = point.x * cos(radian) + point.z * sin(radian);
	point.z = point.x * -sin(radian) + point.z * cos(radian);
	return (point);
}

t_point3	rotate_z(t_point3 point, double degree)
{
	double	radian;

	radian = degrees_to_radians(degree);
	point.x = point.x * cos(radian) + point.y * -sin(radian);
	point.y = point.x * sin(radian) + point.y * cos(radian);
	return (point);
}

void	rotate_v(t_point3 *point, t_rotate rotate) // rotate에 문제가 있는듯.
{
	*point = rotate_x(*point, rotate.x);
	*point = rotate_y(*point, rotate.y);
	*point = rotate_z(*point, rotate.z);
}