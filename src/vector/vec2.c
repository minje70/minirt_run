/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:00:51 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:01:36 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double		vlength(t_vec vec)
{
	return (sqrt(vlength2(vec)));
}

t_vec		vplus(t_vec vec, t_vec vec2)
{
	vec.x += vec2.x;
	vec.y += vec2.y;
	vec.z += vec2.z;
	return (vec);
}

t_vec		vplus_(t_vec vec, double x, double y, double z)
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
	return (vec);
}

t_vec		vminus(t_vec vec, t_vec vec2)
{
	vec.x -= vec2.x;
	vec.y -= vec2.y;
	vec.z -= vec2.z;
	return (vec);
}

t_vec		vminus_(t_vec vec, double x, double y, double z)
{
	vec.x -= x;
	vec.y -= y;
	vec.z -= z;
	return (vec);
}
