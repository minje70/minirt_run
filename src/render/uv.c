/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:51:07 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:27:03 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

void	get_sphere_uv(t_hitrec *rec)
{
	double	theta;
	double	phi;

	theta = acos(rec->normal.y);
	phi = atan2(-rec->normal.z, rec->normal.x) + M_PI;
	rec->u = phi / (2 * M_PI);
	rec->v = theta / M_PI;
}

void	get_square_uv(t_hitrec *rec, t_square *sq, t_point3 left_bottom_p)
{
	t_vec	temp;
	t_vec	dir_v;

	temp = vdivide(vminus(rec->p, left_bottom_p), sq->len);
	dir_v = vunit(vcross(vec3(0, 1, 0), rec->normal));
	rec->u = vdot(temp, dir_v);
	dir_v = vunit(vcross(rec->normal, dir_v));
	rec->v = vdot(temp, dir_v);
}
