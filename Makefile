# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 11:46:52 by sdell-er          #+#    #+#              #
#    Updated: 2024/02/27 15:48:56 by sdell-er         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_C = client
NAME_S = server
MY_LIB = ./my_lib
LIB = ./my_lib/my_lib.a
SRC_C = ./srcs/client_bonus.c
SRC_S = ./srcs/server_bonus.c
OBJ_C = $(SRC_C:.c=.o)
OBJ_S = $(SRC_S:.c=.o)
CC = cc -g -Wall -Wextra -Werror

all: $(NAME_C) $(NAME_S)

$(NAME_C): $(OBJ_C)
	@make -C $(MY_LIB) > /dev/null
	@$(CC) $(OBJ_C) $(LIB) -o $(NAME_C) > /dev/null
	@echo "\e[0;93m[$(NAME_C)] compiled!\e[0m"

$(NAME_S): $(OBJ_S)
	@make -C $(MY_LIB) > /dev/null
	@$(CC) $(OBJ_S) $(LIB) -o $(NAME_S) > /dev/null
	@echo "\e[0;93m[$(NAME_S)] compiled!\e[0m"
	
%.o: %.c
	@$(CC) -c $< -o $@

clean:
	@make clean -C $(MY_LIB) > /dev/null
	@rm -f $(OBJ_C) $(OBJ_S)
	@echo "\e[0;91mcleaned!\e[0m"

fclean: clean
	@make fclean -C $(MY_LIB) > /dev/null
	@rm -f $(NAME_C) $(NAME_S)
	@echo "\e[0;91m[$(NAME_C)] deleted!\e[0m"
	@echo "\e[0;91m[$(NAME_S)] deleted!\e[0m"

re: fclean all

.PHONY: all clean fclean re
