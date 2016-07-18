/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 23:43:49 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/18 23:43:56 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	builtin_setenv(int ac, char **av)
{
	if (ac <= 1)
		print_env();
	else if (ac == 2)
		my_setenv(av[1], "");
	else
		my_setenv(av[1], av[2]);
	return (1);
}

int	builtin_unsetenv(int ac, char **av)
{
	if (ac != 2)
		return (0);
	my_delenv(av[1]);
	return (1);
}

int	builtin_exit(int ac, char **av)
{
	if (ac <= 1)
		exit(0);
	else
		exit(atoi(av[1]));
	return (0);
}

int	builtin_echo(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 1)
		ft_putchar(10);
	else
		while (i < ac)
			ft_putendl(av[i++]);
	return (0);
}
