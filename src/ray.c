#include "ray.h"

t_ray ray(t_point3 orig, t_vec dir)
{
	t_ray r;
	r.orig = orig;
	r.dir = dir;
	return (r);
}

t_vec ray_at(t_ray ray, double t)
{
	return (vplus(vmult(ray.dir, t), ray.orig));
}