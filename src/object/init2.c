/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 22:28:11 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 13:54:16 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

t_square	*set_square(t_point3 p, t_vec n, double len, t_color objcolor)
{
	t_square	*square;

	square = (t_square *)malloc(sizeof(t_square));
	if (square == 0)
		eerror("Error\nsquare init fail!!\n");
	square->p = p;
	square->n = vunit(n);
	if (square->n.y == 1 || square->n.y == -1)
		square->n = vplus(square->n, vec3(0, 0, 0.0000001));
	else if (square->n.z == 1 || square->n.z == -1)
		square->n = vplus(square->n, vec3(0, 0.0000001, 0));
	square->len = len;
	square->color = objcolor;
	return (square);
}

t_cube		*set_cube(t_point3 p, double len, t_color objcolor,
					int texture_type)
{
	t_cube	*cube;

	cube = (t_cube *)malloc(sizeof(t_cube));
	if (cube == 0)
		eerror("Error\ncube init fail!!\n");
	cube->texture = set_texture(texture_type, objcolor, color(0, 0, 0), 0);
	cube->sq[0] = set_square(vplus(p, vmult(vec3(0, 0, 1), len / 2)),
				vec3(0, 0, 1), len, objcolor);
	cube->sq[0]->texture = cube->texture;
	cube->sq[1] = set_square(vplus(p, vmult(vec3(0, 0, -1), len / 2)),
				vec3(0, 0, -1), len, objcolor);
	cube->sq[1]->texture = cube->texture;
	cube->sq[2] = set_square(vplus(p, vmult(vec3(0, 1, 0), len / 2)),
				vec3(0, 1, 0), len, objcolor);
	cube->sq[2]->texture = cube->texture;
	cube->sq[3] = set_square(vplus(p, vmult(vec3(0, -1, 0), len / 2)),
				vec3(0, -1, 0), len, objcolor);
	cube->sq[3]->texture = cube->texture;
	cube->sq[4] = set_square(vplus(p, vmult(vec3(1, 0, 0), len / 2)),
				vec3(1, 0, 0), len, objcolor);
	cube->sq[4]->texture = cube->texture;
	cube->sq[5] = set_square(vplus(p, vmult(vec3(-1, 0, 0), len / 2)),
				vec3(-1, 0, 0), len, objcolor);
	cube->sq[5]->texture = cube->texture;
	return (cube);
}

void		set_pyramid_sub(t_pyramid *py, t_point3 *pp)
{
	pp[0] = vmult(vunit(vcross(vminus(yzero(py->sq->p), py->sq->p),
			py->sq->n)), py->sq->len / 2);
	pp[2] = vmult(vunit(vcross(vminus(py->sq->p, yzero(py->sq->p)),
			py->sq->n)), py->sq->len / 2);
	pp[2] = vplus(vplus(pp[2], vmult(vunit(vcross(pp[0], py->sq->n)),
			py->sq->len / 2)), py->sq->p);
	pp[0] = vplus(vplus(pp[0], vmult(vunit(vcross(pp[0], py->sq->n)),
			py->sq->len / 2)), py->sq->p);
	pp[1] = vsymmetric(pp[0], py->sq->p);
	pp[3] = vsymmetric(pp[2], py->sq->p);
}

t_pyramid	*set_pyramid(t_point3 p, double len, double h, t_color objcolor)
{
	t_pyramid	*py;
	t_point3	pp[4];
	t_point3	top;

	py = (t_pyramid *)malloc(sizeof(t_pyramid));
	if (py == 0)
		eerror("Error\npyramid init fail!!\n");
	py->texture = set_texture(SOLID, objcolor, color(0, 0, 0), 0);
	py->color = objcolor;
	py->p = p;
	py->len = len;
	py->sq = set_square(p, vec3(0, -1, 0), len, objcolor);
	py->sq->texture = py->texture;
	set_pyramid_sub(py, pp);
	top = vplus(p, vmult(vec3(0, 1, 0), h));
	py->tr[0] = set_triangle(pp[0], pp[2], top, objcolor);
	py->tr[1] = set_triangle(pp[2], pp[1], top, objcolor);
	py->tr[2] = set_triangle(pp[1], pp[3], top, objcolor);
	py->tr[3] = set_triangle(pp[3], pp[0], top, objcolor);
	return (py);
}

t_light		*set_light(t_point3 point, double brightness, t_color color)
{
	t_light	*light;
	double	lux;

	lux = 40;
	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (0);
	light->brightness = brightness;
	light->color = vmult(color, brightness * lux);
	light->point = point;
	return (light);
}
