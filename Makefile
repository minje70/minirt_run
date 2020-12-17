NAME = minirt
all :
	gcc -g3 -fsanitize=address ./src/*.c -o $(NAME) -I./include
clean :
	rm -rf $(NAME)
re : clean all
run : all
	./$(NAME)
ppm : re
	./$(NAME) > result.ppm
	open result.ppm
.PHONY : all clean re