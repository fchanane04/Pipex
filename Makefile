# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/03 23:22:12 by fchanane          #+#    #+#              #
#    Updated: 2022/04/24 01:07:25 by fchanane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS	= pipex.h

NAME	=	pipex
  
CC		=	gcc

CFLAGS	= -Wall -Werror -Wextra

RM		=	rm -rf

SRC = 	errors.c\
      	libft_first.c\
		libft_second.c\
		tasks.c\
		leaks.c\
		pipex.c

OBJ = $(subst .c,.o,$(SRC))

all: $(NAME)

$(NAME): ${OBJ}
	$(CC) $(OBJ) -o $(NAME)

%.o : %.c
	@${CC} -c ${CFLAGS} $< -o $@
	

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

