# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 11:35:19 by rreis-de          #+#    #+#              #
#    Updated: 2023/03/07 16:32:55 by rreis-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BONUS = bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

RM = rm -f

SRCS = pipex.c \
		ft_split.c \
		children.c \
		utils.c \
		path.c 

SRCS_BONUS = pipex_bonus.c \
				ft_split.c \
				utils.c \
				path.c \
				list_utils.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean $(NAME) $(BONUS)

.PHONY: all clean fclean re