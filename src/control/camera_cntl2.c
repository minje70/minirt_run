/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_cntl2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:30:40 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 13:12:00 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	cntl_camera_fov(int keycode, t_cntl *cntl)
{
	t_camera	*camera;

	camera = cntl->scene->cam_onair;
	if (keycode == KEY_Q)
	{
		camera->fov += 5;
		if (camera->fov >= 180)
			camera->fov = 180;
		ft_printf("fov ++++++++++++\n");
	}
	else if (keycode == KEY_E)
	{
		camera->fov -= 5;
		if (camera->fov <= 0)
			camera->fov = 0;
		ft_printf("fov -------------\n");
	}
}

void	cntl_cam_rotate(int button, t_cntl *cntl)
{
	t_camera	*cam;
	t_rotate	rot;

	cam = cntl->scene->cam_onair;
	ft_printf("****camera rotate****\n");
	if (button == 1 || button == 7)
		rot = vec3(0, 45, 0);
	else if (button == 2 || button == 6)
		rot = vec3(0, -45, 0);
	else if (button == 5)
		rot = vec3(45, 0, 0);
	else if (button == 4)
		rot = vec3(-45, 0, 0);
	else
	{
		ft_printf("you click button : %d\n", button);
		return ;
	}
	rotate_v(&cam->w, rot);
	set_camera(cntl->scene->cam_onair);
	all_render(cntl, PRERANDER);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
	ft_printf("******회전 완료******\n");
}
