# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlintill <rlintill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/16 17:10:27 by rlintill          #+#    #+#              #
#    Updated: 2020/09/16 17:23:29 by rlintill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rlintill.filler

# files
SRC	=	main.c\
		free.c\
		heat.c\
		piece.c\
		utils.c

OBJ = $(SRC:.c=.o)

LIBFT_A = libft.a

# directories

SRC_DIR = ./src
OBJ_DIR = ./obj
LIB_DIR = ./libft/

# files with their paths
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

# compile
CC = gcc
HEADERS = -I includes
LIB_HEADERS =  -I $(LIB_DIR)includes 
CFLAGS = -c -Wall -Werror -Wextra
LIB = -L $(LIB_DIR) -lft

all: do_lib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) $(LIB_HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIB) -o $(NAME)
	@echo "\033[92m ------- $(NAME) built and ready ------- \033[0m"

do_lib:
	@make -C $(LIB_DIR)

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean
	@echo "\033[92m ------- $(NAME) cleaned ------- \033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIB_DIR) fclean
	@echo "\033[92m ------- $(NAME) fcleaned ------- \033[0m"

re: fclean all

.PHONY: all clean fclean re