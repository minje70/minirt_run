#include "lighting.h"

t_light *set_light(t_color color, t_point3 point)
{
	t_light *light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (0);
	light->color = color;
	light->point = point;
	return (light);
}

t_color ambient_color(t_light *light, double ambient_strength)
{
	return (vmult(light->color, ambient_strength));
}

t_color diff_color(t_light *light, t_hitrec *rec)
{
	t_color result;

	result = vmult(light->color, max_d(vdot(rec->normal, vunit(vminus(light->point, rec->p))), 0.0));
	return (result);
}

t_color specular_color(t_light *light, t_hitrec *rec, t_camera *camera)
{
	double spec;
	double specular_strength;
	t_vec view_dir;
	t_vec reflect_dir;
	t_vec temp;

	specular_strength = 0.5;
	// dprintf(2, "camera->origin:%f, %f, %f\nrec->p:%f, %f, %f\n", camera->origin.x, camera->origin.y, camera->origin.z, rec->p.x, rec->p.y, rec->p.z);

	view_dir = vunit(vminus(camera->origin, rec->p));
	temp = vminus(rec->p, light->point);
	reflect_dir = vunit(vplus(temp, vmult(rec->normal, -2 * vdot(temp, rec->normal))));
	spec = pow(max_d(vdot(view_dir, reflect_dir), 0.0), 256);
	// dprintf(2, "view: %f, %f, %f\nreflect: %f, %f, %f\n", view_dir.x, view_dir.y, view_dir.z, reflect_dir.x, reflect_dir.y, reflect_dir.z);
	// dprintf(2, "vdot(view_dir, reflect_dir)%f\n", vdot(view_dir, reflect_dir));
	return (vmult(light->color, specular_strength * spec));
}

t_bool shadow_color(t_light *light, t_objects *obj, t_hitrec *rec, t_camera *camera)
{
	t_ray r;
	t_hitrec temp_rec;

	r.orig = rec->p;
	r.dir = vminus(light->point, rec->p);
	temp_rec.tmin = 0.001;
	temp_rec.tmax = r.dir.x / r.dir.x;
	// temp_rec.tmax = vlength(r.dir); // 광원에서 표면까지의 거리를 넣어주기.
	if (hit(&r, &temp_rec, obj))
		return (1);
	return (0);
}