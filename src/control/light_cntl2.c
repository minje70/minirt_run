/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cntl2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:34:45 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 13:59:55 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	cntl_light_bright_up(t_cntl *cntl)
{
	double	brightness;
	t_color	*color;

	brightness = ((t_light *)(cntl->selected->data))->brightness;
	color = &((t_light *)(cntl->selected->data))->color;
	if (cntl->selected->type == LI)
	{
		brightness += 0.1;
		if (brightness > 1)
			brightness = 1;
		*color = vdivide(*color,
						((t_light *)(cntl->selected->data))->brightness);
		((t_light *)(cntl->selected->data))->brightness = brightness;
		*color = vmult(*color, brightness);
		ft_printf("%f, %f, %f\n", color->x, color->y, color->z);
	}
	ft_printf("조명증가\n");
}

void	cntl_light_bright_down(t_cntl *cntl)
{
	double	brightness;
	t_color	*color;

	brightness = ((t_light *)(cntl->selected->data))->brightness;
	color = &((t_light *)(cntl->selected->data))->color;
	if (cntl->selected->type == LI)
	{
		brightness -= 0.1;
		if (brightness < 0)
			brightness = 0.000001;
		*color = vdivide(*color,
						((t_light *)(cntl->selected->data))->brightness);
		((t_light *)(cntl->selected->data))->brightness = brightness;
		*color = vmult(*color, brightness);
		ft_printf("%f, %f, %f\n", color->x, color->y, color->z);
	}
	ft_printf("조명감소\n");
}

void	cntl_light_translate_x_pos(t_cntl *cntl)
{
	if (cntl->selected->type == LI)
		((t_light *)(cntl->selected->data))->point.x += 0.3;
	ft_printf("light x이동\n");
}

void	cntl_light_translate_y_pos(t_cntl *cntl)
{
	if (cntl->selected->type == LI)
		((t_light *)(cntl->selected->data))->point.y += 0.3;
	ft_printf("light y이동\n");
}

void	cntl_light(t_cntl *cntl, int keycode)
{
	light_msg();
	if (keycode == KEY_AR_R)
	{
		cntl_light_select(cntl);
		return ;
	}
	else if (keycode == KEY_X)
		cntl_light_translate_x_pos(cntl);
	else if (keycode == KEY_V)
		cntl_light_translate_y_pos(cntl);
	else if (keycode == KEY_ESC)
	{
		cntl_light_deselect(cntl);
		return ;
	}
	else if (keycode == KEY_AR_U)
		cntl_light_bright_up(cntl);
	else if (keycode == KEY_AR_D)
		cntl_light_bright_down(cntl);
	all_render(cntl, PRERANDER);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}
