/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 02:06:41 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 02:06:58 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		check_itoa(char **line, int num)
{
	int	result;
	int	key;

	result = 0;
	key = 0;
	*line = *line + num;
	while (**line == ' ' || **line == '\t' || **line == '\n' || **line == ',')
		(*line)++;
	if (**line == '-')
	{
		key = 1;
		(*line)++;
	}
	if (!(**line >= '0' && **line <= '9'))
		eerror("Error\n파일의 구조가 틀립니다.\n");
	while (**line >= '0' && **line <= '9')
	{
		result = result * 10 + **line - '0';
		(*line)++;
	}
	if (key)
		return (-result);
	return (result);
}

void	check_dtoa_sub(char **line, double *result, double dec)
{
	if (!(**line >= '0' && **line <= '9'))
		eerror("Error\n파일의 구조가 틀립니다.\n");
	while (**line >= '0' && **line <= '9')
	{
		*result = *result * 10 + **line - '0';
		(*line)++;
	}
	if (**line == '.')
	{
		if (!(*(*line - 1) >= '0' && *(*line - 1) <= '9'))
			eerror("Error\n파일의 구조가 틀립니다.\n");
		(*line)++;
		if (!(**line >= '0' && **line <= '9'))
			eerror("Error\n파일의 구조가 틀립니다.\n");
	}
	while (**line >= '0' && **line <= '9')
	{
		dec *= 10;
		*result += (**line - '0') / dec;
		(*line)++;
	}
}

double	check_dtoa(char **line, int num)
{
	double	result;
	double	dec;
	int		key;

	key = 0;
	result = 0;
	dec = 1;
	*line = *line + num;
	while (**line == ' ' || **line == '\t' || **line == '\n' || **line == ',')
		(*line)++;
	if (**line == '-')
	{
		(*line)++;
		key = 1;
	}
	check_dtoa_sub(line, &result, dec);
	if (key)
		return (-result);
	return (result);
}

int		parsing(t_cntl *cntl, char *rtname)
{
	int		fd;
	char	*line;
	char	*temp;

	fd = open(rtname, O_RDONLY);
	if (fd == -1)
		eerror("Error\nParsing fail\n");
	while (get_next_line(fd, &line))
	{
		temp = line;
		while (*line == ' ' || *line == '\t')
			line++;
		parsing_check(cntl, &line);
		free(temp);
	}
	temp = line;
	parsing_check(cntl, &line);
	free(temp);
	return (1);
}
