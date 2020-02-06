/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:15:21 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/02/05 17:15:22 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void				do_st(t_vm *vm, t_cur *cur)
{
	t_4bytes		byte;
	int				skip;

	cur->args[0] = vm->arena[(cur->pos + 2) % MEM_SIZE];
	if (cur->args_type[1] == T_REG)
		cur->reg[cur->args[1]] = cur->reg[cur->args[0]];
	else
	{
		skip = read_t_dir(vm, cur->pos + 2 + cur->arg_size[1], 4) % IDX_MOD;
		byte.hex = cur->reg[cur->args[0]];
		vm->arena[(cur->pos + skip) % MEM_SIZE] = byte.f.o4;
		vm->arena[(cur->pos + (skip + 1) % IDX_MOD) % MEM_SIZE] = byte.f.o3;
		vm->arena[(cur->pos + (skip + 2) % IDX_MOD) % MEM_SIZE] = byte.f.o2;
		vm->arena[(cur->pos + (skip + 3) % IDX_MOD) % MEM_SIZE] = byte.f.o1;
	}
}

void				do_add(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	cur->reg[cur->args[2]] = cur->reg[cur->args[0]] + cur->reg[cur->args[1]];
	if (cur->reg[cur->args[2]] == 0)
		cur->carry = 1;
	else
		cur->carry = 0;
}

void				do_sub(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	cur->reg[cur->args[2]] = cur->reg[cur->args[0]] - cur->reg[cur->args[1]];
	if (cur->reg[cur->args[2]] == 0)
		cur->carry = 1;
	else
		cur->carry = 0;
}

void				do_and(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	cur->reg[cur->args[2]] = cur->args[0] & cur->args[1];
	cur->carry = cur->reg[cur->args[2]] == 0;
}

void				do_or(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	cur->reg[cur->args[2]] = cur->args[0] | cur->args[1];
	cur->carry = cur->reg[cur->args[2]] == 0;
}