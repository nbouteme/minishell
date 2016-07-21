/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 23:43:49 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/21 01:20:39 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	builtin_setenv(int ac, char **av)
{
	extern char **environ;
	if (ac <= 1)
		l_print_env(environ);
	else if (ac == 2)
		my_setenv_kv(av[1]);
	return (0);
}

int	builtin_unsetenv(int ac, char **av)
{
	if (ac != 2)
		return (1);
	my_delenv(av[1]);
	return (0);
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

int	builtin_printenv(int ac, char **av)
{
	extern char **environ;

	(void)ac;
	(void)av;
	l_print_env(environ);
	return (0);
}
