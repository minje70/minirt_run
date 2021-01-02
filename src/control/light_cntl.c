#include "control.h"

void	cntl_light_on(t_cntl *cntl)
{
	t_objects	*temp;

	cntl->mode = LIGM;
	if (cntl->selected == 0)
	{
		while (cntl->scene->world->type != LI)
			cntl->scene->world = cntl->scene->world->next;
		cntl->selected = cntl->scene->world;
	}
	printf("< light mode >\n[right arrow] key : next light\n");
}

void	cntl_light_on_and_off(t_cntl *cntl)
{
	if (cntl->light_on == LIGHT_OFF || cntl->light_on == RAINBOW)
	{
		cntl->light_on = LIGHT_ON;
		perror("light on(if you press o, light off)\n");
	}
	else
	{
		cntl->light_on = LIGHT_OFF;
		perror("light off(if you press o, light on)\n");
	}
	all_render(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}

void	cntl_rainbow_on_anc_off(t_cntl *cntl)
{
	if (cntl->light_on != RAINBOW)
	{
		cntl->light_on = RAINBOW;
		perror("rainbow on\n");
	}
	else
	{
		cntl->light_on = LIGHT_OFF;
		perror("rainbow off\n");
	}
	all_render(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}

void	cntl_light_select(t_cntl *cntl)
{
	t_objects	*temp;

	if (cntl->selected == 0 || cntl->selected->next == 0)
		temp = (t_objects *)cntl->scene->world;
	else
		temp = (t_objects *)cntl->selected->next;
	while (temp && temp->type != LI)
		temp = temp->next;
	if (temp == 0)
	{
		temp = (t_objects *)cntl->scene->world;
		while (temp && temp->type != LI)
			temp = temp->next;
		cntl->selected = temp;
		printf("마지막 조명입니다.\n");
	}
	else
	{
		cntl->selected = temp;
		printf("다음 조명입니다.\n");
	}
}

void	cntl_light_deselect(t_cntl *cntl)
{
	printf("light deselect\n");
	cntl->selected = NULL;
	cntl->mode = DEFM;
}

void	cntl_light_bright_up(t_cntl *cntl)
{
	double		brightness;
	t_color	*light_color;

	brightness = ((t_light *)(cntl->selected->data))->brightness;
	light_color = &((t_light *)(cntl->selected->data))->light_color;
	if (cntl->selected->type == LI)
	{
		((t_light *)(cntl->selected->data))->brightness += 0.1;
		if (((t_light *)(cntl->selected->data))->brightness > 1)
			((t_light *)(cntl->selected->data))->brightness = 1;
		*light_color = vdivide(*light_color, brightness);
		brightness = ((t_light *)(cntl->selected->data))->brightness;
		*light_color = vmult(*light_color, brightness);
	}
	printf("조명증가\n");
}

void	cntl_light_bright_down(t_cntl *cntl)
{
	double		brightness;
	t_color	*light_color;

	brightness = ((t_light *)(cntl->selected->data))->brightness;
	light_color = &((t_light *)(cntl->selected->data))->light_color;
	if (cntl->selected->type == LI)
	{
		((t_light *)(cntl->selected->data))->brightness -= 0.1;
		if (((t_light *)(cntl->selected->data))->brightness <= 0)
			((t_light *)(cntl->selected->data))->brightness = 0.000001;
		*light_color = vdivide(*light_color, brightness);
		brightness = ((t_light *)(cntl->selected->data))->brightness;
		*light_color = vmult(*light_color, brightness);
	}
	printf("조명감소\n");
}

void	cntl_light_translate_x_pos(t_cntl *cntl)
{
	if (cntl->selected->type == LI)
		((t_light *)(cntl->selected->data))->point.x += 0.3;
	printf("라이트 x이동\n");
}

void	cntl_light_translate_y_pos(t_cntl *cntl)
{
	if (cntl->selected->type == LI)
		((t_light *)(cntl->selected->data))->point.y += 0.3;
	printf("라이트 y이동\n");
}

void	cntl_light(t_cntl *cntl, int keycode)
{
	if (keycode == KEY_AR_R) // 광원 바꾸기. 오른쪽 방향키
		cntl_light_select(cntl);
	else if (keycode == KEY_X) // 광원 이동 x
		cntl_light_translate_x_pos(cntl);
	else if (keycode == KEY_V) // 광원 이동 v
		cntl_light_translate_y_pos(cntl);
	else if (keycode == KEY_ESC) // 선택 종료 esc
		cntl_light_deselect(cntl);
	else if (keycode == 24) // 밝기 밝게 =
		cntl_light_bright_up(cntl);
	else if (keycode == 27) // 밝기 어둡게 -
		cntl_light_bright_down(cntl);
	all_render(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}