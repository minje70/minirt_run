#include "parsing.h"

void	eerror(char *msg)
{
	perror(msg);
	exit(0);
}

int	check_itoa(char **line, int num)
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
	if (!(**line >= '0' && **line <= '9'))
		eerror("Error\n파일의 구조가 틀립니다.\n");
	while (**line >= '0' && **line <= '9')
	{
		result = result * 10 + **line - '0';
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
		result += (**line - '0') / dec;
		(*line)++;
	}
	if (key)
		return (-result);
	return (result);
}

int	parsing_check(t_cntl *cntl, char **line)
{
	if (**line == 's' && *(*line + 1) == 'p')
		obj_add_back(&cntl->scene->world, set_object(SP, set_sphere(point3(check_dtoa(line, 2), check_dtoa(line, 0), check_dtoa(line, 0)), check_dtoa(line, 0), vdivide(color(check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0)), 255.0))));
	else if (**line == 'p' && *(*line + 1) == 'l')
		obj_add_back(&cntl->scene->world, set_object(PL, set_plane(point3(check_dtoa(line, 2), check_dtoa(line, 0), check_dtoa(line, 0)), vec3(check_dtoa(line, 0), check_dtoa(line, 0), check_dtoa(line, 0)), vdivide(color(check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0)), 255.0))));
	else if (**line == 's' && *(*line + 1) == 'q')
		obj_add_back(&cntl->scene->world, set_object(SQ, set_square(point3(check_dtoa(line, 2), check_dtoa(line, 0), check_dtoa(line, 0)), vec3(check_dtoa(line, 0), check_dtoa(line, 0), check_dtoa(line, 0)), check_dtoa(line, 0), vdivide(color(check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0)), 255.0))));
	else if (**line == 'c' && *(*line + 1) == 'y')
		obj_add_back(&cntl->scene->world, set_object(CY, set_cylinder(point3(check_dtoa(line, 2), check_dtoa(line, 0), check_dtoa(line, 0)), vec3(check_dtoa(line, 0), check_dtoa(line, 0), check_dtoa(line, 0)), check_dtoa(line, 0), check_dtoa(line, 0), vdivide(color(check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0)), 255.0))));
	else if (**line == 't' && *(*line + 1) == 'r')
		obj_add_back(&cntl->scene->world, set_object(TR, set_triangle(point3(check_dtoa(line, 2), check_dtoa(line, 0), check_dtoa(line, 0)), point3(check_dtoa(line, 0), check_dtoa(line, 0), check_dtoa(line, 0)), point3(check_dtoa(line, 0), check_dtoa(line, 0), check_dtoa(line, 0)), vdivide(color(check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0)), 255.0))));
	else if (**line == 'c' && *(*line + 1) == 'u')
		obj_add_back(&cntl->scene->world, set_object(CU, set_cube(point3(check_dtoa(line, 2), check_dtoa(line, 0), check_dtoa(line, 0)), check_dtoa(line, 0), vdivide(color(check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0)), 255.0))));
	else if (**line == 'p' && *(*line + 1) == 'y')
		obj_add_back(&cntl->scene->world, set_object(PY, set_pyramid(point3(check_dtoa(line, 2), check_dtoa(line, 0), check_dtoa(line, 0)), check_dtoa(line, 0), check_dtoa(line, 0), vdivide(color(check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0)), 255.0))));
	else if (**line == 'R')
		set_viewport(&cntl->scene->canv, check_itoa(line, 1), check_itoa(line, 0));
	else if (**line == 'A')
		set_amblight(&cntl->scene->canv, check_dtoa(line, 1), vdivide(color(check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0)), 255.0));
	else if (**line == 'c')
		obj_add_back(&cntl->scene->cam_list, set_object(CAM, init_camera(point3(check_dtoa(line, 1), check_dtoa(line, 0), check_dtoa(line, 0)), vec3(check_dtoa(line, 0), check_dtoa(line, 0), check_dtoa(line, 0)), check_itoa(line, 0))));
	else if (**line == 'l')
		obj_add_back(&cntl->scene->world, set_object(LI, set_light(point3(check_dtoa(line, 1), check_dtoa(line, 0), check_dtoa(line, 0)), check_dtoa(line, 0), vdivide(color(check_itoa(line, 0), check_itoa(line, 0), check_itoa(line, 0)), 255.0))));
	else if (**line != 0)
		eerror("Error\n잘못된 식별자가 들어왔습니다.");
	return (1);
}

// 파싱에 성공하면 1, 아니면 0
int	parsing(t_cntl *cntl, char *rtname)
{
	int		fd;
	char	*line;
	char	*temp;

	fd = open(rtname, O_RDONLY);
	if (fd == -1)
	{
		perror("Parsing fail");
		exit(1);
	}
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