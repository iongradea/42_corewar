# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igradea <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/11 19:01:51 by igradea           #+#    #+#              #
#    Updated: 2019/01/09 15:53:17 by igradea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

# Compiler
CC = gcc

# Source files
SRC = main.c parse_inst.c parse_inst_2.c op.c ft_debug.c ft_ch_args.c \
			ft_annex.c ft_ch_calc_args.c ft_inst_size.c calc_args.c \
			create_out_file.c ft_free.c ft_annex_2.c get_progname.c \
			get_progcomment.c 

SRCS = $(addprefix ./$(SRC_DIR)/, $(SRC))

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = bin
LBFT_DIR = ../libft

# Libraries
LIBFT_LIB = -lftprintf

# Include
INC_H = op.h asm.h
INCS_H = $(addprefix ./$(INC_DIR)/, $(INC_H))


# Others commands
RM = /bin/rm

# binaries
OBJ = $(SRC:.c=.o)

OBJS = $(addprefix ./$(OBJ_DIR)/, $(OBJ))

# Flags, libraries, include
# Several compile modes are defined: no flags, debug, standard
ifdef MODE
ifeq ($(MODE), no)
endif
ifeq ($(MODE), debug)
	CFLAGS = -g
endif
ifeq ($(MODE), bug_address)
	CFLAGS = -g3 -fsanitize=address
endif
else
	CFLAGS = -Wall -Wextra -Werror
endif

all: $(NAME)

# compiling run binary
$(NAME): $(OBJS)
	$(MAKE) -C $(LBFT_DIR) MODE=$(MODE)
	$(CC) $(CFLAGS) $^ -L$(LBFT_DIR) $(LIBFT_LIB) -o $@

# compiling binaries
./$(OBJ_DIR)/%.o: ./$(SRC_DIR)/%.c $(INCS_H)
	@mkdir ./$(OBJ_DIR) 2> /dev/null || true
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LBFT_DIR) clean
	$(RM) -rfv $(OBJ_DIR) 2> /dev/null || true

fclean: clean
	$(MAKE) -C $(LBFT_DIR) fclean
	$(RM) -rfv $(NAME)

re: fclean all

# Non-file targets
.PHONY: all, re, clean, fclean
