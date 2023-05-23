# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 20:12:36 by juan-aga          #+#    #+#              #
#    Updated: 2023/05/22 16:20:42 by juan-aga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

	NAME	= coRSAir

	LIBS	= -L/Users/juan-aga/.brew/opt/openssl@3/lib -lssl -lcrypto

	HEADER	= -I ./inc/ -I /Users/juan-aga/.brew/opt/openssl@3/include/

	CFLAGS	= -Wall -Werror -Wextra -Wno-deprecated-declarations

	SRC		= src/main.c	\
			src/rsa.c		\
			src/utils.c

all		: $(NAME)

$(NAME) : $(OBJ)
		gcc -g $(SRC) $(HEADER) $(CFLAGS) $(LIBS) -o $(NAME)

re		:
		rm $(NAME)
		make $(NAME)
