/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cntl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:55:02 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 15:19:49 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	cntl_object_select(int button, int x, int y, t_cntl *cntl)
{
	t_ray		r;
	t_hitrec	rec;

	if (button != 1)
		ft_printf("If you want to select object, do left click!\n");
	else
	{
		r = shoot_ray(&rec, cntl, x, y);
		if (hit(&r, &rec, cntl->scene->world))
		{
			cntl->selected = rec.obj;
			cntl->mode = 1;
			object_msg();
		}
		else
		{
			cntl->selected = NULL;
			ft_printf("There is no object!\n");
		}
	}
}

int		is_double(char *str)
{
	char *start_point;

	start_point = str;
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
		++str;
	if (*str == '.')
		++str;
	while (ft_isdigit(*str))
		++str;
	if (*str == 0)
		return (0);
	ft_printf("Rotation value must be number\n");
	ft_printf("** INPUT ERROR **\n");
	ft_printf("** your input: \"%s\" **\n", str);
	return (-1);
}

double	put_rotate(char *input)
{
	char	*temp;
	double	result;

	temp = input;
	if (is_double(input) == -1)
	{
		free(temp);
		return (0);
	}
	result = check_dtoa(&input, 0);
	free(temp);
	return (result);
}

void	cntl_object_rotate(t_cntl *cntl)
{
	t_objects	*selected;
	t_vec		r_deg;
	char		*input;
	char		*temp;

	selected = cntl->selected;
	if (selected->type == SP || selected->type == TR)
		return ;
	ft_printf("\n*** TYPE Add rotation in degree ***\n");
	ft_printf("current_rotate is : (x:%.2f, y:%.2f, z:%.2f)\nx add:\n ",
			selected->rotate.x, selected->rotate.y, selected->rotate.z);
	get_next_line(0, &input);
	selected->rotate.x += put_rotate(input);
	ft_printf("y add:\n");
	get_next_line(0, &input);
	selected->rotate.y += put_rotate(input);
	ft_printf("z add:\n");
	get_next_line(0, &input);
	selected->rotate.z += put_rotate(input);
	ft_printf("Rotation Add success\n");
	ft_printf("current_rotate is : (x:%.2f, y:%.2f, z:%.2f)\n",
		selected->rotate.x, selected->rotate.y, selected->rotate.z);
}

void	cntl_object(int keycode, t_cntl *cntl)
{
	object_msg();
	if (keycode == KEY_X)
		cntl_object_translate_x_pos(cntl);
	else if (keycode == KEY_V)
		cntl_object_translate_y_pos(cntl);
	else if (keycode == KEY_AR_U)
		cntl_object_u_scale(cntl);
	else if (keycode == KEY_AR_D)
		cntl_object_d_scale(cntl);
	else if (keycode == KEY_ESC)
	{
		cntl_object_deselect(cntl);
		return ;
	}
	else if (keycode == KEY_R)
		cntl_object_rotate(cntl);
	all_render(cntl, PRERANDER);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}
