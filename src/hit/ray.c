/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:12:48 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:25:41 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	ray(t_point3 orig, t_vec dir)
{
	t_ray	r;

	r.orig = orig;
	r.dir = dir;
	return (r);
}

t_vec	ray_at(t_ray ray, double t)
{
	return (vplus(vmult(ray.dir, t), ray.orig));
}

t_color	ray_color(t_ray *r, t_objects *object, t_camera camera, int light_on)
{
	t_hitrec rec;

	rec.tmin = 0.001;
	rec.tmax = INFINITY;
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

t_ray	shoot_ray(t_hitrec *rec, t_cntl *cntl, int x, int y)
{
	t_ray	r;
	double	u;
	double	v;

	rec->tmin = 0.001;
	rec->tmax = INFINITY;
	u = (double)x / (cntl->scene->canv.width - 1);
	v = (double)y / (cntl->scene->canv.height - 1);
	r = ray(cntl->scene->cam_onair->origin, vminus(vminus(vminus(
		cntl->scene->cam_onair->left_top_corner,
		vmult(cntl->scene->cam_onair->horizontal, u)),
		vmult(cntl->scene->cam_onair->vertical, v)),
		cntl->scene->cam_onair->origin));
	return (r);
}
