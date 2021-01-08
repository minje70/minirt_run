/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:01:19 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/07 17:02:06 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"

void	rotate_r(t_ray *r, t_rotate rot)
{
	rotate_v(&r->orig, rot);
	rotate_v(&r->dir, rot);
}

t_bool	check_cy_rotate(t_objects *obj, t_hitrec *rec, t_ray *r)
{
	t_cylinder	t_cy;
	t_ray		t_r;
	t_bool		result;
	t_point3	offset;

	t_cy = *(t_cylinder *)obj->data;
	t_r = *r;
	if (obj->rotate.x == 0 && obj->rotate.y == 0 && obj->rotate.z == 0)
		result = hit_cap_cylinder(&t_cy, &t_r, rec);
	else
	{
		offset = vmult(vplus((*(t_cylinder *)obj->data).p,
				(*(t_cylinder *)obj->data).p2), 0.5);
		t_r.orig = vminus(t_r.orig, offset);
		t_cy.p2 = vminus(t_cy.p2, offset);
		t_cy.p = vminus(t_cy.p, offset);
		rotate_r(&t_r, obj->rotate);
		result = hit_cap_cylinder(&t_cy, &t_r, rec);
		ray_normal_back(rec, &obj->rotate, &offset);
	}
	return (result);
}

t_bool	check_tr_rotate(t_objects *obj, t_hitrec *rec, t_ray *r)
{
	t_triangle	t_tr;
	t_ray		t_r;
	t_bool		result;
	t_point3	offset;

	t_tr = *(t_triangle *)obj->data;
	t_r = *r;
	if (obj->rotate.x == 0 && obj->rotate.y == 0 && obj->rotate.z == 0)
		result = hit_triangle(&t_tr, &t_r, rec);
	else
	{
		offset = vdivide(vplus(t_tr.p1, vplus(t_tr.p2, t_tr.p3)), 3);
		t_r.orig = vminus(t_r.orig, offset);
		t_tr.p1 = vminus(t_tr.p1, offset);
		t_tr.p2 = vminus(t_tr.p2, offset);
		t_tr.p3 = vminus(t_tr.p3, offset);
		rotate_r(&t_r, obj->rotate);
		result = hit_triangle(&t_tr, &t_r, rec);
		ray_normal_back(rec, &obj->rotate, &offset);
	}
	return (result);
}

t_bool	check_sq_rotate(t_objects *obj, t_hitrec *rec, t_ray *r)
{
	t_square	t_sq;
	t_ray		t_r;
	t_bool		result;
	t_point3	offset;

	t_sq = *(t_square *)obj->data;
	t_r = *r;
	if (obj->rotate.x == 0 && obj->rotate.y == 0 && obj->rotate.z == 0)
		result = hit_square(&t_sq, &t_r, rec);
	else
	{
		offset = vminus(t_sq.p, point3(0.01, 0.01, 0.01));
		t_r.orig = vminus(t_r.orig, offset);
		t_sq.p = vminus(t_sq.p, offset);
		rotate_r(&t_r, obj->rotate);
		result = hit_square(&t_sq, &t_r, rec);
		ray_normal_back(rec, &obj->rotate, &offset);
	}
	return (result);
}

void	ray_normal_back(t_hitrec *rec, t_rotate *rot, t_point3 *offset)
{
	if (rot->x == 0 && rot->y == 0 && rot->z == 0)
		return ;
	rotate_iv(&rec->p, vmult(*rot, -1));
	rec->p = vplus(rec->p, *offset);
	rotate_iv(&rec->normal, vmult(*rot, -1));
}
