# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fregulie <fregulie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/16 03:39:31 by fregulie          #+#    #+#              #
#    Updated: 2021/09/29 18:51:17 by fregulie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
CC				=	clang
FLAGS			=	-Wall -Wextra

SRCS			=	main.c \
					init.c \
					threads.c \
					routine.c \
					eat.c \
					tools.c

PATH_I			=	./includes/
PATH_SRCS		=	./srcs/
PATH_OBJS		=	./.objs/

OBJS			=	$(SRCS:.c=.o)
PREFIX_OBJS		=	$(addprefix $(PATH_OBJS), $(OBJS))

all				:	$(PATH_OBJS) $(NAME)

$(PATH_OBJS)	:
					@mkdir -p $(PATH_OBJS)

$(NAME)			:	$(PREFIX_OBJS)
					@$(CC) -o $@ $(PREFIX_OBJS) $(FLAGS) -lpthread

$(PATH_OBJS)%.o	:	$(PATH_SRCS)%.c $(PATH_I)*.h
					@echo "Compiling "$<
					@$(CC) -o $@ -c $< -I $(PATH_I) $(FLAGS)

clean			:
					@rm -rf $(PATH_OBJS)

fclean			:	clean
					@rm -f $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re sanit
