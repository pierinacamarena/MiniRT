NAME	=	mini_rt

OBJS	=	main.o\
			vector.o\
			ray.o\
			color.o\
			screen.o\
			parse.o\
			lexer.o\
			scanner.o\
			free.o\
			free2.o\
			list.o\
			ray_color.o\
			utils.o\
			hit.o\
			init.o\
			color_image.o\
			init_obj1.o\
			init_obj2.o\
			parse_utils.o\
			init_obj_utils.o

HEADS	=	params.h\
			vector.h\
			ray.h\
			color.h\
			screen.h\
			parse.h\
			lexer.h\
			scanner.h\
			free.h\
			list.h\
			ray_color.h\
			utils.h\
			hit.h\
			init.h\
			color_image.h

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(OBJS):	%.o:%.c $(HEADS)
			$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
