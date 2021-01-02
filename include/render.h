#ifndef RENDER_H
# define RENDER_H

# define THREAD 500

# include "structure.h"
# include "hit.h"
# include "pthread.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color);
void	all_render(t_cntl *cntl);
t_color	draw_rainbow(t_hitrec *rec);

#endif