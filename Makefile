# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jconcent <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/14 12:57:19 by sberic            #+#    #+#              #
#    Updated: 2020/11/11 19:58:42 by jconcent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
LIBFT = libft/libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj

INCLUDE = -I./include
INCLUDE += -I./libft/include

HEADERS = include/lem_in.h


SRCS = main.c
SRCS += copy_links_and_rooms.c
SRCS += end_with_error.c
SRCS += find_new_ways.c
SRCS += finding_paths.c
SRCS += hash.c
SRCS += links.c
SRCS += bellman_ford.c
SRCS += parsing.c
SRCS += print_map.c
SRCS += rooms.c
SRCS += run_ants.c
SRCS += short_way.c
SRCS += short_way_utilities.c
SRCS += short_way_utilities2.c
SRCS += suurballe.c
SRCS += free_lem.c

OBJS = $(SRCS:.c=.o)

SRCS_PATH = $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS_PATH = $(addprefix $(OBJ_DIR)/,$(OBJS))


.PHONY: clean fclean all re make_lib

all: $(LIBFT) $(NAME)

$(LIBFT) : make_lib
	@mkdir -p $(OBJ_DIR)

make_lib:
	@make -C ./libft/

$(NAME): $(OBJS_PATH) $(LIBFT) $(HEADERS)
	$(CC) -o $@ $(OBJS_PATH) $(LIBFT) $(INCLUDE)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS) Makefile
	$(CC) -o $@ -c $< $(INCLUDE) $(FLAGS)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C ./libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft/ fclean

re: fclean all

.PHONY: make_lib clean fclean re
