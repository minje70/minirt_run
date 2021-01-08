/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 12:52:55 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 20:03:23 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	object_msg(void)
{
	system("clear");
	ft_printf("< object mode >\n");
	ft_printf("[press X] : x move\n[press V] : y move\n");
	ft_printf("[press R] : rotate mode\n[press ArrowUp] : scale up\n");
	ft_printf("[press ArrowDown] : scale down\n[press ESC] : exit\n");
}

void	camera_msg(void)
{
	system("clear");
	ft_printf("< camera mode >\n[right arrow] key : next camera\n");
	ft_printf("[w,a,s,d] : move\n[q,e]");
	ft_printf(" key : fov\n[mouse click, wheel] : rotate\n");
	ft_printf("to default mode : [esc] key\n");
}

void	light_msg(void)
{
	system("clear");
	ft_printf("< light mode >\n[right arrow] : next light\n[press X] :
				x move\n");
	ft_printf("[press V] : y move\n[Up Arrow] : bright up\n");
	ft_printf("[Down Arrow] : bright down\n[press ESC] : default mode\n");
}

void	default_msg(void)
{
	system("clear");
	ft_printf("< default mode >\n");
	ft_printf("[object Click] : select object\n");
	ft_printf("[press C] : camera mode\n");
	ft_printf("[press L] : light mode\n");
	ft_printf("[press T] : rainbow mode\n");
	ft_printf("[press O] : light off render\n");
	ft_printf("[press R] : antialiasing\n");
}
