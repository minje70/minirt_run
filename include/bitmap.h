/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:22:20 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:28:27 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

typedef struct s_bmph_file		t_bmph_file;
typedef struct s_bmph_info		t_bmph_info;
typedef struct s_bmph			t_bmph;

# pragma pack(push, 1)

struct	s_bmph_file
{
	unsigned char	magic1;
	unsigned char	magic2;
	unsigned int	size;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned int	offset;
};

struct	s_bmph_info
{
	unsigned int	size;
	int				width;
	int				height;
	unsigned short	plane;
	unsigned short	bit_per_pixel;
	unsigned int	compression;
	unsigned int	size_image;
	unsigned int	resolution_x;
	unsigned int	resolution_y;
	unsigned int	color_used;
	unsigned int	color_important;
};

struct	s_bmph
{
	t_bmph_file		file_h;
	t_bmph_info		info_h;
};

# pragma pack(pop)

#endif
