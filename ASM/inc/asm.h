/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/07 21:49:38 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdbool.h>
# include <limits.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "op.h"
# include "../../libft/inc/libft.h"
# include "../../libft/inc/ft_printf.h"
# include "../../libft/inc/get_next_line.h"

# define ERROR -1
# define UNDEFINED -1
# define DEBUG 1

# define NB_ARG_MAX 3

/*
** opcode starts at 1
*/

# define OP_TAB_INDEX(opcode) (opcode - 1)

/*
** first argument is the name of the instruction
*/

# define ARG_INDEX(i) (i + 1)

# define REG_SIZE 1
# define IND_SIZE 2
# define DIR_SIZE(opcode) (op_tab[OP_TAB_INDEX(opcode)].dir_size)

# define FL_STANDARD 0
# define FL_NAME 0b1
# define FL_NAME_LINES 0b10
# define FL_COMMENT 0b100
# define FL_COMMENT_LINES 0b1000
# define DEL_CHAR '"'

/*
** Operation codes
*/

# define LIVE 0x01
# define LD 0x02
# define ST 0x03
# define ADD 0x04
# define SUB 0x05
# define AND 0x06
# define OR 0x07
# define XOR 0x08
# define ZJMP 0x09
# define LDI 0x0a
# define STI 0x0b
# define FORK 0x0c
# define LLD 0x0d
# define LLDI 0x0e
# define LFORK 0x0f
# define AFF 0x10

# define NB_OP 16

# define OCP_DIR 0b10
# define OCP_IND 0b11
# define OCP_REG 0b01

typedef struct		s_inst
{
	int				opcode;
	char 			*line;
	char			*args[1 + NB_ARG_MAX + 1];
	char			*label;
	struct s_inst	*n;
	struct s_inst	*p;
	int				ocp;
	int				param[NB_ARG_MAX];
	int				size;
}					t_inst;

/*
** Operations structure
*/

typedef struct		s_op
{
	int				opcode;
	char			*mmemo;
	int				nb_param;
	int				param[4];
	int				cycle;
	char			*desc;
	int				set_carry;
	int				ocp_param;
	int				dir_size;
}					t_op;

/*
** parsing instructions
*/

int					get_inst(char *line, t_inst **inst, t_header *head);
int					ft_ch_opcode(char *str);
int					ft_ret_opcode(char *str);
int					ft_ch_err_lab(char *str);
int					ft_ch_rm_lab_c(char **str);

/*
** check instructions
*/

int					ch_all_inst(t_inst *inst);
int					ch_one_inst(t_inst *tmp, t_inst *inst);

/*
** size and arguments value
*/

int					calc_one_inst_size(t_inst *tmp);
int				calc_all_size(t_inst *inst);
int					ft_is_lab(char *arg);
int					ft_is_reg(char *str);
int					ft_is_ind(char *str);
int					ft_is_dir(char *str);
int					ft_arg_size(char *arg, int opcode);
void				calc_all_arg(t_inst *inst);

/*
** print out instruction to .cor file
*/

void				out_all_inst(int fd, t_inst *inst);
void				out_header(int fd, t_header *head, int size);

/*
** free instruction list & header
*/

void				ft_free_all_inst(t_inst *inst);
void				ft_free_head(t_header *head);

/*
** annex et annex_2 et get_progname et get_comment
*/

int					ft_is_valid_opcode(int opcode);
int					ft_is_empty_line(char *line);
char				*s_to_cor(char *str);
int				ft_is_special_line(char *line);
//int					get_prog_name(char *line, int *flag, t_header *head);
int 	get_prog_name(char *line, int *flag, t_header *head);
int 	get_prog_comment(char *line, int *flag, t_header *head);
int 	ft_ch_cmd_error(char *str);
int 			IS_NAME_LINE(char *line);
int 			IS_COMMENT_LINE(char *line);
t_inst		*ft_new_inst(char *line);
int 	 ERROR_MSG(char *msg);

/*
** debug
*/

void				prt_inst(t_inst *inst);
void				prt_tab(char **tab);
void				prt_one_inst(t_inst *inst);

extern const t_op	op_tab[17];

#endif
