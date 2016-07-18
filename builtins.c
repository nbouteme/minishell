/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 01:59:49 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/18 01:35:05 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <sys/stat.h>
void free_arr(char **arr);

char *empty_arr[] = {0};
char *def_arr[] = {"printenv", 0};

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

typedef struct	s_env_opts
{
	int empty;
	char **env;
	char *cmd;
	char **args;
}				t_env_opts;

void parse_env_opts(char **av, t_env_opts *opts)
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
	opts->args = opts->cmd ? av : def_arr;
	opts->cmd = opts->cmd ? opts->cmd : def_arr[0];
}

int	builtin_env(int ac, char **av)
{
	t_env_opts opts;
	t_cmdexpr cmd;

	(void)ac;
	parse_env_opts(av + 1, &opts);
	cmd.cmd = opts.cmd;
	cmd.args = opts.args;
	cmd.environ = opts.empty ? empty_arr : opts.env;
	eval_from_path(&cmd);
	free_arr(opts.env);
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

char *oldp = 0;
char *curp = 0;

typedef struct	s_cd_opts
{
	int physical;
	char *dir_op;
}				t_cd_opts;

int cd_step6(t_cd_opts *opts);
int cd_step5(t_cd_opts *opts);
int cd_step7(t_cd_opts *opts);
int cd_step8();
int cd_step10();

void parse_cd_opts(int ac, char **av, t_cd_opts *opts)
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

int cd_step6(t_cd_opts *opts)
{
	curp = ft_strdup(opts->dir_op);
	return (cd_step7(opts));
}

int cd_step5(t_cd_opts *opts)
{
	const char *cdpath;
	char **arr;
	char **tmp;

	cdpath = my_get_env("HOME");
	if (!cdpath)
		return (cd_step6(opts));
	arr = ft_strsplit(cdpath, ';');
	tmp = arr;
	while(*tmp)
	{
		/* TODO: test if the concatenation of that pathname, a <slash> character if that pathname did not end with a <slash> char‐
           acter, and the directory operand names a directory. If the pathname is null, test if the concatenation of dot, a <slash> character,
           and the operand names a directory. In either case, if the resulting string names an existing directory, set curpath to that  string
           and proceed to step 7. */
		++tmp;
	}
	tmp = arr;
	while(*tmp)
		free(*tmp++);
	free(arr);
	return (cd_step6(opts));
}

int cd_step7(t_cd_opts *opts)
{
	char *tmp;
	char *tmp2;
	const char *pwd;

	if (opts->physical)
		return (cd_step10());
	if (curp[0] != '/')
	{
		pwd = my_get_env("PWD");
		pwd = pwd ? pwd : ".";
		if (pwd[ft_strlen(pwd) - 1] != '/')
			tmp2 = ft_strjoin(pwd, "/");
		else
			tmp2 = ft_strdup(pwd);
		tmp = ft_strjoin(tmp2, curp);
		free(curp);
		free(tmp2);
		curp = tmp;
	}
	return (cd_step10());
}

int check_components(char **start, char **end)
{
	(void)start;
	(void)end;
	return 1;
}


int is_dir(const char *path)
{
	struct stat s;

	stat(path, &s);
	return (S_ISDIR(s.st_mode));
}

void run_cd_diag()
{
	ft_putstr("cd: ");
	if (access(curp, F_OK) == -1)
		ft_putstr("no such file or directory: ");
	else if (!is_dir(curp))
		ft_putstr("not a directory: ");
	else if (access(curp, R_OK | X_OK) == -1)
		ft_putstr("permission denied: ");
	puts(curp);
}

int cd_step10()
{
	if(chdir(curp) != -1)
		return (0);
	run_cd_diag();
	return (1);
}

int	cd_stage2(t_cd_opts *opts)
{
	if (opts->dir_op[0] == '/')
	{
		curp = ft_strdup(opts->dir_op);
		return (cd_step7(opts));
	}
	else if (opts->dir_op[0] == '.')
		return (cd_step6(opts));
	return (cd_step5(opts));
}


int	builtin_cd(int ac, char **av)
{
	t_cd_opts opts;
	int ret;

	free(oldp);
	oldp = curp;
	curp = 0;
	parse_cd_opts(ac, av + 1, &opts);
	if (!opts.dir_op)
		return (1);
	ret = cd_stage2(&opts);
	free(opts.dir_op);
	return (ret);
}
