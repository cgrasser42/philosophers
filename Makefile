# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/31 17:49:26 by cgrasser          #+#    #+#              #
#    Updated: 2025/06/14 17:03:35 by cgrasser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = build
	
SRC = data/data.c data/philo.c data/mutex.c data/fork.c \
	main.c utils.c

OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

all: $(BIN)

$(BIN): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(BIN)

re: fclean all

.PHONY: all clean fclean re