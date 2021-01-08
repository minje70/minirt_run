/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:32:52 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 15:18:02 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

int		cntl_close(t_cntl *cntl)
{
	system("clear");
	ft_printf("Close mlx, BYE\n");
	mlx_destroy_window(cntl->mlx, cntl->win);
	exit(0);
}

int		cntl_mouse_click(int button, int x, int y, t_cntl *cntl)
{
	if (cntl->mode == 0)
		cntl_object_select(button, x, y, cntl);
	else if (cntl->mode == 2)
		cntl_cam_rotate(button, cntl);
	return (0);
}

int		cntl_key_press(int keycode, t_cntl *cntl)
{
	if (keycode == KEY_O)
		cntl_light_on_and_off(cntl);
	else if (keycode == KEY_R && cntl->mode == DEFM)
	{
		all_render(cntl, ALLRANDER);
		mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
		ft_printf("안티 얼라이어싱 적용 완료!\n");
	}
	else if (keycode == KEY_C && cntl->mode != CAMM)
		cntl_camera_on(cntl);
	else if (keycode == KEY_ESC && cntl->mode == DEFM)
		cntl_close(cntl);
	else if (keycode == KEY_L && cntl->mode != LIGM)
		cntl_light_on(cntl);
	else if (keycode == KEY_T)
		cntl_rainbow_on_anc_off(cntl);
	else if (cntl->mode == CAMM)
		cntl_camera(cntl, keycode);
	else if (cntl->mode == OBJM)
		cntl_object(keycode, cntl);
	else if (cntl->mode == LIGM)
		cntl_light(cntl, keycode);
	else
		ft_printf("***press keycode:%d***\n", keycode);
	return (1);
}

int		cntl_click_x(int focus, t_cntl *cntl)
{
	system("clear");
	ft_printf("**Click Red X Button**\n");
	ft_printf("******Goodbye~~!******\n");
	exit(0);
}

void	my_mlx_control(t_cntl *cntl)
{
	default_msg();
	mlx_hook(cntl->win, 2, (1L << 0), cntl_key_press, cntl);
	mlx_hook(cntl->win, 17, (1L << 5), cntl_click_x, cntl);
	mlx_hook(cntl->win, 4, (1L << 6), cntl_mouse_click, cntl);
	mlx_loop(cntl->mlx);
}
