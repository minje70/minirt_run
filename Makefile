NAME = minirt
all :
	# @$(MAKE) -C ./ft_printf all
	# @$(MAKE) -C ./mlx all
	@$(CC) -g3 -fsanitize=address -L./ft_printf -lftprintf -Lmlx -I ./ft_printf -I ./ft_printf/libdir -I ./mlx -I ./include ./src/*.c -lmlx -framework OpenGL -framework AppKit -o $(NAME)
clean :
	# @$(MAKE) -C ./ft_printf fclean
	# @$(MAKE) -C ./mlx clean
	@rm -rf $(NAME)
re : clean all

run : re
	./$(NAME)
ppm : re
	@./$(NAME) > result.ppm
	@open result.ppm
.PHONY : all run ppm clean re
