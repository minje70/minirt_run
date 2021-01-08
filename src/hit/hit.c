/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:27:01 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 20:04:41 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

t_bool	hit_triangle(t_triangle *tri, t_ray *r, t_hitrec *rec)
{
	double	root;
	t_vec	temp;

	root = vdot(vminus(tri->p1, r->orig), tri->normal) / vdot(tri->normal,
			r->dir);
	if (root < 0)
		return (0);
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	temp = ray_at(*r, root);
	if (!is_inside(tri, temp))
		return (0);
	rec->t = root;
	rec->p = temp;
	rec->normal = tri->normal;
	rec->obj_color = tri->color;
	rec->texture = *tri->texture;
	set_face_normal(r, rec);
	return (1);
}

void	set_face_normal(t_ray *r, t_hitrec *rec)
{
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	rec->normal = rec->front_face ? rec->normal : vmult(rec->normal, -1);
}

t_color	hit_parallel_light(t_hitrec *rec, t_objects *obj, t_vec n,
				t_camera *camera)
{
	t_color	ambient;
	t_color	diff;
	t_color	specular;
	t_light	light;
	t_vec	light_dir;

	n = vunit(n);
	light.color = color(1, 1, 1);
	ambient = vmult(light.color, 0.1);
	diff = vmult(light.color, max_d(vdot(rec->normal, vunit(vmult(n, -1))),
			0.0));
	specular = parallel_specular_color(n, rec, camera);
	if (!shadow_parallel_color(&n, obj, rec))
		return (vmult_(vplus(vplus(ambient, diff), specular), albedo(rec)));
	return (color(0, 0, 0));
}

t_bool	hit_light_sub(t_hitrec *rec, t_objects *obj, t_camera *camera,
						t_color *result)
{
	t_color		amb_diff_spec;
	t_objects	*temp_obj;
	double		distance_attenuation;

	temp_obj = obj;
	distance_attenuation = 1 / (vlength2(vminus((
			(t_light *)obj->data)->point, rec->p)) + 1);
	amb_diff_spec = vplus(vplus(ambient_color(obj->data, 0.1),
					diff_color(obj->data, rec)),
					specular_color(obj->data, rec, camera));
	if (!shadow_color(obj->data, temp_obj, rec) || rec->texture.type
		== SKY_BOX)
	{
		if (rec->texture.type == SKY_BOX)
		{
			*result = albedo(rec);
			return (1);
		}
		*result = vplus(*result, vmult(vmult_(amb_diff_spec, albedo(rec))
			, distance_attenuation));
	}
	return (0);
}

t_color	hit_light(t_hitrec *rec, t_objects *obj, t_camera *camera)
{
	t_color		result;

	rec->tmax = INFINITY;
	rec->tmin = 0.001;
	result = hit_parallel_light(rec, obj, vec3(-0.5, -1, 0.5), camera);
	while (obj)
	{
		if (obj->type == LI)
		{
			if (hit_light_sub(rec, obj, camera, &result))
				return (result);
		}
		obj = obj->next;
	}
	return (result);
}
