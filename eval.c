/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 02:04:13 by nbouteme          #+#    #+#             */
/*   Updated: 2016/05/08 02:17:42 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#define BUILTIN_DECL(x) { #x, builtin_ ##x }

const t_builtin g_builtins[] =
{
	BUILTIN_DECL(cd),
	BUILTIN_DECL(setenv),
	BUILTIN_DECL(env),
	BUILTIN_DECL(unsetenv),
	BUILTIN_DECL(exit)
};

#undef BUILTIN_DECL

void	exec_stage2(t_cmdexpr *cmd, char *binpath)
{
	extern char		**environ;
	int				cid;

	if (fork())
		wait(&cid);
	else
		execve(binpath, cmd->args, environ);
}

void	execute_cmd(t_cmdexpr *cmd, char *dir)
{
	char	*fullname;
	char	*r;

	r = 0;
	if (dir[ft_strlen(dir) - 1] != '/')
		r = ft_strjoin(dir, "/");
	else
		r = ft_strdup(dir);
	fullname = ft_strjoin(r, cmd->cmd);
	if (access(fullname, X_OK | R_OK) == 0)
		exec_stage2(cmd, fullname);
	else
	{
		ft_putstr("minishell: ");
		ft_putstr(cmd->cmd);
		ft_putstr(": Permission denied\n");
	}
}

int		eval_in_dir(t_cmdexpr *cmd, char *dir)
{
	DIR				*dirh;
	struct dirent	*head;

	if (!(dirh = opendir(dir)))
		return (0);
	while ((head = readdir(dirh)))
		if (!ft_strcmp(cmd->cmd, head->d_name))
		{
			execute_cmd(cmd, dir);
			closedir(dirh);
			return (1);
		}
	closedir(dirh);
	return (0);
}

void	eval_from_path(t_cmdexpr *cmd)
{
	char		**path;
	const char	*p;

	path = 0;
	if ((p = my_get_env("PATH")))
	{
		path = ft_strsplit(p, ':');
		while (*path && !eval_in_dir(cmd, *path))
		{
			free(*path);
			++path;
		}
	}
	if (!path || !*path)
	{
		ft_putstr("minishell: ");
		ft_putstr(cmd->cmd);
		ft_putstr(": Command not found\n");
	}
}

void	eval_cmd(t_dlist *elem)
{
	t_cmdexpr	*cmd;
	t_u32		i;
	int			j;

	cmd = elem->content;
	i = ~0;
	while (++i < (sizeof(g_builtins) / sizeof(g_builtins[0])))
		if (ft_strcmp(g_builtins[i].name, cmd->cmd) == 0)
		{
			j = 0;
			while (cmd->args[j])
				++j;
			g_builtins[i].fun(j, cmd->args);
			return ;
		}
	eval_from_path(cmd);
}