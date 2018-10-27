# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igradea <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/11 19:01:51 by igradea           #+#    #+#              #
#    Updated: 2018/10/27 12:52:12 by bbichero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

# colors
Y = \033[0;33m
R = \033[0;31m
G = \033[0;32m
E = \033[39m

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

all: libft $(NAME)

# compiling run binary
$(NAME): $(OBJS)
	@echo "$(Y)[COMPILING VM FILES]$(E)"
	@echo "$(G)$(CC) $(CFLAGS) $^ -L$(LBFT_DIR) $(LIBFT_LIB) -o $@$(E)"
	@$(CC) $(CFLAGS) $^ -L$(LBFT_DIR) $(LIBFT_LIB) -o $@
	@echo "$(Y)[COMPILLING DONE]"

# compiling binaries
./$(OBJ_DIR)/%.o: ./$(SRC_DIR)/%.c $(INCS_H)
	@mkdir ./$(OBJ_DIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(R)[CLEANING VM FILES]$(E)"
	@$(MAKE) -C $(LBFT_DIR) clean
	@$(RM) -rfv $(NAME)
	@$(RM) -rfv $(OBJ_DIR) 2> /dev/null || true
	@echo "$(R)[CLEANING DONE]$(E)"

fclean: clean
	@$(RM) -rfv $(NAME)
	@$(MAKE) -C $(LBFT_DIR) fclean

libft:
	@echo "$(Y)[COMPILING LIBFT]$(E)"
	@echo "$(G)$(MAKE) -C $(LBFT_DIR) MODE=$(MODE)$(E)"
	@$(MAKE) -C $(LBFT_DIR) MODE=$(MODE)
	@echo "$(Y)[COMPILATION DONE]$(E)"

re: fclean all

# Non-file targets
.PHONY: all, re, clean, fclean
