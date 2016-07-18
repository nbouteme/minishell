/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 02:01:36 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/19 00:03:26 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void		print_env(void)
{
	extern char	**environ;
	char		**e;

	e = environ;
	while (*e)
	{
		ft_putendl(*e);
		++e;
	}
}

void		my_delenv(char *key)
{
	extern char	**environ;

	return (l_my_delenv(environ, key));
}

void		my_setenv(char *key, char *val)
{
	extern char	**environ;

	return (l_my_setenv(environ, key, val));
}

const char	*my_get_env(const char *key)
{
	extern char	**environ;

	return (l_my_get_env(environ, key));
}

void		dupenv(void)
{
	extern char **environ;

	environ = l_dupenv(environ);
}
