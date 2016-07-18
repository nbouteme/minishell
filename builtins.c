/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 01:59:49 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/18 23:57:39 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char *g_empty_arr[] = {0};
char *g_def_arr[] = {"printenv", 0};
char *g_oldp = 0;
char *g_curp = 0;

void	parse_env_opts(char **av, t_env_opts *opts)
{
	extern char	**environ;

	opts->empty = 0;
	opts->cmd = 0;
	opts->args = 0;
	opts->env = l_dupenv(environ);
	while (*av)
	{
		if (ft_strcmp(*av, "-") == 0 || ft_strcmp(*av, "-i") == 0)
		{
			++av;
			opts->empty = 1;
			break ;
		}
		if (ft_strcmp(*av, "-u") == 0)
			l_my_delenv(opts->env, *(++av));
		else if (ft_strchr(*av, '='))
			l_my_setenv_kv(opts->env, *av);
		else
			break ;
		++av;
	}
	opts->cmd = *av;
	opts->args = opts->cmd ? av : g_def_arr;
	opts->cmd = opts->cmd ? opts->cmd : g_def_arr[0];
}

int		builtin_env(int ac, char **av)
{
	t_env_opts	opts;
	t_cmdexpr	cmd;

	(void)ac;
	parse_env_opts(av + 1, &opts);
	cmd.cmd = opts.cmd;
	cmd.args = opts.args;
	cmd.environ = opts.empty ? g_empty_arr : opts.env;
	eval_from_path(&cmd);
	free_arr(opts.env);
	return (1);
}

void	parse_cd_opts(int ac, char **av, t_cd_opts *opts)
{
	opts->physical = 0;
	opts->dir_op = 0;
	while (*av)
	{
		if (ft_strcmp(*av, "-P")
			&& ft_strcmp(*av, "-L"))
		{
			ac = 0;
			++av;
			break ;
		}
		opts->physical = ft_strcmp(*av, "-P") ? 1 : 0;
		opts->physical = ft_strcmp(*av, "-L") ? 0 : 1;
		++av;
	}
	if (ac)
		opts->dir_op = 0;
	else
		opts->dir_op = ft_strdup(*(--av));
	if (!opts->dir_op ||
		(ft_strcmp(*av, "-P") == 0 && ft_strcmp(*av, "-L") == 0))
		opts->dir_op = ft_strdup(my_get_env("HOME"));
}

int		builtin_cd(int ac, char **av)
{
	t_cd_opts	opts;
	int			ret;

	free(g_oldp);
	g_oldp = g_curp;
	g_curp = 0;
	parse_cd_opts(ac, av + 1, &opts);
	if (!opts.dir_op)
		return (1);
	ret = cd_stage2(&opts);
	free(opts.dir_op);
	return (ret);
}
