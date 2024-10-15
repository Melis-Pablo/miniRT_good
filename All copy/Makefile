################################################################################
#                                     CONFIG                                   #
################################################################################
NAME	:=	minirt
CC		:=	cc
FLAGS	:=	-Wall -Wextra -Werror
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################
SRCS	:=	main.c \
			check_ident.c \
			cleanup.c \
			get_next_line.c \
			get_utils.c \
			getters_acl.c \
			getters.c \
			ml_extras.c \
			parse_tools.c \
			print_lights.c \
			print_objs.c \
			print.c \
			in_shadow.c \
			ray_color.c \
			ray_color_tools.c \
			window_fill.c \
			render.c \
			utils.c \
			utils2.c \
			vector_ops.c \
			vector_ops2.c \

OBJS	:=	$(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}
################################################################################
#                                   COLORS                                     #
################################################################################
CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f
################################################################################
#                                  Makefile  objs                              #
################################################################################
UNAME		:=	$(shell uname)

ifeq ($(UNAME), Darwin)
$(NAME): ${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@ $(MAKE) -C mlx all >/dev/null 2>&1
			@ cp ./mlx/libmlx.a .
			$(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(OBJS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
			@echo "$(GREEN)$(NAME) created[0m ✔️"
endif

ifeq ($(UNAME), Linux)
$(NAME): ${OBJS}
			@echo "$(GREEN)Linux compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."

			$(CC) $(CFLAGS) -g3 -o $(NAME) $(OBJS) -Imlx_linux -Lmlx_linux -lmlx  -L/usr/lib -lXext -lX11 -lm
			@echo "$(GREEN)$(NAME) created[0m ✔️"
endif

all:		${NAME}

ifeq ($(UNAME), Darwin)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif

ifeq ($(UNAME), Linux)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif


ifeq ($(UNAME), Linux)
fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C mlx_linux clean 
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

ifeq ($(UNAME), Darwin)
fclean:		clean
			@ ${RM} ${NAME}
			@ rm libmlx.a
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

valgrind:	all
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) scenes/scene8.rt 50 50 1

#make -j4 valgrind

re:			fclean all

cleanly:	all clean

.PHONY:		all clean fclean re cleanly valgrind