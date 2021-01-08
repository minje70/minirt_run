/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cntl2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:45:40 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 15:29:35 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	cntl_object_translate_x_pos(t_cntl *cntl)
{
	if (cntl->selected->type == SP)
		((t_sphere *)(cntl->selected->data))->center.x += 0.5;
	else if (cntl->selected->type == TR)
	{
		((t_triangle *)(cntl->selected->data))->p1.x += 0.5;
		((t_triangle *)(cntl->selected->data))->p2.x += 0.5;
		((t_triangle *)(cntl->selected->data))->p3.x += 0.5;
	}
	else if (cntl->selected->type == SQ)
		((t_square *)(cntl->selected->data))->p.x += 0.5;
	else if (cntl->selected->type == CY)
	{
		((t_cylinder *)(cntl->selected->data))->p.x += 0.5;
		((t_cylinder *)(cntl->selected->data))->p2.x += 0.5;
	}
}

void	cntl_object_translate_y_pos(t_cntl *cntl)
{
	if (cntl->selected->type == SP)
		((t_sphere *)(cntl->selected->data))->center.y += 0.5;
	else if (cntl->selected->type == TR)
	{
		((t_triangle *)(cntl->selected->data))->p1.y += 0.5;
		((t_triangle *)(cntl->selected->data))->p2.y += 0.5;
		((t_triangle *)(cntl->selected->data))->p3.y += 0.5;
	}
	else if (cntl->selected->type == SQ)
		((t_square *)(cntl->selected->data))->p.y += 0.5;
	else if (cntl->selected->type == CY)
	{
		((t_cylinder *)(cntl->selected->data))->p.y += 0.5;
		((t_cylinder *)(cntl->selected->data))->p2.y += 0.5;
	}
}

void	cntl_object_u_scale(t_cntl *cntl)
{
	t_cylinder	*cyl;

	if (cntl->selected->type == SP)
		((t_sphere *)(cntl->selected->data))->radius += 0.05;
	else if (cntl->selected->type == CY)
	{
		cyl = (t_cylinder *)(cntl->selected->data);
		cyl->r += 0.05;
		cyl->h += 0.05;
		cyl->p2 = vplus(cyl->p, vmult(cyl->v, cyl->h));
	}
	else if (cntl->selected->type == SQ)
		((t_square *)(cntl->selected->data))->len += 0.05;
}

void	cntl_object_d_scale(t_cntl *cntl)
{
	t_cylinder	*cyl;

	if (cntl->selected->type == SP)
	{
		((t_sphere *)(cntl->selected->data))->radius -= 0.05;
		if (((t_sphere *)(cntl->selected->data))->radius < 0)
			((t_sphere *)(cntl->selected->data))->radius = 0;
	}
	else if (cntl->selected->type == CY)
	{
		cyl = (t_cylinder *)(cntl->selected->data);
		cyl->r -= 0.05;
		cyl->h -= 0.05;
		if (cyl->r < 0)
			cyl->r = 0;
		if (cyl->h < 0)
			cyl->h = 0;
		cyl->p2 = vplus(cyl->p, vmult(cyl->v, cyl->h));
	}
	else if (cntl->selected->type == SQ)
	{
		((t_square *)(cntl->selected->data))->len -= 0.05;
		if (((t_square *)(cntl->selected->data))->len < 0)
			((t_square *)(cntl->selected->data))->len = 0;
	}
}

void	cntl_object_deselect(t_cntl *cntl)
{
	cntl->mode = 0;
	cntl->selected = NULL;
	default_msg();
}
