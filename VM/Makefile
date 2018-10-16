# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igradea <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/11 19:01:51 by igradea           #+#    #+#              #
#    Updated: 2018/04/23 14:10:39 by igradea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

# Compiler
CC = gcc

# Source files
SRC = main.c op.c debug.c get_playr.c ft_annex.c vm_mem.c \
			ft_op_fun.c ft_op_fun_2.c ft_prt_mem.c ft_prt_mem_2.c\
			cpu.c cpu_2.c exec_op.c parse_opt.c \
			ft_bin_add_sub_ld_st.c \
			ft_aff_sti_ldi_lldi.c \
			ft_live_zjmp_fork_lfork.c \


SRCS = $(addprefix ./$(SRC_DIR)/, $(SRC))

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = bin
LBFT_DIR = ../libft

# Libraries
LIBFT_LIB = -lftprintf

# Include
INC_H = vm.h op.h
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
	$(RM) -rfv $(NAME)
	$(RM) -rfv $(OBJ_DIR) 2> /dev/null || true

fclean: clean
	$(MAKE) -C $(LBFT_DIR) fclean
	$(RM) -rfv $(NAME)

re: fclean all

# Non-file targets
.PHONY: all, re, clean, fclean
