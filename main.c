/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 00:23:59 by nbouteme          #+#    #+#             */
/*   Updated: 2016/03/27 05:57:41 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <dirent.h>
typedef struct	s_cmdexpr
{
	char *cmd;
	char **args;
	int r_flags;
}				t_cmdexpr;

typedef struct	s_builtin
{
	const char *name;
	int	(*fun)(int , char **);
}				t_builtin;

#define BUILTIN_DECL(x) { #x, builtin_ ##x }

int builtin_cd		(int ac, char **av){(void)av;(void)ac;return 0;}
int builtin_setenv	(int ac, char **av){(void)av;(void)ac;return 0;}
int builtin_unsetenv(int ac, char **av){(void)av;(void)ac;return 0;}
int builtin_env		(int ac, char **av){(void)av;(void)ac;return 0;}
int builtin_exit	(int ac, char **av){(void)av;(void)ac;return 0;}
int builtin_dot		(int ac, char **av){(void)av;(void)ac;return 0;}
int builtin_dotdot	(int ac, char **av){(void)av;(void)ac;return 0;}
int builtin_	(int ac, char **av){(void)av;(void)ac;return 0;}

int builtin_not_found(int ac, char **av)
{
	(void)ac;
	ft_putstr("minishell: ");
	ft_putstr(av[0]);
	ft_putstr(": command not found\n");
	return (1);
}

const t_builtin g_builtins[7] =
{
	{".", builtin_not_found},
	{"..", builtin_not_found},
	BUILTIN_DECL(cd),
	BUILTIN_DECL(setenv),
	BUILTIN_DECL(unsetenv),
	BUILTIN_DECL(env),
	BUILTIN_DECL(exit)
};

const char *my_get_env(const char *key)
{
	extern char **environ;
	char **e;
	t_u64 l;

	l = ft_strlen(key);
	e = environ;
	while (*e)
		if (ft_strncmp(key, *e, l) == 0 && e[0][l] == '=')
			return (&e[0][l + 1]);
		else ++e;
	return (0);
}

t_cmdexpr *parse_subcmd(const char **line)
{
	const char *d;
	const char *f;
	t_cmdexpr *ret;

	ret = malloc(sizeof(*ret));
	f = *line;
	while (*f && ft_isspace(*f))
		++f;
	d = f;
	while (*d && !ft_isspace(*d))
		++d;
	ret->cmd = ft_strsub(f, 0, d - f);
	ret->args = ft_strsplitv(*line, ft_isspace);
	*line = d;
	return (ret);
}

t_bnode *parse_cmd(const char *line)
{
	const char *d;
	t_bnode *ret;

	ret = ftext_lstnew();
	while (*line && ft_isspace(*line))
		++line;
	d = line;
	while (*d && !ft_isspace(*d))
		++d;
	while (*line)
		ftext_lstpush_back(ret, ftext_lstnewelemown(parse_subcmd(&line), 0));
	return (ret);
}

void exec_stage2(t_cmdexpr *cmd, char *binpath)
{
	int cid;
	extern char **environ;

	if (fork())
		wait(&cid);
	else
		execve(binpath, cmd->args, environ);
}

void execute_cmd(t_cmdexpr *cmd, char *dir)
{
	char *fullname;
	char *r;

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


int eval_in_dir(t_cmdexpr *cmd, char *dir)
{
	DIR *dirh;
	struct dirent *head;

	dirh = opendir(dir);
	if (dirh)
	{
		while ((head = readdir(dirh)))
			if (!ft_strcmp(cmd->cmd, head->d_name))
			{
				execute_cmd(cmd, dir);
				closedir(dirh);
				return (1);
			}
		closedir(dirh);
	}
	return (0);
}

void eval_from_path(t_cmdexpr *cmd)
{
	char **path;

	path = ft_strsplit(my_get_env("PATH"), ':');
	while (*path && !eval_in_dir(cmd, *path))
	{
		free(*path);
		++path;
	}
	if (!*path)
	{
		ft_putstr("minishell: ");
		ft_putstr(cmd->cmd);
		ft_putstr(": Command not found\n");
	}
	//free(path);
}

void eval_cmd(t_dlist *elem)
{
	t_cmdexpr *cmd;
	t_u32 i;
	int j;

	cmd = elem->content;
	i = ~0;
	while (++i < 5)
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

int main()
{
	char *line;

	while (write(1, "$> ", 3) && get_next_line(0, &line) > 0)
	{
		t_bnode *cmd = parse_cmd(line);
		ftext_lstiter(cmd, eval_cmd);
		free(line);
	}
	ft_putchar(10);
	ft_putchar('\e');
	ft_putchar('=');
}
