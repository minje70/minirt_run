/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:27:46 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 16:10:43 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

void	set_sphere_disc(t_sphere *sphere, t_ray *r, t_hit_disc *disc)
{
	disc->oc = vminus(r->orig, sphere->center);
	disc->a = vdot(r->dir, r->dir);
	disc->half_b = vdot(disc->oc, r->dir);
	disc->c = vdot(disc->oc, disc->oc) - sphere->radius * sphere->radius;
	disc->discriminant = disc->half_b * disc->half_b - disc->a * disc->c;
}

t_bool	hit_sphere(t_sphere *sphere, t_ray *r, t_hitrec *rec)
{
	t_hit_disc	disc;
	double		sqrtd;
	double		root;

	set_sphere_disc(sphere, r, &disc);
	if (disc.discriminant < 0)
		return (0);
	sqrtd = sqrt(disc.discriminant);
	root = (-disc.half_b - sqrtd) / disc.a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-disc.half_b + sqrtd) / disc.a;
		if (root < rec->tmin || root > rec->tmax)
			return (0);
	}
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	rec->normal = vdivide(vminus(rec->p, sphere->center), sphere->radius);
	rec->obj_color = sphere->obj_color;
	set_face_normal(r, rec);
	rec->texture = *sphere->texture;
	get_sphere_uv(rec);
	return (1);
}

t_bool	hit_plane(t_plane *plane, t_ray *r, t_hitrec *rec)
{
	double	root;

	root = vdot(vminus(plane->p, r->orig), plane->normal) /
			vdot(plane->normal, r->dir);
	if (root < 0)
		return (0);
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	rec->normal = plane->normal;
	rec->obj_color = plane->color;
	rec->texture = *plane->texture;
	set_face_normal(r, rec);
	return (1);
}

t_bool	hit(t_ray *r, t_hitrec *rec, t_objects *object)
{
	t_hitrec	temp_rec;
	t_bool		hit_anything;
	double		closest_so_far;

	closest_so_far = rec->tmax;
	hit_anything = 0;
	temp_rec = *rec;
	while (object)
	{
		if (object_hit(r, &temp_rec, object))
		{
			hit_anything = 1;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
			rec->obj = object;
		}
		object = object->next;
	}
	return (hit_anything);
}

t_bool	object_hit(t_ray *r, t_hitrec *rec, t_objects *object)
{
	t_bool	result;

	if (object->type == SP)
		result = hit_sphere(object->data, r, rec);
	else if (object->type == PL)
		result = check_pl_rotate(object, rec, r);
	else if (object->type == TR)
		result = check_tr_rotate(object, rec, r);
	else if (object->type == CY)
		result = check_cy_rotate(object, rec, r);
	else if (object->type == SQ)
		result = check_sq_rotate(object, rec, r);
	else if (object->type == CU)
		result = check_cu_rotate(object, rec, r);
	else if (object->type == PY)
		result = check_py_rotate(object, rec, r);
	else
		result = 0;
	return (result);
}
