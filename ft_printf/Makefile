NAME = libftprintf.a
AR = ar rc
CC = gcc
CFLAG = -Wall -Wextra -Werror
MKOBJDIR = mkdir -p obj
LIBFT = libft
LIBFTDIR = ./libdir
SRCDIR = ./src
OBJDIR = ./obj
SRCNAME = checking.c	\
		ft_printf.c		\
		cd_printing.c	\
		us_printing.c	\
		xp_printing.c	\
		xp_printing2.c	\
		per_printing.c	\
		ls_printing.c	\
		f_printing.c	\
		f_printing2.c	\
		n_printing.c	\
		putfunc.c		\
		util.c

OBJNAME = $(SRCNAME:.c=.o)
SRC = $(addprefix $(SRCDIR)/, $(SRCNAME))
OBJ = $(addprefix $(OBJDIR)/, $(OBJNAME))

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	@mv $(LIBFTDIR)/$(LIBFT).a $(NAME)
	@$(AR) $@ $(OBJ)
$(LIBFT) :
	@$(MAKE) -C $(LIBFTDIR) all
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(MKOBJDIR)
	@$(CC) $(CFLAG) -I ./ -c -o $@ $<
bonus : all

clean :
	@$(MAKE) -C $(LIBFTDIR) clean
	@rm -rf $(OBJ) a.out

fclean :
	@$(MAKE) -C $(LIBFTDIR) fclean
	@rm -rf $(OBJ) $(NAME) a.out
re : fclean all
