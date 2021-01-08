/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:41:36 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 13:36:19 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

t_color	ambient_color(t_light *light, double ambient_strength)
{
	return (vmult(light->color, ambient_strength));
}

t_color	diff_color(t_light *light, t_hitrec *rec)
{
	t_color	result;

	result = vmult(light->color, max_d(vdot(rec->normal,
			vunit(vminus(light->point, rec->p))), 0.0));
	return (result);
}

t_color	specular_color(t_light *light, t_hitrec *rec, t_camera *camera)
{
	double	spec;
	double	specular_strength;
	t_vec	view_dir;
	t_vec	reflect_dir;
	t_vec	temp;

	specular_strength = 0.5;
	view_dir = vunit(vminus(camera->origin, rec->p));
	temp = vminus(rec->p, light->point);
	reflect_dir = vunit(vplus(temp, vmult(rec->normal, -2 *
				vdot(temp, rec->normal))));
	spec = pow(max_d(vdot(view_dir, reflect_dir), 0.0), 256);
	return (vmult(light->color, specular_strength * spec));
}

t_bool	shadow_parallel_color(t_vec *light_dir, t_objects *obj, t_hitrec *rec)
{
	t_ray		r;
	t_hitrec	temp_rec;

	r.orig = rec->p;
	r.dir = vmult(*light_dir, -1);
	r.dir = vunit(r.dir);
	temp_rec.tmax = INFINITY;
	temp_rec.tmin = 0.0001;
	if (hit(&r, &temp_rec, obj))
		return (1);
	return (0);
}

t_bool	shadow_color(t_light *light, t_objects *obj, t_hitrec *rec)
{
	t_ray		r;
	t_hitrec	temp_rec;

	r.orig = rec->p;
	r.dir = vminus(light->point, rec->p);
	temp_rec.tmax = r.dir.x;
	r.dir = vunit(r.dir);
	temp_rec.tmax /= r.dir.x;
	temp_rec.tmin = 0.0001;
	if (hit(&r, &temp_rec, obj))
		return (1);
	return (0);
}
