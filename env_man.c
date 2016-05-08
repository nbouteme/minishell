/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 02:01:36 by nbouteme          #+#    #+#             */
/*   Updated: 2016/05/08 02:21:05 by nbouteme         ###   ########.fr       */
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
	char		**e;
	t_u64		l;

	l = ft_strlen(key);
	e = environ;
	while (*e)
		if (ft_strncmp(key, *e, l) == 0 && e[0][l] == '=')
		{
			free(*e);
			while (e[1])
			{
				*e = e[1];
				++e;
			}
			*e = 0;
			return ;
		}
		else
			++e;
}

void		my_setenv(char *key, char *val)
{
	extern char	**environ;
	char		*tmp;
	char		**e;
	t_u64		l;

	l = ft_strlen(key);
	tmp = ft_strnew(l + ft_strlen(val) + 2);
	ft_strcat(tmp, key);
	ft_strcat(tmp, "=");
	ft_strcat(tmp, val);
	e = environ;
	while (*e)
		if (ft_strncmp(key, *e, l) == 0 && e[0][l] == '=')
		{
			free(*e);
			*e = tmp;
			return ;
		}
		else
			++e;
	l = e - environ;
	e = ft_memcpy(ft_memalloc(8 * (l + 2)), environ, 8 * l);
	e[l] = tmp;
	environ = e;
}

const char	*my_get_env(const char *key)
{
	extern char	**environ;
	char		**e;
	t_u64		l;

	l = ft_strlen(key);
	e = environ;
	while (*e)
		if (ft_strncmp(key, *e, l) == 0 && e[0][l] == '=')
			return (&e[0][l + 1]);
		else
			++e;
	return (0);
}

void		dupenv(void)
{
	extern char **environ;
	char		**newenv;
	char		**e;
	t_u64		l;

	e = environ;
	while (*e)
		++e;
	l = e - environ;
	newenv = malloc(sizeof(char*) * (l + 1));
	e = newenv;
	ft_memcpy(newenv, environ, sizeof(char*) * (l + 1));
	while (*e)
	{
		*e = ft_strdup(*e);
		++e;
	}
	environ = newenv;
}
