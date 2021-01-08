/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 22:26:20 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 16:12:17 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

t_texture	*set_texture(int type, t_color albedo1, t_color albedo2,
						double option)
{
	t_texture	*text;

	text = (t_texture *)malloc(sizeof(t_texture));
	if (text == 0)
		eerror("Error\ntexture init fail!!\n");
	text->type = type;
	text->albedo1 = albedo1;
	text->albedo2 = albedo2;
	text->option = option;
	return (text);
}

t_sphere	*set_sphere(t_point3 center, double radius, t_color objcolor,
						int texture_type)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == 0)
		eerror("Error\nsphere init fail!!\n");
	sphere->radius = radius;
	sphere->center = center;
	sphere->obj_color = objcolor;
	sphere->texture = set_texture(texture_type, objcolor, color(0, 0, 0), 0);
	return (sphere);
}

t_plane		*set_plane(t_point3 point, t_vec normal, t_color objcolor,
						int texture_type)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (plane == 0)
		eerror("Error\nplane init fail!!\n");
	plane->p = point;
	plane->normal = vunit(normal);
	plane->color = objcolor;
	plane->texture = set_texture(texture_type, objcolor, color(0, 0, 0), 0);
	return (plane);
}

t_triangle	*set_triangle(t_point3 p1, t_point3 p2, t_point3 p3,
							t_color objcolor)
{
	t_triangle	*tri;
	t_vec		temp;

	tri = (t_triangle *)malloc(sizeof(t_triangle));
	if (tri == 0)
		eerror("Error\ntriangle init fail!!\n");
	tri->texture = set_texture(SOLID, objcolor, color(0, 0, 0), 0);
	tri->p1 = p1;
	tri->p2 = p2;
	tri->p3 = p3;
	tri->color = objcolor;
	temp = vcross(vminus(p2, p1), vminus(p3, p1));
	tri->normal = vdivide(temp, vlength(temp));
	return (tri);
}

t_cylinder	*set_cylinder(t_point3 p, t_vec v, double r, double h)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cyl == 0)
		eerror("Error\ncylinder init fail!!\n");
	cyl->h = h;
	cyl->p = p;
	cyl->p2 = vplus(p, vmult(v, h));
	cyl->r = r;
	cyl->v = vunit(v);
	return (cyl);
}
