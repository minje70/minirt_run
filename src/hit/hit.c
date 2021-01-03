#include "hit.h"

t_bool hit_sphere(t_sphere *sphere, t_ray *r, t_hitrec *rec)
{
	t_vec oc = vminus(r->orig, sphere->center);
	double a = vdot(r->dir, r->dir);
	double half_b = vdot(oc, r->dir);
	double c = vdot(oc, oc) - sphere->radius * sphere->radius;
	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	double sqrtd = sqrt(discriminant);
	double root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (0);
	}
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	rec->normal = vdivide(vminus(rec->p, sphere->center), sphere->radius);
	rec->obj_color = sphere->obj_color;
	// dprintf(2, "r->normal:%f, %f, %f\n", rec->normal.x, rec->normal.y, rec->normal.z);
	set_face_normal(r, rec);
	return (1);
}

t_bool hit_plane(t_plane *plane, t_ray *r, t_hitrec *rec)
{
	double	root;

	root = vdot(vminus(plane->p, r->orig), plane->normal) / vdot(plane->normal, r->dir);
	if (root < 0)
		return (0);
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	rec->normal = plane->normal;
	rec->obj_color = plane->color;
	set_face_normal(r, rec);
	// dprintf(2, "root : %f\n", rec->t);
	return (1);
}
t_bool hit_triangle(t_triangle *tri, t_ray *r, t_hitrec *rec)
{
	double	root;
	t_vec	temp;

	root = vdot(vminus(tri->p1, r->orig), tri->normal) / vdot(tri->normal, r->dir);
	if (root < 0)
	{
		return (0);
	}
	if (root < rec->tmin || root > rec->tmax)
	{
		return (0);
	}
	temp = ray_at(*r, root);
	if (!is_inside(tri, temp))
		return (0);
	rec->t = root;
	rec->p = temp;
	rec->normal = tri->normal;
	rec->obj_color = tri->color;
	set_face_normal(r, rec);
	// rec->p = vplus(rec->p, vmult(rec->normal, 0.0001));
	return (1);
}

void set_face_normal(t_ray *r, t_hitrec *rec)
{
	//  front_face = dot(r.direction(), outward_normal) < 0;
    //     normal = front_face ? outward_normal :-outward_normal;
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	rec->normal = rec->front_face ? rec->normal : vmult(rec->normal, -1);
}

t_color	hit_parallel_light(t_hitrec *rec, t_objects *obj, t_vec n)
{
	t_color	ambient;
	t_color diff;
	t_light	light;
	t_vec	light_dir;

	n = vunit(n);
	light.color = color(1, 1, 1);
	ambient = vmult(light.color, 0.1);
	diff = vmult(light.color, max_d(vdot(rec->normal, vunit(vmult(n, -1))), 0.0));
	if (!shadow_parallel_color(&n, obj, rec))
		return (vmult_(vplus(ambient, diff), rec->obj_color));
	return (color(0, 0, 0));
}

t_color hit_light(t_hitrec *rec, t_objects *obj, t_camera *camera)
{
	t_color result;
	t_color ambient;
	t_color diff;
	t_color specular;
	t_objects *temp_obj;
	double distance_attenuation;

	temp_obj = obj;
	result = color(0, 0, 0);
	rec->tmax = infinity;
	rec->tmin = 0.001;
	result = vplus(result, hit_parallel_light(rec, obj, vec3(-0.5, -1, 0.5)));
	while (obj)
	{
		if (obj->type == LI)
		{
			distance_attenuation = 1 / (vlength2(vminus(((t_light *)obj->data)->point, rec->p)) + 1);
			ambient = ambient_color(obj->data, 0.1);
			diff = diff_color(obj->data, rec);
			specular = specular_color(obj->data, rec, camera);
			if (!shadow_color(obj->data, temp_obj, rec))
				result = vplus(result, vmult(vmult_(vplus(vplus(ambient, diff), specular), rec->obj_color), distance_attenuation));
		}
		obj = obj->next;
	}
	return (result);
}