/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:20:28 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:20:32 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <fcntl.h>
# include "structure.h"
# include "get_next_line.h"
# include "camera.h"
# include "hit.h"
# include "libft.h"
# include "uutil.h"

int		check_itoa(char **line, int num);
double	check_dtoa(char **line, int num);
int		parsing_check(t_cntl *cntl, char **line);
int		parsing(t_cntl *cntl, char *rtname);

#endif
