/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 18:25:53 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/07 18:55:55 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

t_bool	hit_cy_circle(t_plane *pl, t_ray *r, t_hitrec *rec, double radius)
{
	t_vec	v;

	if (hit_plane(pl, r, rec))
	{
		v = vminus(pl->p, rec->p);
		if (vlength(v) <= radius)
			return (1);
	}
	return (0);
}

void	set_cylinder_disc(t_cylinder *cy, t_ray *r, t_hit_disc *disc)
{
	disc->a = vlength2(vminus(r->dir, vmult(cy->v, vdot(cy->v, r->dir))));
	disc->half_b = vdot(vminus(r->dir, vmult(cy->v, vdot(cy->v, r->dir))),
				vminus(vminus(r->orig, cy->p), vmult(cy->v, vdot(cy->v,
				vminus(r->orig, cy->p)))));
	disc->c = vlength2(vminus(vminus(r->orig, cy->p), vmult(cy->v, vdot(cy->v,
				vminus(r->orig, cy->p))))) - cy->r * cy->r;
	disc->discriminant = disc->half_b * disc->half_b - disc->a * disc->c;
}

void	cylinder_rec(t_cylinder *cy, t_ray *r, t_hitrec *rec, double root)
{
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	rec->normal = vdivide(vminus(vminus(rec->p, cy->p), vmult(cy->v,
					vdot(cy->v, vminus(rec->p, cy->p)))), cy->r);
	rec->obj_color = cy->color;
	set_face_normal(r, rec);
	rec->p = vplus(rec->p, vmult(rec->normal, 0.001));
}

t_bool	cylinder_root_check(t_cylinder *cy, t_ray *r, double root)
{
	return (vdot(cy->v, vminus(cy->p2, ray_at(*r, root))) < 0 ||
			vdot(cy->v, vminus(cy->p, ray_at(*r, root))) > 0);
}

t_bool	hit_cylinder(t_cylinder *cy, t_ray *r, t_hitrec *rec)
{
	t_hit_disc	disc;
	double		sqrtd;
	double		root;

	set_cylinder_disc(cy, r, &disc);
	sqrtd = sqrt(disc.discriminant);
	root = (-disc.half_b - sqrtd) / disc.a;
	if (disc.discriminant < 0)
		return (0);
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-disc.half_b + sqrtd) / disc.a;
		if (root < rec->tmin || root > rec->tmax)
			return (0);
		else if (cylinder_root_check(cy, r, root))
			return (0);
	}
	else if (cylinder_root_check(cy, r, root))
	{
		root = (-disc.half_b + sqrtd) / disc.a;
		if (cylinder_root_check(cy, r, root))
			return (0);
	}
	cylinder_rec(cy, r, rec, root);
	return (1);
}
