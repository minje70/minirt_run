#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <time.h>
#include "get_next_line.h"
#include "structure.h"
#include "camera.h"
#include "vector.h"
#include "ray.h"
#include "hit.h"
#include "lighting.h"
#include "parsing.h"
#include "mlxutil.h"
#include "render.h"
#include "control.h"

void	scene_init(t_cntl *cntl)
{
	if ((cntl->scene = (t_scene *)malloc(sizeof(t_scene))) == 0)
		eerror("Error\nSceneinit Fail!!!\n");
	cntl->scene->world = 0;
	cntl->scene->canv.height = -1;
	cntl->scene->canv.width = -1;
	cntl->scene->canv.amb_light = -1;
	cntl->scene->canv.color = color(-1, -1, -1);
	cntl->scene->cam_list = 0;
	cntl->mode = 0;
	cntl->light_on = LIGHT_ON;
	if ((cntl->img = (t_data *)malloc(sizeof(t_data))) == 0)
		eerror("Error\nSceneinit Fail!!!\n");
}

int		main(int ac, char **av)
{
	t_cntl		cntl;
	t_std_set	s_set;

	if (ac != 2 && ac != 3)
	{
		perror("인수 갯수틀립니다.");
		exit(1);
	}
	scene_init(&cntl);
	parsing(&cntl, av[1]);
	cntl_display_resolution(&cntl);
	cntl.scene->cam_onair = cntl.scene->cam_list->data;
	set_camera(cntl.scene->cam_onair);
	cntl.mlx = mlx_init(); // mlx를 사용하기 전 초기화 해주는 함수. 최근 MLX인스턴스를 리턴함.
	cntl.win = mlx_new_window(cntl.mlx, cntl.scene->canv.width, cntl.scene->canv.height, "mijeong's minirt!"); // MLX인스턴스, 가로길이, 세로길이, 
	cntl.img->img = mlx_new_image(cntl.mlx, cntl.scene->canv.width, cntl.scene->canv.height); // bit를 하나하나 찍는거 보다는 이미지로 저장을 해서 한번에 찍어내는게 효율적이기 때문에 사용.
	cntl.img->addr = mlx_get_data_addr(cntl.img->img, &cntl.img->bits_per_pixel, &cntl.img->line_length, &cntl.img->endian);
	cntl.scene->img = cntl.img;
	all_render(&cntl);
	if (ac == 3 && ft_strncmp("--save", av[2], 6) == 0)
		bmp_save(&cntl);
	mlx_put_image_to_window(cntl.mlx, cntl.win, cntl.img->img, 0, 0);
	my_mlx_control(&cntl);
}