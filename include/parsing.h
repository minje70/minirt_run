#ifndef PARSING_H
# define PARSING_H
# include <fcntl.h>
# include "structure.h"
# include "get_next_line.h"
# include "camera.h"
# include "hit.h"
# include "libft.h"

int		check_itoa(char **line, int num);
double	check_dtoa(char **line, int num);
int		parsing_check(t_cntl *cntl, char **line);
int		parsing(t_cntl *cntl, char *rtname);
void	eerror(char *msg);

#endif