/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 18:55:57 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/07 18:56:12 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

void	capcylinder_rec(t_hitrec *rec, t_hitrec *temp_rec, t_cylinder *cy,
		int *hit_anything)
{
	*hit_anything = 1;
	temp_rec->tmax = temp_rec->t;
	*rec = *temp_rec;
	rec->texture = *cy->texture;
}

t_bool	hit_cap_cylinder(t_cylinder *cy, t_ray *r, t_hitrec *rec)
{
	int			hit_anything;
	t_hitrec	temp_rec;
	t_plane		pl;

	temp_rec = *rec;
	hit_anything = 0;
	pl.color = cy->color;
	pl.normal = cy->v;
	pl.texture = cy->texture;
	if (hit_cylinder(cy, r, &temp_rec))
		capcylinder_rec(rec, &temp_rec, cy, &hit_anything);
	pl.p = cy->p;
	if (hit_cy_circle(&pl, r, &temp_rec, cy->r))
		capcylinder_rec(rec, &temp_rec, cy, &hit_anything);
	pl.p = cy->p2;
	if (hit_cy_circle(&pl, r, &temp_rec, cy->r))
		capcylinder_rec(rec, &temp_rec, cy, &hit_anything);
	return (hit_anything);
}
