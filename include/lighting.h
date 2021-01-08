/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:23:43 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 14:15:56 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H
# include <math.h>
# include "structure.h"
# include "vector.h"
# include "uutil.h"
# include "hit.h"

t_color	ambient_color(t_light *light, double ambient_strength);
t_color	diff_color(t_light *light, t_hitrec *rec);
t_color	specular_color(t_light *light, t_hitrec *rec, t_camera *camera);
t_bool	shadow_color(t_light *light, t_objects *obj, t_hitrec *rec);
t_bool	shadow_parallel_color(t_vec *light_dir, t_objects *obj, t_hitrec *rec);

t_color	parallel_specular_color(t_vec v, t_hitrec *rec, t_camera *camera);

#endif
