#include "camera.h"

void	set_viewport(t_std_set *s_set, int width, int height)
{
	dprintf(2, "width:%d\n", width);
	s_set->width = width;
	s_set->height = height;
}

void	set_amblight(t_std_set *s_set, double lighting_ratio, t_color color)
{
	s_set->color = color;
	s_set->amb_light = lighting_ratio;
}

int set_camera(t_camera *camera, t_std_set *s_set, t_point3 lookfrom, t_vec w, double fov)
{
	double	ratio;
	t_vec	u;
	t_vec	v;
	t_vec	vup;

	ratio = (double)s_set->width / s_set->height;
	camera->focal_len = 1;
	camera->viewport_h = 2 * tan(degrees_to_radians(fov) / 2) * camera->focal_len;
	camera->viewport_w = 2 * tan(degrees_to_radians(fov) / 2) * camera->focal_len;

	vup = vec3(0, 1, 0);
	w = vunit(w);
	u = vunit(vcross(vup, w));
	v = vcross(w, u);
	camera->origin = lookfrom;
	camera->horizontal = vmult(u, camera->viewport_w);
	camera->vertical = vmult(v, camera->viewport_h);
	camera->higher_left_corner = vminus(vplus(vminus(camera->origin, 
			vdivide(camera->horizontal, 2)), vdivide(camera->vertical, 2)), w);
	return (1);
}

int	set_camera2(t_camera *camera, t_point3 lookfrom, t_vec w)
{
	t_vec	u;
	t_vec	v;
	t_vec	vup;

	vup = vec3(0, 1, 0);
	u = vunit(vcross(vup, w));
	v = vcross(w, u);
	camera->origin = lookfrom;
	camera->horizontal = vmult(u, camera->viewport_w);
	camera->vertical = vmult(v, camera->viewport_h);
	camera->higher_left_corner = vminus(vplus(vminus(camera->origin, 
			vdivide(camera->horizontal, 2)), vdivide(camera->vertical, 2)), w);
	return (1);
}