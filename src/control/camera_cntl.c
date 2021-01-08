/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_cntl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:30:32 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 20:03:47 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	cntl_camera_off(t_cntl *cntl)
{
	cntl->mode = 0;
	default_msg();
}

void	cntl_camera_on(t_cntl *cntl)
{
	cntl->mode = 2;
	camera_msg();
}

void	cntl_select_camera(t_cntl *cntl)
{
	t_objects	*temp;

	temp = (t_objects *)cntl->scene->cam_list;
	while (cntl->scene->cam_onair != (t_camera *)temp->data)
		temp = temp->next;
	if (temp->next == 0)
	{
		ft_printf("마지막 캠입니다.\n");
		cntl->scene->cam_onair = (t_camera *)cntl->scene->cam_list->data;
	}
	else
	{
		ft_printf("다음캠입니다.\n");
		cntl->scene->cam_onair = ((t_objects *)temp->next)->data;
	}
}

void	cntl_camera_translate(int keycode, t_cntl *cntl)
{
	t_camera	*camera;

	camera = cntl->scene->cam_onair;
	if (keycode == KEY_W)
		camera->origin = vplus(camera->origin, vmult(camera->w, 0.2));
	else if (keycode == KEY_S)
		camera->origin = vplus(camera->origin, vmult(camera->w, -0.2));
	else if (keycode == KEY_A)
		camera->origin = vplus(camera->origin, vcross(vmult(camera->w, -0.2),
						camera->vertical));
	else if (keycode == KEY_D)
		camera->origin = vplus(camera->origin, vcross(vmult(camera->w, 0.2),
						camera->vertical));
	else
		return ;
	ft_printf("camera move!!\n");
}

void	cntl_camera(t_cntl *cntl, int keycode)
{
	camera_msg();
	if (keycode == KEY_ESC)
	{
		cntl_camera_off(cntl);
		return ;
	}
	else if (keycode == KEY_AR_R)
		cntl_select_camera(cntl);
	else if (keycode == KEY_E || keycode == KEY_Q)
		cntl_camera_fov(keycode, cntl);
	else
		cntl_camera_translate(keycode, cntl);
	set_camera(cntl->scene->cam_onair);
	all_render(cntl, PRERANDER);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}
