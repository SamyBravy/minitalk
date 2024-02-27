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
BNAME_C = client_bonus
BNAME_S = server_bonus
MY_LIB = ./my_lib
LIB = ./my_lib/my_lib.a
SRC_C = ./Mandatory/client.c
SRC_S = ./Mandatory/server.c
BSRC_C = ./Bonus/client_bonus.c
BSRC_S = ./Bonus/server_bonus.c
OBJ_C = $(SRC_C:.c=.o)
OBJ_S = $(SRC_S:.c=.o)
BOBJ_C = $(BSRC_C:.c=.o)
BOBJ_S = $(BSRC_S:.c=.o)
CC = cc -g -Wall -Wextra -Werror

all: $(NAME_C) $(NAME_S)

bonus : $(BNAME_C) $(BNAME_S)

$(NAME_C): $(OBJ_C)
	@make -C $(MY_LIB)
	$(CC) $(OBJ_C) $(LIB) -o $(NAME_C)

$(NAME_S): $(OBJ_S)
	@make -C $(MY_LIB)
	$(CC) $(OBJ_S) $(LIB) -o $(NAME_S)
	
$(BNAME_C): $(BOBJ_C)
	@make -C $(MY_LIB)
	@$(CC) $(BOBJ_C) $(LIB) -o $(BNAME_C)

$(BNAME_S) : $(BOBJ_S)
	@make -C $(MY_LIB)
	@$(CC) $(BOBJ_S) $(LIB) -o $(BNAME_S)
%.o: %.c
	$(CC) -c $< -o $@

clean:
	make clean -C $(MY_LIB)
	rm -f $(OBJ_C) $(OBJ_S) $(BOBJ_C) $(BOBJ_S)

fclean: clean
	make fclean -C $(MY_LIB)
	rm -f $(NAME_C) $(NAME_S) $(BNAME_C) $(BNAME_S)

re: fclean all

rebonus : fclean bonus

.PHONY: all clean fclean re
