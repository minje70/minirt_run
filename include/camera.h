/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:17:35 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:17:37 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <math.h>
# include "structure.h"
# include "vector.h"
# include "uutil.h"

void		set_amblight(t_std_set *s_set, double lighting_ratio,
						t_color color);
void		set_viewport(t_std_set *s_set, int width, int height);
t_camera	*init_camera(t_point3 lookfrom, t_vec w, double fov);
int			set_camera(t_camera	*cam);
#endif
