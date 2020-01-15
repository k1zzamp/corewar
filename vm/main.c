/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:05:40 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/11 10:05:42 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		flag(int *i, int ac, char **av, t_vm *vm)
{
	if (*i + 1 < ac && !ft_strncmp(av[*i], "-dump", 5))
	{
		vm->dump = ft_atoi(av[++(*i)]);
		if (vm->dump < 0)
			return (printf("Invalid option in flag [-dump]\n") - 31);
		(*i)++;
		return (1);
	}
	else if (*i < ac && !ft_strncmp(av[*i], "-v", 2))
	{
		vm->color = 1;
		(*i)++;
		return (1);
	}
	return (1);
}

int		parser(t_vm *vm, int ac, char **av)
{
	int i;
	int n;

	i = 1;
	while (i < ac)
	{
		n = -1;
		if (!flag(&i, ac, av, vm))
			return (0);
		if (i + 1 < ac && !ft_strcmp(av[i], "-n"))
		{   
			n = ft_atoi(av[++i]);
			if (n > MAX_PLAYERS	|| n < 1)
				return (printf("Invalid option in flag [-n]\n") - 28);
			i++;
		}
		if (i < ac && !init_champ(&i, av, n, vm))
			return(0);
	}
	if (vm->players > MAX_PLAYERS)
		return (printf("Too much champions\n") - 19);
	return (1);
}

void		init(t_vm *vm)
{
	int i;

	i = -1;
	vm->dump = -1;
	vm->color = -1;
	vm->players = 0;
	while (++i < MAX_PLAYERS)
		vm->champ[i] = NULL;
}

int		main(int ac, char **av)
{
	t_vm		vm;

	if (ac < 2)
	{
		printf("usage: ./vm [champ1, champ2 ...]\n");
		exit(0);
	}
	init(&vm);
	if (!(parser(&vm, ac, av)))
		exit(1);
	build_arena(&vm);
	exit(0);
}
