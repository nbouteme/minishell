/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 01:59:49 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/17 02:03:46 by nbouteme         ###   ########.fr       */
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

int	builtin_env(int ac, char **av)
{
	(void)av;
	(void)ac;
	print_env();
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
int cd_step9();
int cd_step10();

void parse_cd_opts(int ac, char **av, t_cd_opts *opts)
{
	(void)ac;
	while(*(++av))
	{
		if(ft_strcmp(*av, "-P")
		   && ft_strcmp(*av, "-L"))
			break;
		opts->physical = ft_strcmp(*av, "-P") ? 1 : 0;
		opts->physical = ft_strcmp(*av, "-L") ? 0 : 1;
	}
	opts->dir_op = *(--av);
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
	}
	return (cd_step8());
}

int check_components(char **start, char **end)
{
	(void)start;
	(void)end;
	return 1;
}

int cd_step8()
{
	char *canon;
	char **arr;
	char **tmp;

	canon = ft_strnew(256);
	arr = ft_strsplit(curp, '/');
	tmp = arr;
	while (*tmp)
	{
		if (ft_strcmp(*tmp, "") || ft_strcmp(*tmp, "."))
			continue ;
		if (tmp != arr && (ft_strcmp(tmp[-1], "") || ft_strcmp(tmp[-1], "..")))
		{
			if (!check_components(arr, tmp - 1))
				return 1;
			*ft_strrchr(canon, '/') = 0;
		}
	}
	return (cd_step9());
}

int cd_step9()
{
	if (ft_strlen(curp) + 1 > 256 &&
		my_get_env("PWD") != 0 &&
		ft_strstr(curp, my_get_env("PWD")) == curp)
	{
		/* TODO: Reduire */
	}
	return (cd_step10());
}

void run_cd_diag()
{
	perror("cd");
	puts(curp);
}

int cd_step10()
{
	if(chdir(curp) != -1)
		return (0);
	run_cd_diag();
	return (1);
}

int	builtin_cd(int ac, char **av)
{
	t_cd_opts opts;

	free(oldp);
	oldp = curp;
	curp = 0;
	parse_cd_opts(ac, av + 1, &opts);
	if (!opts.dir_op)
		return (1);
	if (opts.dir_op[0] == '/')
	{
		curp = opts.dir_op;
		return (cd_step7(&opts));
	}
	else if (opts.dir_op[0] == '.')
		return (cd_step6(&opts));
	return (cd_step5(&opts));
}
