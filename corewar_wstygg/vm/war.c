/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:48:04 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/24 17:58:18 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void				reset_cur_args(t_cur *cur)
{
	cur->arg_size[0] = 0;
	cur->arg_size[1] = 0;
	cur->arg_size[2] = 0;
	cur->args[0] = 0;
	cur->args[1] = 0;
	cur->args[2] = 0;
	cur->args_type[0] = 0;
	cur->args_type[1] = 0;
	cur->args_type[2] = 0;
	cur->args_type[3] = 0;
}

void				do_cycle(t_vm *v)
{
	t_cur			*c;
	int				skip;

	c = v->curs;
	while (c)
	{
		if (c->cyc_before_op <= 0)
			if ((c->operation = v->arena[c->pos]) >= 0x01
				&& c->operation <= 0x10)
				c->cyc_before_op = g_op_tab[c->operation].need_cycles;
		if (--c->cyc_before_op <= 0)
		{
			if (!(skip = check_op(v, c)))
			{
				do_op(v, c);
				c->pos = (c->pos + 1 + g_op_tab[c->operation].code_type_arg +
				c->arg_size[0] + c->arg_size[1] + c->arg_size[2]) % MEM_SIZE;
				reset_cur_args(c);
			}
			else
				c->pos = (c->pos + skip) % MEM_SIZE;
		}
		c = c->next;
	}
}

int					war_coming(t_vm *v)
{
	while (++v->global)
	{
		if ((v->cycles_to_die > 0) ? !(v->global % v->cycles_to_die) : 1)
		{
			v->checks++;
			delete_deads(v);
			if (v->live_count >= NBR_LIVE)
				v->cycles_to_die -= CYCLE_DELTA;
			if (v->checks == MAX_CHECKS)
			{
				v->cycles_to_die -= CYCLE_DELTA;
				v->checks = 0;
			}
			v->live_count = 0;
		}
		do_cycle(v);
		if (v->curs_alive == 0)
			break ;
	}
	if (v->last_champ)
		printf("Global - [%lu]\nPlayer %d - \"%s\" (\"%s\") - won!\n",
		v->global, v->last_champ->n, v->last_champ->name, v->last_champ->com);
	else
		printf("No one won...\n");
	return (1);
}