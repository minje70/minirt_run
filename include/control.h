/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:09:59 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 12:55:47 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_H
# define CONTROL_H

# define DEFM 0
# define OBJM 1
# define CAMM 2
# define LIGM 3

# define LIGHT_ON 0
# define LIGHT_OFF 1

# define PRERANDER 0
# define ALLRANDER 1

# define PIXEL_PER_COLOR 20

# include "mlx.h"
# include "vector.h"
# include "structure.h"
# include "bitmap.h"
# include "parsing.h"
# include "key_macos.h"
# include "render.h"
# include "camera.h"
# include "ray.h"
# include "ft_printf.h"
# include "unistd.h"

void		my_mlx_control(t_cntl *cntl);
void		cntl_display_resolution(t_cntl *cntl);
/*
** object
*/

void		cntl_object(int keycode, t_cntl *cntl);
void		cntl_object_select(int button, int x, int y, t_cntl *cntl);
void		cntl_object_deselect(t_cntl *cntl);
void		cntl_object_u_scale(t_cntl *cntl);
void		cntl_object_d_scale(t_cntl *cntl);
void		cntl_object_translate_x_pos(t_cntl *cntl);
void		cntl_object_translate_y_pos(t_cntl *cntl);
void		cntl_object_rotate(t_cntl *cntl);
/*
** camera
*/
void		cntl_camera_on(t_cntl *cntl);
void		cntl_camera_off(t_cntl *cntl);
void		cntl_select_camera(t_cntl *cntl);
void		cntl_cam_rotate(int keycode, t_cntl *cntl);
void		cntl_camera_translate(int keycode, t_cntl *cntl);
void		cntl_camera(t_cntl *cntl, int keycode);
void		cntl_camera_fov(int keycode, t_cntl *cntl);
/*
** light
*/
void		cntl_light_deselect(t_cntl *cntl);
void		cntl_light_translate_x_pos(t_cntl *cntl);
void		cntl_light_translate_y_pos(t_cntl *cntl);
void		cntl_light_bright_up(t_cntl *cntl);
void		cntl_light_bright_down(t_cntl *cntl);
void		cntl_light(t_cntl *cntl, int keycode);
void		cntl_light_select(t_cntl *cntl);
void		cntl_light_on(t_cntl *cntl);
void		cntl_light_on_and_off(t_cntl *cntl);
void		cntl_rainbow_on_anc_off(t_cntl *cntl);

/*
** save
*/
void		bmp_save(t_cntl *cntl);

/*
** msg
*/
void		object_msg();
void		camera_msg();
void		light_msg();
void		default_msg();

#endif
