/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:19:10 by djoye             #+#    #+#             */
/*   Updated: 2020/01/21 17:35:04 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int     live(t_vm *vm, t_cur *cur)
{
    int arg;

    cur->step++;
    arg = get_arg(vm->arena, cur, T_DIR, 0);
    
}