/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 02:01:36 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/21 01:27:50 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void		l_my_delenv(char **environ, char *key)
{
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

void		l_my_setenv_kv(char ***environ, char *kv)
{
	char		**e;
	t_u64		l;

	l = ft_strchr(kv, '=') - kv;
	e = *environ;
	while (*e)
		if (ft_strncmp(kv, *e, l) == 0 && e[0][l] == '=')
		{
			free(*e);
			*e = ft_strdup(kv);
			return ;
		}
		else
			++e;
	l = e - *environ;
	e = ft_memcpy(ft_memalloc(8 * (l + 2)), environ, 8 * l);
	e[l] = ft_strdup(kv);
	*environ = e;
}

void		l_my_setenv(char ***environ, char *key, char *val)
{
	char		*tmp;
	t_u64		l;

	l = ft_strlen(key);
	tmp = ft_strnew(l + ft_strlen(val) + 2);
	ft_strcat(tmp, key);
	ft_strcat(tmp, "=");
	ft_strcat(tmp, val);
	l_my_setenv_kv(environ, tmp);
	free(tmp);
}

const char	*l_my_get_env(char **environ, const char *key)
{
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

char		**l_dupenv(char **environ)
{
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
	return (newenv);
}
