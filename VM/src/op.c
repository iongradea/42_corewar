/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:44:35 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

const t_op op_tab[17] =
{
	{LIVE, "live", 1, {T_DIR, 0, 0}, 10, "alive", false, false, 4, &ft_live},
	{LD, "ld", 2, {T_DIR | T_IND, T_REG, 0}, 5, "load", true, true, 4, &ft_ld},
	{ST, "st", 2, {T_REG, T_IND | T_REG, 0}, 5, "store", false, true, 0, &ft_st},
	{ADD, "add", 3, {T_REG, T_REG, T_REG}, 10, "addition", true, true, 0,
		&ft_add_sub},
	{SUB, "sub", 3, {T_REG, T_REG, T_REG}, 10, "soustraction", true, true, 0,
		&ft_add_sub},
	{AND, "and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", true, true, 4, &ft_bin},
	{OR, "or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", true, true, 4, &ft_bin},
	{XOR, "xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", true, true, 4, &ft_bin},
	{ZJMP, "zjmp", 1, {T_DIR, 0, 0}, 20, "jump if zero", false, false, 2,
		&ft_zjmp},
	{LDI, "ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25,
		"load index", false, true, 2, &ft_ldi},
	{STI, "sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25,
		"store index", false, true, 2, &ft_sti},
	{FORK, "fork", 1, {T_DIR, 0, 0}, 800, "fork", false, false, 2, &ft_fork},
	{LLD, "lld", 2, {T_DIR | T_IND, T_REG, 0}, 10, "long load", true, true, 4,
		&ft_ld},
	{LLDI, "lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50,
		"long load index", true, true, 2, &ft_lldi},
	{LFORK, "lfork", 1, {T_DIR, 0, 0}, 1000, "long fork", false, false, 2,
		&ft_fork},
	{AFF, "aff", 1, {T_REG, 0, 0}, 2, "aff", false, true, 0, &ft_aff},
	{0, 0, 0, {0, 0, 0}, 0, 0, 0, 0, 0, 0}
};

const unsigned char	g_color[6][10] = {RED, GREEN, YELLOW, BLUE, PURPLE, CYAN};

const unsigned char	g_colorpc[6][10] = {RED_BKG, GREEN_BKG, YELLOW_BKG, BLUE_BKG,
	PURPLE_BKG, CYAN_BKG};
