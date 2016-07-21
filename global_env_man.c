/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 02:01:36 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/21 01:13:25 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void		my_setenv_kv(char *kv)
{
	extern char	**environ;

	return (l_my_setenv_kv(environ, kv));
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
