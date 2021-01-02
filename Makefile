NAME = minirt
all :
	# @$(MAKE) -C ./ft_printf all
	# @$(MAKE) -C ./mlx all
	@$(CC) -g3 -fsanitize=address -O3 -L./ft_printf -lftprintf -Lmlx -I ./ft_printf -I ./ft_printf/libdir -I ./mlx -I ./include ./src/*/*.c ./src/*.c -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	install_name_tool -change libmlx.dylib ./mlx/libmlx.dylib $(NAME)
clean :
	# @$(MAKE) -C ./ft_printf fclean
	# @$(MAKE) -C ./mlx clean
	@rm -rf $(NAME)
re : clean all

run : re
	./$(NAME) temp.rt
ppm : re
	@./$(NAME) > result.ppm
	@open result.ppm
.PHONY : all run ppm clean re
