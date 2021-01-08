/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 22:27:11 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/07 22:27:43 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void		set_viewport(t_std_set *s_set, int width, int height)
{
	if (s_set->width != -1 || s_set->height != -1)
		eerror("R은 한번만 적용할 수 있습니다.\n");
	s_set->width = width;
	s_set->height = height;
}

void		set_amblight(t_std_set *s_set, double lighting_ratio, t_color color)
{
	if (s_set->amb_light != -1 || s_set->color.x != -1 || s_set->color.y != -1
		|| s_set->color.z != -1)
		eerror("A는 한번만 적용할 수 있습니다.\n");
	s_set->color = color;
	s_set->amb_light = lighting_ratio;
}

t_camera	*init_camera(t_point3 lookfrom, t_vec w, double fov)
{
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (cam == 0)
		eerror("cam 할당실패\n");
	cam->origin = lookfrom;
	cam->w = w;
	cam->fov = fov;
	return (cam);
}

int			set_camera(t_camera *cam)
{
	t_vec	u;
	t_vec	v;
	t_vec	vup;

	vup = vec3(0, 1, 0);
	cam->w = vunit(cam->w);
	u = vunit(vcross(vup, cam->w));
	v = vcross(cam->w, u);
	cam->horizontal = vmult(u, 2 * tan(degrees_to_radians(cam->fov) / 2));
	cam->vertical = vmult(v, 2 * tan(degrees_to_radians(cam->fov) / 2));
	cam->left_top_corner = vplus(vplus(vplus(cam->w, cam->origin),
			vdivide(cam->horizontal, 2)), vdivide(cam->vertical, 2));
	return (1);
}
