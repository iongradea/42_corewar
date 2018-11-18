/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:22:13 by bbichero          #+#    #+#             */
/*   Updated: 2018/11/18 15:38:34 by bbichero         ###   ########.fr       */
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
# define ERROR_MSG(str) (ft_printf("%s\n", str))

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
# define REG_SIZE 1
# define IND_SIZE 2
# define DIR_SIZE(op) (op_tab[op].dir_size)

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

# define MEM_CIR_POS(pos) (((pos) % MEM_SIZE) < 0 ? (((pos) % MEM_SIZE) + MEM_SIZE) : ((pos) % MEM_SIZE))
# define IS_OP_CODE(i) (i <= 0x10 && i >= 0x01)
# define OP_TAB_INDEX(opcode) (opcode - 1)
# define IS_REG(nb) (nb < 16 && nb >= 0)
# define IS_INVALID_REG(vm, ps, arg_i, arg) (ft_is_type(vm, ps, arg_i, T_REG) && !IS_REG(arg))
# define PARAM_OCP_CODE(op, arg_i) (((op) >> ((3 - arg_i) * 2)) & 0b11)
# define VALID_OCP_PART(ocp) (ocp == 0b01 || ocp == 0b10 || ocp == 0b11)
# define CHECK_OCP_END_00(ocp) (ocp & 0b11)
# define TOTAL_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 4)

/*
** Process structure
*/

typedef struct		s_ps
{
	char			*playr;
	int				uid;
	unsigned char	*code;
	int				code_size;
	unsigned int	reg[REG_NUMBER];
	int				pc;
	int				live;
	int				op_size;
	int				opcode;
	int				color;
	int				nolor;
	int				carry;
	int				cyc_len;
	int				index_start;
	int				inst_len;
	char			string[TOTAL_SIZE + 1];
	char			inst[CHAMP_MAX_SIZE + 1];
	struct s_ps		*next;
}					t_ps;

typedef struct		s_arena
{
	char			hex;
	int				color;
	int				prevcolor;
	int				occupied;
	int				new_color_count;
}					t_arena;

/*
** Virtual machine memory
*/

typedef struct		s_vm_mem
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
	int				last_live;
	int				nb_players;
	int				lives;
	t_arena			a[MEM_SIZE];
	t_ps			ps[MAX_NB_PLAYR + 1];
}					t_vm_mem;

/*
** Operations structure
*/

typedef struct		s_op
{
	int				opcode;
	char			*mmemo;
	int				nb_param;
	int				param[3];
	int				cycle;
	char			*desc;
	int				set_carry;
	int				ocp_param;
	int				dir_size;
	int				(*fun)(t_vm_mem *, t_ps *, int);
}					t_op;

/*
** Parsing functions & initialization functions
*/

int					get_playr(int fd, t_ps **ps, int ac, char **av, t_vm_mem *vm);
void				add_data_vm(t_vm_mem *vm, t_ps *ps);
t_vm_mem			*ft_new_mem(void);
int					ft_parse_opt(int ac, char **av, t_vm_mem *vm);
int					ft_usage(void);
void				ft_jmp_opt(int ac, char **av, int *i);
int					ft_check_ps_uid(t_ps *ps, int uid);
void				cpu_checks(t_vm_mem *vm, t_ps *ps);

/*
** CPU architecture
*/

int					cpu(t_vm_mem *vm, t_ps *ps);
int					exec_op(t_vm_mem *vm, t_ps *lst);
int					ft_nb_live(t_vm_mem *vm);
void				ft_kill_reset_ps(t_vm_mem *vm);
void				ft_reset_ps(t_vm_mem *vm);
int					ft_one_live_ps(t_vm_mem *vm);

/*
** CPU Operations
*/

int					ft_bin(t_vm_mem *vm, t_ps *ps, int opcode);
int					ft_add_sub(t_vm_mem *vm, t_ps *ps, int opcode);
int					ft_ld(t_vm_mem *vm, t_ps *ps, int opcode);
int					ft_st(t_vm_mem *vm, t_ps *ps, int opcode);
int					ft_aff(t_vm_mem *vm, t_ps *ps, int opcode);
int					ft_sti(t_vm_mem *vm, t_ps *ps, int opcode);
int					ft_ldi(t_vm_mem *vm, t_ps *ps, int opcode);
int					ft_lldi(t_vm_mem *vm, t_ps *ps, int opcode);

/*
** CPU operations no ocp
*/

int					ft_live(t_vm_mem *vm, t_ps *ps, int opcode);
int					ft_zjmp(t_vm_mem *vm, t_ps *ps, int opcode);
int					ft_fork(t_vm_mem *vm, t_ps *ps, int opcode);

/*
** CPU Operations functions
*/

int					ft_is_type(t_vm_mem *vm, t_ps *ps, int arg_i, \
		unsigned int type);
int					ft_arg_size(t_vm_mem *vm, t_ps *ps, int arg_i);
int					ft_op_size(t_vm_mem *vm, t_ps *ps, int nb_arg);
unsigned int		ft_get_arg(t_vm_mem *vm, t_ps *ps, int arg_i);
unsigned int		ft_get_val(t_ps *ps, t_vm_mem *vm, \
		unsigned int arg, int arg_i);
unsigned char		ft_get_ocp(t_vm_mem *vm, t_ps *ps, int arg_i);
int					check_ocp_fmt(t_vm_mem *vm, t_ps *ps, int nb_arg);
t_ps				*ft_cpy_playr(t_ps *ps, t_vm_mem *vm);
void				ft_chg_mem_uid(t_vm_mem *vm, t_ps *ps, int pos, \
		int size);

/*
** Print memory to console functions
*/

void				ft_prt_mem(t_vm_mem *vm);
void				ft_byte(t_vm_mem *vm, unsigned char c);
void				ft_hex(t_vm_mem *vm, unsigned char c);
void				add_bot_mem(t_vm_mem *vm);
void				add_top_mem(t_vm_mem *vm);
int					ft_add_c_mem(t_vm_mem *vm, char *str);

/*
** Annex functions
*/

void				ft_add_ps(t_ps *ps, t_ps *tmp, t_vm_mem *vm);
int					ft_next_op(t_ps *ps, int carry_mod);
int					ft_get_code_size(int fd);
int					ft_prt_winner(t_vm_mem *vm);

/*
** Debug functions
*/

void				prt_op(void);
void				prt_ps(t_ps *ps);
void				prt_vm(t_vm_mem *vm);
void				prt_mem_uid(t_vm_mem *vm);
int					ft_main_debug(t_vm_mem *vm, t_ps *ps);

/*
** Ncurse functions
*/

void		ft_ncurse(t_vm_mem *vm);
void 		ft_init_ncurses(void);
void		ft_init_arena(t_vm_mem *vm);
void		ft_print_arena(t_vm_mem *vm);
void		ft_print_test(void);
void		ft_print_game_stats(t_vm_mem *vm);

void		ft_parsing(t_vm_mem *vm, t_ps *ps);
void		ft_build_arena(t_vm_mem *vm);
void		ft_player_to_arena(t_vm_mem *vm, int i, int *k);

void		ft_print_lives(t_vm_mem *vm, int i);

/*
** Global variable
** extern means it is available throughout the program
** static means it can only be used inside the .c file where it is defined
*/

extern const t_op			op_tab[17];
extern const unsigned char	g_color[6][10];
extern const unsigned char	g_colorpc[6][10];
extern unsigned int			g_verbose;

#endif
