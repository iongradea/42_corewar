/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:22:13 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/14 15:40:57 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <sys/types.h>
# include <stdbool.h>
# include <limits.h>
# include <ncurses.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../../libft/inc/libft.h"
# include "../../libft/inc/get_next_line.h"
# include "../../libft/inc/ft_printf.h"
# include "op.h"

/*
** Some var
*/

# define UNDEFINED -1
# define PS_DEAD -1
# define MAX_NB_PLAYR 1000

/*
** Debugging and errors
*/

# define DEBUG 0

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

/*
** Options
*/

# define VERBOSE 0x01
# define GRAPHIC 0x02
# define DUMP 0x04
# define NCURSE 0x08

# define VERBOSE_DISPLAY 400

/*
** Parameters size
*/

# define OPCODE_SIZE 1
# define OCP_SIZE 1
# define REG_SIZE_P 1
# define IND_SIZE_P 2
# define DIR_SIZE_P(op) (g_op_tab[op].dir_size)

/*
** carry
*/

# define CARRY_TRUE 1
# define CARRY_FALSE 0
# define NO_CARRY -1

/*
** VM
** memory length for graphic visual
*/

# define MEM_LINE_LENGTH 64
# define NO_PLAYR -1

/*
** CPU operations
*/

# define IS_OP_CODE(i) (i <= 0x10 && i >= 0x01)
# define OP_TAB_INDEX(opcode) (opcode - 1)
# define IS_REG(nb) (nb < 16 && nb >= 0)
# define PARAM_OCP_CODE(op, arg_i) (((op) >> ((3 - arg_i) * 2)) & 0b11)
# define VALID_OCP_PART(ocp) (ocp != 0b00)
# define CHECK_OCP_END_00(ocp) (ocp & 0b11)
# define TOTAL_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 4)

/*
** Process structure
*/

typedef struct				s_ps
{
	char					*playr;
	int						uid;
	int						ps_uid;
	unsigned char			*code;
	int						code_size;
	int						reg[REG_NUMBER + 1];
	int						pc;
	int						live;
	int						op_size;
	int						opcode;
	int						color;
	int						fl;
	int						carry;
	int						cyc_len;
	struct s_ps				*next;
	struct s_ps				*prev;
}							t_ps;

typedef struct				s_arena
{
	char					hex;
	int						playr_uid;
	int						color;
	int						color_pc;
}							t_arena;

/*
** Virtual machine memory
*/

typedef struct				s_vm_mem
{
	unsigned char	mem[MEM_SIZE];
	int				cycle;
	int				real_cycle;
	int				cycle_to_die;
	int				ch_decr;
	int				check;
	int				opt;
	int				dump;
	int				display;
	int				ncurse;
	int				verbose;
	int				mem_uid[MEM_SIZE];
	unsigned char	mem_color[MEM_SIZE * 1000];
	int				mem_color_size;
	int				mem_color_ind;
	int				playr_uid[MAX_PLAYERS + 1];
	int				nb_players;
	int				lives;
	int				last_live;
	t_arena			a[MEM_SIZE];
	int				playr_live[MAX_PLAYERS + 1];
	t_ps			**ps_st;
}							t_vm_mem;

/*
** Operations structure
*/

typedef struct				s_op
{
	int						opcode;
	char					*mmemo;
	int						nb_param;
	int						param[3];
	int						cycle;
	char					*desc;
	int						set_carry;
	int						ocp_param;
	int						dir_size;
	int						(*fun)(t_vm_mem *, t_ps *, int);
}							t_op;

/*
** Parsing functions & initialization functions
*/

int							get_playr(int fd, t_ps **ps, int ac, char **av);
void						add_data_vm(t_vm_mem *vm, t_ps *ps);
t_vm_mem					*ft_new_mem(void);
int							ft_parse_opt(int ac, char **av, t_vm_mem *vm);
int							ft_usage(void);
void						ft_jmp_opt(int ac, char **av, int *i);
int							ft_check_ps_uid(t_ps *ps, int uid);
void						cpu_checks(t_vm_mem *vm, t_ps *ps);

/*
** CPU architecture
*/

int							cpu(t_vm_mem *vm, t_ps *ps);
int							exec_op(t_vm_mem *vm, t_ps *lst);
int							exec_op_2(t_ps *lst, t_vm_mem *vm, t_ps *tmp);
int							ft_nb_live(t_ps *ps);
void						ft_kill_reset_ps(t_vm_mem *vm);
int							ft_one_live_ps(t_ps *ps);
int							ft_mem_cir_pos(int pos);

/*
** CPU Operations
*/

int							ft_bin(t_vm_mem *vm, t_ps *ps, int opcode);
int							ft_add_sub(t_vm_mem *vm, t_ps *ps, int opcode);
int							ft_ld(t_vm_mem *vm, t_ps *ps, int opcode);
int							ft_st(t_vm_mem *vm, t_ps *ps, int opcode);
int							ft_aff(t_vm_mem *vm, t_ps *ps, int opcode);
int							ft_sti(t_vm_mem *vm, t_ps *ps, int opcode);
int							ft_sti_2(t_vm_mem *vm, t_ps *ps, int arg1, \
									int arg2);
int							ft_ldi(t_vm_mem *vm, t_ps *ps, int opcode);
int							ft_ldi_2(t_vm_mem *vm, t_ps *ps, int arg0, \
									int arg1);
int							ft_lldi(t_vm_mem *vm, t_ps *ps, int opcode);
int							ft_lldi_2(t_vm_mem *vm, t_ps *ps, int arg0, \
									int arg1);

/*
** CPU operations no ocp
*/

int							ft_live(t_vm_mem *vm, t_ps *ps, int opcode);
int							ft_zjmp(t_vm_mem *vm, t_ps *ps, int opcode);
int							ft_fork(t_vm_mem *vm, t_ps *ps, int opcode);

/*
** CPU Operations functions
** ft_get_arg : used to get the argument from the operations
** ft_get_val : used to get the value to be processed for the binary op
** ft_get_ind : used to get the value pointed by the indirect
*/

int							ft_is_type(t_vm_mem *vm, t_ps *ps, int arg_i, \
															unsigned int type);
int							ft_arg_size(t_vm_mem *vm, t_ps *ps, int arg_i);
int							ft_op_size(t_vm_mem *vm, t_ps *ps, int nb_arg);
int							ft_op_size_2(t_vm_mem *vm, t_ps *ps);
int							ft_get_arg(t_vm_mem *vm, t_ps *ps, int arg_i);
int							ft_get_val(t_ps *ps, t_vm_mem *vm, int arg, \
																int arg_i);
unsigned char				ft_get_ocp(t_vm_mem *vm, t_ps *ps, int arg_i);
int							check_ocp_fmt(t_vm_mem *vm, t_ps *ps, int nb_arg);
t_ps						*ft_cpy_playr(t_ps *ps);
void				ft_chg_mem_uid(t_vm_mem *vm, t_ps *ps, int pos, int size);
int							ft_get_ind(t_ps *ps, t_vm_mem *vm, int arg, \
																int idx_mod);

/*
** Print memory to console functions
*/

void						ft_prt_mem(t_vm_mem *vm, t_ps *ps);
void						ft_byte(t_vm_mem *vm, unsigned char c);
void						ft_hex(t_vm_mem *vm, unsigned char c);
void						add_bot_mem(t_vm_mem *vm);
void						add_top_mem(t_vm_mem *vm);
int							ft_add_c_mem(t_vm_mem *vm, char *str);
int							ft_is_pc(t_ps *ps, int index);

/*
** Annex functions
*/

void						ft_add_ps(t_ps *ps, t_ps *tmp);
int							ft_next_op(t_ps *ps, int carry_mod);
int							ft_get_code_size(int fd);
int							ft_prt_winner(t_vm_mem *vm, t_ps *ps);
int							ft_ps_uid(void);
int							is_invalid_reg(t_vm_mem *vm, t_ps *ps, \
											int arg_i, int arg);
int							error_msg(char *str);
void						ft_new_ps_sub(t_ps *ps);

/*
** Debug functions
*/

void						prt_op(void);
void						prt_ps(t_ps *ps);
void						prt_vm(t_vm_mem *vm);
void						prt_mem_uid(t_vm_mem *vm);
int							ft_main_debug(t_vm_mem *vm, t_ps *ps);

/*
** Ncurse functions
*/

void						ft_ncurse(t_vm_mem *vm, t_ps *ps);
void						ft_print_arena(t_vm_mem *vm, t_ps *ps);
void						ft_print_arena_2(t_vm_mem *vm, int i);
void						ft_init_ncurses(void);
void						ft_init_arena(t_vm_mem *vm);
void						ft_print_lives(t_vm_mem *vm, int i);
void						ft_print_game_stats(t_vm_mem *vm, t_ps *ps);

/*
** Free functions
*/

void						ft_free_ps(t_ps *ps);
void						ft_free_all_ps(t_ps *ps);

/*
** Global variable
** extern means it is available throughout the program
** static means it can only be used inside the .c file where it is defined
*/

extern const t_op			g_op_tab[17];
extern const unsigned char	g_color[6][10];
extern const unsigned char	g_colorpc[6][10];
extern unsigned int			g_verbose;

#endif
