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

t_color ray_color(t_ray *r, t_objects *object, t_camera camera, int light_on)
{
	t_hitrec rec;

	rec.tmin = 0.001;
	rec.tmax = infinity;
    if (hit(r, &rec, object))
	{
		if (light_on == LIGHT_ON)
        	return (hit_light(&rec, object, &camera));
		else if (light_on == RAINBOW)
			return (draw_rainbow(&rec));
		else
			return (rec.obj_color);
	}
	return (color(0.1, 0.1, 0.1));
}