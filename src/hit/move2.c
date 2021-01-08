/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:01:47 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/07 17:02:48 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"

t_bool	check_pl_rotate(t_objects *obj, t_hitrec *rec, t_ray *r)
{
	t_plane		t_pl;
	t_ray		t_r;
	t_bool		result;
	t_point3	offset;

	t_pl = *(t_plane *)obj->data;
	t_r = *r;
	if (obj->rotate.x == 0 && obj->rotate.y == 0 && obj->rotate.z == 0)
		result = hit_plane(&t_pl, &t_r, rec);
	else
	{
		offset = vminus(t_pl.p, point3(0.01, 0.01, 0.01));
		t_r.orig = vminus(t_r.orig, offset);
		t_pl.p = vminus(t_pl.p, offset);
		rotate_r(&t_r, obj->rotate);
		result = hit_plane(&t_pl, &t_r, rec);
		ray_normal_back(rec, &obj->rotate, &offset);
	}
	return (result);
}

t_bool	check_cu_rotate(t_objects *obj, t_hitrec *rec, t_ray *r)
{
	t_cube		t_cu;
	t_ray		t_r;
	t_bool		result;
	t_point3	offset;

	t_cu = *(t_cube *)obj->data;
	t_r = *r;
	if (obj->rotate.x == 0 && obj->rotate.y == 0 && obj->rotate.z == 0)
		result = hit_cube(&t_cu, &t_r, rec);
	else
	{
		offset = vminus(t_cu.p, point3(0.01, 0.01, 0.01));
		t_r.orig = vminus(t_r.orig, offset);
		t_cu.p = vminus(t_cu.p, offset);
		rotate_r(&t_r, obj->rotate);
		result = hit_cube(&t_cu, &t_r, rec);
		ray_normal_back(rec, &obj->rotate, &offset);
	}
	return (result);
}

t_bool	check_py_rotate(t_objects *obj, t_hitrec *rec, t_ray *r)
{
	t_pyramid	t_py;
	t_ray		t_r;
	t_bool		result;
	t_point3	offset;

	t_py = *(t_pyramid *)obj->data;
	t_r = *r;
	if (obj->rotate.x == 0 && obj->rotate.y == 0 && obj->rotate.z == 0)
		result = hit_pyramid(&t_py, &t_r, rec);
	else
	{
		offset = vminus(t_py.p, point3(0.01, 0.01, 0.01));
		t_r.orig = vminus(t_r.orig, offset);
		t_py.p = vminus(t_py.p, offset);
		rotate_r(&t_r, obj->rotate);
		result = hit_pyramid(&t_py, &t_r, rec);
		ray_normal_back(rec, &obj->rotate, &offset);
	}
	return (result);
}
