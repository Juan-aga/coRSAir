# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-aga <juan-aga@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 20:12:36 by juan-aga          #+#    #+#              #
#    Updated: 2023/05/16 20:19:38 by juan-aga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

	NAME	= coRSAir

#	INCLUDE	= ...

	HEADER	= -I ./inc/

	CFLAGS	= -Wall -Werror -Wextra -Wno-deprecated-declarations

	SRC		= src/main.c	\
			src/rsa.c		\
			src/utils.c

all		: $(NAME)

$(NAME) :
		gcc $(SRC) $(CFLAGS) $(HEADER) -lssl -lcrypto -o $(NAME)
				
