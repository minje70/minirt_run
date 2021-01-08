/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:14:06 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 20:09:32 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

t_color	parallel_specular_color(t_vec v, t_hitrec *rec, t_camera *camera)
{
	double	spec;
	double	specular_strength;
	t_vec	view_dir;
	t_vec	reflect_dir;
	t_vec	temp;

	specular_strength = 0.5;
	view_dir = vunit(vminus(camera->origin, rec->p));
	temp = v;
	reflect_dir = vunit(vplus(temp, vmult(rec->normal, -2 *
				vdot(temp, rec->normal))));
	spec = pow(max_d(vdot(view_dir, reflect_dir), 0.0), 256);
	return (vmult(color(1, 1, 1), specular_strength * spec));
}
