/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/11/27 17:11:27 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

const t_op	g_op_tab[17] =
{
	{LIVE, "live", 1, {T_DIR, 0, 0, 0}, 10, "alive", false, false, 4, 1},
	{LD, "ld", 2, {T_DIR | T_IND, T_REG, 0, 0}, 5, "load", true, true, 4, 2},
	{ST, "st", 2, {T_REG, T_IND | T_REG, 0, 0}, 5, "store", false, true, 0, 2},
	{ADD, "add", 3, {T_REG, T_REG, T_REG, 0}, 10, "addition", true, true, 0,
		3},
	{SUB, "sub", 3, {T_REG, T_REG, T_REG, 0}, 10, "soustraction", true, true,
		0, 3},
	{AND, "and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG, 0},
		6, "et (and  r1, r2, r3   r1&r2 -> r3", true, true, 4, 3},
	{OR, "or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG, 0}, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", true, true, 4, 3},
	{XOR, "xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG, 0},
		6, "ou (xor  r1, r2, r3   r1^r2 -> r3", true, true, 4, 3},
	{ZJMP, "zjmp", 1, {T_DIR, 0, 0, 0}, 20, "jump if zero", false, false, 2,
		1},
	{LDI, "ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG, 0}, 25,
		"load index", false, true, 2, 3},
	{STI, "sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG, 0}, 25,
		"store index", false, true, 2, 3},
	{FORK, "fork", 1, {T_DIR, 0, 0, 0}, 800, "fork", false, false, 2, 1},
	{LLD, "lld", 2, {T_DIR | T_IND, T_REG, 0, 0}, 10, "long load", true, true,
		4, 2},
	{LLDI, "lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG, 0}, 50,
		"long load index", true, true, 2, 3},
	{LFORK, "lfork", 1, {T_DIR, 0, 0, 0}, 1000, "long fork", false, false, 2,
		1},
	{AFF, "aff", 1, {T_REG, 0, 0, 0}, 2, "aff", false, true, 0, 1},
	{0, 0, 0, {0, 0, 0, 0}, 0, 0, 0, 0, 0, 0}
};
