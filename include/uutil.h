/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uutil.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:21:33 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:27:50 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UUTIL_H
# define UUTIL_H
# include <math.h>
# include "vector.h"
# include "structure.h"

double	degrees_to_radians(double degrees);
double	max_d(double d1, double d2);
t_bool	is_inside(t_triangle *tri, t_point3 p);
t_bool	is_inside_(t_point3 p1, t_point3 p2, t_point3 p3, t_point3 p);
void	rotate_v(t_point3 *point, t_rotate rotate);
void	rotate_iv(t_point3 *point, t_rotate rotate);
double	random_double();
void	eerror(char *msg);

#endif
