#ifndef MLXUTIL_H
# define MLXUTIL_H
# include "structure.h"
# include <stdio.h>
# include <stdlib.h>

int	mlx_close(int keycode, t_cntl *cntl);
int red_x_close(int keycode, t_cntl *cntl);
int	mlx_point(int x, int y, t_cntl *cntl);

#endif