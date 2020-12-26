#include "parsing.h"

int	check_itoa(char **line)
{
	int	result;
	int	key;

	result = 0;
	key = 0;
	while (**line == ' ' || **line == '\t' || **line == '\n' || **line == ',' || ft_isalpha(**line))
		(*line)++;
	if (**line == '-')
	{
		key = 1;
		(*line)++;
	}
	while (**line >= '0' && **line <= '9')
	{
		result = result * 10 + **line - '0';
		(*line)++;
	}
	if (key)
		return (-result);
	return (result);
}

double	check_dtoa(char **line)
{
	double	result;
	double	dec;
	int		key;

	key = 0;
	result = 0;
	dec = 1;
	while (**line == ' ' || **line == '\t' || **line == '\n' || **line == ',' || ft_isalpha(**line))
		(*line)++;
	if (**line == '-')
	{
		(*line)++;
		key = 1;
	}
	while (**line >= '0' && **line <= '9')
	{
		result = result * 10 + **line - '0';
		(*line)++;
	}
	if (**line == '.')
		(*line)++;
	while (**line >= '0' && **line <= '9')
	{
		dec *= 10;
		result += (**line - '0') / dec;
		(*line)++;
	}
	if (key)
		return (-result);
	return (result);
}

int	parsing_check(t_camera *camera, t_objects **obj, t_std_set *s_set, char **line)
{
	if (**line == 's' && *(*line + 1) == 'p')
		obj_add_back(obj, set_object(SP, set_sphere(point3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), check_dtoa(line), vdivide(color(check_itoa(line), check_itoa(line), check_itoa(line)), 255.0))));
	else if (**line == 'p' && *(*line + 1) == 'l')
		obj_add_back(obj, set_object(PL, set_plane(point3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), vec3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), vdivide(color(check_itoa(line), check_itoa(line), check_itoa(line)), 255.0))));
	else if (**line == 's' && *(*line + 1) == 'q')
		obj_add_back(obj, set_object(SQ, set_square(point3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), vec3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), check_dtoa(line), vdivide(color(check_itoa(line), check_itoa(line), check_itoa(line)), 255.0))));
	else if (**line == 'c' && *(*line + 1) == 'y')
		obj_add_back(obj, set_object(CY, set_cylinder(point3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), vec3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), check_dtoa(line), check_dtoa(line), vdivide(color(check_itoa(line), check_itoa(line), check_itoa(line)), 255.0))));
	else if (**line == 't' && *(*line + 1) == 'r')
		obj_add_back(obj, set_object(TR, set_triangle(point3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), point3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), point3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), vdivide(color(check_itoa(line), check_itoa(line), check_itoa(line)), 255.0))));
	else if (**line == 'R')
		set_viewport(s_set, check_itoa(line), check_itoa(line));
	else if (**line == 'A')
		set_amblight(s_set, check_dtoa(line), vdivide(color(check_itoa(line), check_itoa(line), check_itoa(line)), 255.0));
	else if (**line == 'c')
		set_camera(camera, s_set, point3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), vec3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), check_itoa(line));
	else if (**line == 'l')
		obj_add_back(obj, set_object(LI, set_light(point3(check_dtoa(line), check_dtoa(line), check_dtoa(line)), check_dtoa(line), vdivide(color(check_itoa(line), check_itoa(line), check_itoa(line)), 255.0))));
	else
		return (0);
	return (1);
}

// 파싱에 성공하면 1, 아니면 0
int	parsing(t_camera *camera, t_objects **obj, t_std_set *s_set, char *rtname)
{
	int		fd;
	char	*line;
	char	*temp;

	fd = open(rtname, O_RDONLY);
	if (fd == -1)
	{
		dprintf(2, "parsing fail!!!!!!\n");
		return (-1);
	}
	while (get_next_line(fd, &line))
	{
		temp = line;
		parsing_check(camera, obj, s_set, &line);
		dprintf(2, "%s\n", temp);
		free(temp);
	}
	temp = line;
	parsing_check(camera, obj, s_set, &line);
	dprintf(2, "%s\n", temp);
	free(temp);
	return (1);
}