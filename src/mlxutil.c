# include "mlxutil.h"

int	mlx_point(int x, int y, t_cntl *cntl)
{
	dprintf(2, "%d, %d\n", x, y);
	return (0);
}

int	mlx_close(int keycode, t_cntl *cntl)
{
	if (keycode == 53)
	{
		perror("esc키를 누르셨습니다.\n종료합니다");
		exit(1);
	}
	return (0);
}

int red_x_close(int keycode, t_cntl *cntl)
{
	perror("x버튼을 누르셨습니다. \n종료합니다.");
	exit(1);
}