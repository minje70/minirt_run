#include "control.h"

void		cntl_object(int keycode, t_cntl *cntl)
{
	clock_t start, end;
	if (keycode == KEY_X)
		cntl_object_translate_x_pos(cntl);
	else if (keycode == KEY_V)
		cntl_object_translate_y_pos(cntl);
	else if (keycode == KEY_AR_U)
		cntl_object_u_scale(cntl);
	else if (keycode == KEY_AR_D)
		cntl_object_d_scale(cntl);
	else if (keycode == KEY_ESC)
		cntl_object_deselect(cntl);
	else if (keycode == KEY_R) // key R
		cntl_object_rotate(cntl);
	all_render(cntl);
	start = clock();
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
	end = clock();
	printf("image_towindow하는시간%f\n", ((double)end - start)/CLOCKS_PER_SEC);
}

void		cntl_object_select(int button, int x, int y, t_cntl *cntl)
{
	double		u;
	double		v;
	t_ray		r;
	t_hitrec	rec;

	printf("button: %d, x:%d, y:%d\n",button, x, y);
	if (button != 1)// 좌클릭 아닐 때,
		printf("If you want to select object, do left click!\n");
	else
	{
		rec.tmin = 0.001;
		rec.tmax = infinity;
		u = (double)x / (cntl->scene->canv.width - 1);
		v = (double)y / (cntl->scene->canv.height - 1);
		r = ray(cntl->scene->cam_onair->origin, vminus(vminus(vminus(cntl->scene->cam_onair->left_top_corner, vmult(cntl->scene->cam_onair->horizontal, u)), vmult(cntl->scene->cam_onair->vertical, v)), cntl->scene->cam_onair->origin));
		// u = (double)x / (cntl->scene->canv.width - 1);
		// v = (double)(cntl->scene->canv.height - y) / (cntl->scene->canv.height - 1);
		// r.orig = cntl->scene->cam_onair->origin;
		// r.dir = vunit(vminus(vplus(vplus(cntl->scene->cam_onair->left_top_corner, vmult(cntl->scene->cam_onair->horizontal, u)), vmult(cntl->scene->cam_onair->vertical, v)), cntl->scene->cam_onair->origin));
		if (hit(&r, &rec, cntl->scene->world))
		{
			cntl->selected = rec.obj;
			cntl->mode = 1;
			printf("An object was selected!\n!Deselct key : ESC\n");
		}
		else
		{
			cntl->selected = NULL;
			printf("There is no object!\n");
		}
	}
}

void		cntl_object_deselect(t_cntl *cntl)
{
	cntl->mode = 0;
	cntl->selected = NULL;
	printf("< Now default mode >\n");
}

int	is_double(char *str)
{
	char *start_point;

	start_point = str;
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
		++str;
	if (*str == '.')
		++str;
	while (ft_isdigit(*str))
		++str;
	if (*str == 0)
		return (0);
	printf("Rotation value must be number\n");
	printf("** INPUT ERROR **\n");
	printf("** your input: \"%s\" **\n", str);
	return (-1);
}

void		cntl_object_rotate(t_cntl *cntl) // move.c 파일에 있는 각 type의 rotate 함수를 사용해보자.
{
	t_objects	*selected;
	t_vec		r_deg;
	char		*input;
	char		*temp;

	selected = cntl->selected;
	if (selected->type == SP || selected->type == TR)
		return ;
	printf("\n*** TYPE Add rotation in degree ***\n");
	printf("current_rotate is : (x:%.2f, y:%.2f, z:%.2f)\nx add:\n ", selected->rotate.x, selected->rotate.y, selected->rotate.z);
	get_next_line(0, &input);
	temp = input;
	if(is_double(input) == -1)
	{
		free(temp);
		return ;
	}
	selected->rotate.x += check_dtoa(&input, 0);
	printf("y add:\n");
	free(temp);
	get_next_line(0, &input);
	temp = input;
	if(is_double(input) == -1)
	{
		free(temp);
		return ;
	}
	selected->rotate.y += check_dtoa(&input, 0);
	printf("z add:\n");
	free(temp);
	get_next_line(0, &input);
	temp = input;
	if(is_double(input) == -1)
	{
		free(temp);
		return ;
	}
	selected->rotate.z += check_dtoa(&input, 0);
	free(temp);
	printf("Rotation Add success\n");
	printf("current_rotate is : (x:%.2f, y:%.2f, z:%.2f)\n", selected->rotate.x, selected->rotate.y, selected->rotate.z);
}

void		cntl_object_translate_x_pos(t_cntl *cntl)
{
	if (cntl->selected->type == SP)
			((t_sphere *)(cntl->selected->data))->center.x += 0.3;
}

void		cntl_object_translate_y_pos(t_cntl *cntl)
{
	if (cntl->selected->type == SP)
			((t_sphere *)(cntl->selected->data))->center.y += 0.3;
}

void		cntl_object_u_scale(t_cntl *cntl)
{
	t_cylinder	*cyl;

	if (cntl->selected->type == SP)
		((t_sphere *)(cntl->selected->data))->radius += 0.05;
	if (cntl->selected->type == CY)
	{
		cyl = (t_cylinder *)(cntl->selected->data);
		cyl->r += 0.05;
		cyl->h += 0.05;
		cyl->p2 = vplus(cyl->p, vmult(cyl->v, cyl->h));
	}
	if (cntl->selected->type == SQ)
		((t_square *)(cntl->selected->data))->len += 0.05;
}

void		cntl_object_d_scale(t_cntl *cntl)
{
	t_cylinder	*cyl;

	if (cntl->selected->type == SP)
	{
		((t_sphere *)(cntl->selected->data))->radius -= 0.05;
		if (((t_sphere *)(cntl->selected->data))->radius < 0)
			((t_sphere *)(cntl->selected->data))->radius = 0;
	}
	if (cntl->selected->type == CY)
	{
		cyl = (t_cylinder *)(cntl->selected->data);
		cyl->r -= 0.05;
		cyl->h -= 0.05;
		if (cyl->r < 0)
			cyl->r = 0;
		if (cyl->h < 0)
			cyl->h = 0;
		cyl->p2 = vplus(cyl->p, vmult(cyl->v, cyl->h));
	}
	if (cntl->selected->type == SQ)
	{
		((t_square *)(cntl->selected->data))->len -= 0.05;
		if (((t_square *)(cntl->selected->data))->len < 0)
			((t_square *)(cntl->selected->data))->len = 0;
	}
}
