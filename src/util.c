#include "uutil.h"

double	degrees_to_radians(double degrees)
{
	return degrees * M_PI / 180.0;
}

double	max_d(double d1, double d2)
{
	return (d1 > d2 ? d1 : d2);
}

t_bool	is_inside(t_triangle *tri, t_point3 p)
{
	t_vec	v1;
	t_vec	v2;

	v1 = vcross(vminus(tri->p2, tri->p1), vminus(p, tri->p1));
	v2 = vcross(vminus(tri->p2, tri->p1), vminus(tri->p3, tri->p1));
	if (vdot(v1, v2) < 0)
		return (0);
	v1 = vcross(vminus(tri->p3, tri->p1), vminus(p, tri->p1));
	v2 = vcross(vminus(tri->p3, tri->p1), vminus(tri->p2, tri->p1));
	if (vdot(v1, v2) < 0)
		return (0);
	v1 = vcross(vminus(tri->p2, tri->p3), vminus(p, tri->p3));
	v2 = vcross(vminus(tri->p2, tri->p3), vminus(tri->p1, tri->p3));
	if (vdot(v1, v2) < 0)
		return (0);
	else
		return (1);
}

t_bool	is_inside_(t_point3 p1, t_point3 p2, t_point3 p3, t_point3 p)
{
	t_vec	v1;
	t_vec	v2;

	v1 = vcross(vminus(p2, p1), vminus(p, p1));
	v2 = vcross(vminus(p2, p1), vminus(p3, p1));
	if (vdot(v1, v2) < 0)
		return (0);
	v1 = vcross(vminus(p3, p1), vminus(p, p1));
	v2 = vcross(vminus(p3, p1), vminus(p2, p1));
	if (vdot(v1, v2) < 0)
		return (0);
	v1 = vcross(vminus(p2, p3), vminus(p, p3));
	v2 = vcross(vminus(p2, p3), vminus(p1, p3));
	if (vdot(v1, v2) < 0)
		return (0);
	else
		return (1);
}
