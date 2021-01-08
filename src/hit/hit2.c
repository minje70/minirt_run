/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:29:44 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/07 19:30:10 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

void	hit_square_sub(t_square *sq, t_point3 *p)
{
	p[0] = vmult(vunit(vcross(vec3(0, -1, 0), sq->n)), sq->len / 2);
	p[2] = vmult(vunit(vcross(vec3(0, 1, 0), sq->n)), sq->len / 2);
	p[2] = vplus(vplus(p[2], vmult(vunit(vcross(p[0], sq->n)), sq->len / 2)),
			sq->p);
	p[0] = vplus(vplus(p[0], vmult(vunit(vcross(p[0], sq->n)), sq->len / 2)),
			sq->p);
	p[1] = vsymmetric(p[0], sq->p);
	p[3] = vsymmetric(p[2], sq->p);
}

t_bool	hit_square(t_square *sq, t_ray *r, t_hitrec *rec)
{
	t_point3	p[4];
	t_vec		temp;
	double		root;

	root = vdot(vminus(sq->p, r->orig), sq->n);
	if (vdot(sq->n, r->dir) == 0)
		root = root / 0.000001;
	else
		root = root / vdot(sq->n, r->dir);
	if (root < 0 || root < rec->tmin || root > rec->tmax)
		return (0);
	hit_square_sub(sq, p);
	temp = ray_at(*r, root);
	if (!(is_inside_(p[0], p[1], p[2], temp) || is_inside_(p[0], p[1], p[3],
		temp)))
		return (0);
	rec->t = root;
	rec->p = temp;
	rec->normal = sq->n;
	rec->obj_color = sq->color;
	set_face_normal(r, rec);
	rec->texture = *sq->texture;
	get_square_uv(rec, sq, p[3]);
	return (1);
}

t_bool	hit_cube(t_cube *cu, t_ray *r, t_hitrec *rec)
{
	int			i;
	int			hit_anything;
	t_hitrec	temp_rec;

	temp_rec = *rec;
	hit_anything = 0;
	i = -1;
	while (++i < 6)
	{
		if (hit_square(cu->sq[i], r, &temp_rec))
		{
			hit_anything = 1;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
			rec->obj = (t_objects *)cu->sq[i];
			rec->texture = *cu->texture;
		}
	}
	return (hit_anything);
}

t_bool	hit_pyramid(t_pyramid *py, t_ray *r, t_hitrec *rec)
{
	int			i;
	int			hit_anything;
	t_hitrec	temp_rec;

	temp_rec = *rec;
	hit_anything = 0;
	i = -1;
	while (++i < 4)
	{
		if (hit_triangle(py->tr[i], r, &temp_rec))
		{
			hit_anything = 1;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
			rec->texture = *py->texture;
		}
	}
	if (hit_square(py->sq, r, &temp_rec))
	{
		hit_anything = 1;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
		rec->texture = *py->texture;
	}
	return (hit_anything);
}
