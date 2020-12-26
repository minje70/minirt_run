#ifndef PARSING_H
# define PARSING_H
# include <fcntl.h>
# include "structure.h"
# include "get_next_line.h"
# include "camera.h"
# include "hit.h"
# include "libft.h"

int	check_itoa(char **line);
double	check_dtoa(char **line);
int	parsing_check(t_camera *camera, t_objects **obj, t_std_set *s_set, char **line);
int	parsing(t_camera *camera, t_objects **obj, t_std_set *s_set, char *rtname);

#endif