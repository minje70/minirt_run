/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cntl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:34:03 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 13:22:42 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	cntl_light_on(t_cntl *cntl)
{
	t_objects	*temp;

	cntl->mode = LIGM;
	while (cntl->scene->world->type != LI)
		cntl->scene->world = cntl->scene->world->next;
	cntl->selected = cntl->scene->world;
	light_msg();
}

void	cntl_light_on_and_off(t_cntl *cntl)
{
	if (cntl->light_on == LIGHT_OFF || cntl->light_on == RAINBOW)
	{
		cntl->light_on = LIGHT_ON;
		perror("light on(if you press o, light off)\n");
	}
	else
	{
		cntl->light_on = LIGHT_OFF;
		perror("light off(if you press o, light on)\n");
	}
	all_render(cntl, PRERANDER);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}

void	cntl_rainbow_on_anc_off(t_cntl *cntl)
{
	if (cntl->light_on != RAINBOW)
	{
		cntl->light_on = RAINBOW;
		ft_printf("<rainbow on>\n");
	}
	else
	{
		cntl->light_on = LIGHT_OFF;
		ft_printf("<rainbow off>\n");
	}
	all_render(cntl, PRERANDER);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}

void	cntl_light_select(t_cntl *cntl)
{
	t_objects	*temp;

	if (cntl->selected == 0 || cntl->selected->next == 0)
		temp = (t_objects *)cntl->scene->world;
	else
		temp = (t_objects *)cntl->selected->next;
	while (temp && temp->type != LI)
		temp = temp->next;
	if (temp == 0)
	{
		temp = (t_objects *)cntl->scene->world;
		while (temp && temp->type != LI)
			temp = temp->next;
		cntl->selected = temp;
		ft_printf("마지막 조명입니다.\n");
	}
	else
	{
		cntl->selected = temp;
		ft_printf("다음 조명입니다.\n");
	}
}

void	cntl_light_deselect(t_cntl *cntl)
{
	default_msg();
	cntl->selected = NULL;
	cntl->mode = DEFM;
}
