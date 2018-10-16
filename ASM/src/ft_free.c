/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2013/11/06 14:44:35 by iongradea        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void  ft_free_head(t_header *head)
{
  free(head->prog_name);
  free(head->comment);
}

void  ft_free_all_inst(t_inst *inst)
{
  while (inst)
  {
    free(inst);
    inst = inst->n;
  }
}
