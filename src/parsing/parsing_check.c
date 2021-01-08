/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 02:00:14 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 15:50:45 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_bool	parsing_check2(t_cntl *cntl, char **line)
{
	t_square	*sq;

	if (**line == 't' && *(*line + 1) == 'r')
		obj_add_back(&cntl->scene->world, set_object(TR, set_triangle(point3(
			check_dtoa(line, 2), check_dtoa(line, 0), check_dtoa(line, 0)),
			point3(check_dtoa(line, 0), check_dtoa(line, 0), check_dtoa(
			line, 0)), point3(check_dtoa(line, 0), check_dtoa(line, 0),
			check_dtoa(line, 0)), vdivide(color(check_itoa(line, 0),
			check_itoa(line, 0), check_itoa(line, 0)), 255.0))));
	else if (**line == 's' && *(*line + 1) == 'q')
	{
		sq = set_square(point3(check_dtoa(line, 2), check_dtoa(line, 0),
			check_dtoa(line, 0)), vec3(check_dtoa(line, 0), check_dtoa(line, 0)
			, check_dtoa(line, 0)), check_dtoa(line, 0), vdivide(color(
			check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0))
			, 255.0));
		sq->texture = set_texture(check_itoa(line, 0), sq->color,
			color(0, 0, 0), 0);
		obj_add_back(&cntl->scene->world, set_object(SQ, sq));
	}
	else
		return (0);
	return (1);
}

t_bool	parsing_check3(t_cntl *cntl, char **line)
{
	t_cylinder	*cy;

	if (**line == 'c' && *(*line + 1) == 'y')
	{
		cy = set_cylinder(point3(check_dtoa(line, 2), check_dtoa(line, 0)
			, check_dtoa(line, 0)), vec3(check_dtoa(line, 0), check_dtoa(
			line, 0), check_dtoa(line, 0)), check_dtoa(line, 0)
			, check_dtoa(line, 0));
		cy->color = vdivide(color(check_itoa(line, 0), check_itoa(line, 0)
			, check_itoa(line, 0)), 255.0);
		cy->texture = set_texture(SOLID, cy->color, color(0, 0, 0), 0);
		obj_add_back(&cntl->scene->world, set_object(CY, cy));
	}
	else if (**line == 'p' && *(*line + 1) == 'y')
		obj_add_back(&cntl->scene->world, set_object(PY, set_pyramid(point3(
			check_dtoa(line, 2), check_dtoa(line, 0), check_dtoa(line, 0))
			, check_dtoa(line, 0), check_dtoa(line, 0), vdivide(color(
			check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0))
			, 255.0))));
	else
		return (0);
	return (1);
}

t_bool	parsing_check4(t_cntl *cntl, char **line)
{
	t_cube		*cu;

	if (**line == 'c' && *(*line + 1) == 'u')
	{
		cu = set_cube(point3(check_dtoa(line, 2), check_dtoa(line, 0)
			, check_dtoa(line, 0)), check_dtoa(line, 0), vdivide(color(
			check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0))
			, 255.0), check_itoa(line, 0));
		set_skybox_img(cntl, cu, "./skybox/roundabout.png");
		obj_add_back(&cntl->scene->world, set_object(CU, cu));
	}
	else if (**line == 'R')
		set_viewport(&cntl->scene->canv, check_itoa(line, 1), check_itoa(
			line, 0));
	else if (**line == 'A')
		set_amblight(&cntl->scene->canv, check_dtoa(line, 1), vdivide(color(
			check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0))
			, 255.0));
	else
		return (0);
	return (1);
}

t_bool	parsing_check5(t_cntl *cntl, char **line)
{
	if (**line == 'c')
		obj_add_back(&cntl->scene->cam_list, set_object(CAM, init_camera(
			point3(check_dtoa(line, 1), check_dtoa(line, 0), check_dtoa(
			line, 0)), vec3(check_dtoa(line, 0), check_dtoa(line, 0)
			, check_dtoa(line, 0)), check_itoa(line, 0))));
	else if (**line == 'l')
		obj_add_back(&cntl->scene->world, set_object(LI, set_light(point3(
			check_dtoa(line, 1), check_dtoa(line, 0), check_dtoa(line, 0))
			, check_dtoa(line, 0), vdivide(color(check_itoa(line, 0)
			, check_itoa(line, 0), check_itoa(line, 0)), 255.0))));
	else if (**line != 0)
		eerror("Error\n잘못된 식별자가 들어왔습니다.");
	else
		return (0);
	return (1);
}

int		parsing_check(t_cntl *cntl, char **line)
{
	if (**line == '#')
		;
	else if (**line == 's' && *(*line + 1) == 'p')
		obj_add_back(&cntl->scene->world, set_object(SP, set_sphere(point3(
			check_dtoa(line, 2), check_dtoa(line, 0), check_dtoa(line, 0)),
			check_dtoa(line, 0), vdivide(color(check_itoa(line, 0), check_itoa(
			line, 0), check_itoa(line, 0)), 255.0), check_itoa(line, 0))));
	else if (**line == 'p' && *(*line + 1) == 'l')
		obj_add_back(&cntl->scene->world, set_object(PL, set_plane(point3(
			check_dtoa(line, 2), check_dtoa(line, 0), check_dtoa(line, 0)),
			vec3(check_dtoa(line, 0), check_dtoa(line, 0), check_dtoa(line, 0))
			, vdivide(color(check_itoa(line, 0), check_itoa(line, 0)
			, check_itoa(line, 0)), 255.0), check_itoa(line, 0))));
	else if (parsing_check2(cntl, line))
		return (1);
	else if (parsing_check3(cntl, line))
		return (1);
	else if (parsing_check4(cntl, line))
		return (1);
	else if (parsing_check5(cntl, line))
		return (1);
	return (1);
}
