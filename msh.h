/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 00:31:16 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/19 00:05:47 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <libft/std.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/wait.h>
# include "get_next_line.h"

typedef struct	s_cmdexpr
{
	char		*cmd;
	char		**args;
	char		**environ;
	int			r_flags;
}				t_cmdexpr;

typedef struct	s_env_opts
{
	int		empty;
	char	**env;
	char	*cmd;
	char	**args;
}				t_env_opts;

typedef struct	s_cd_opts
{
	int			physical;
	char		*dir_op;
}				t_cd_opts;

typedef struct	s_builtin
{
	const char	*name;
	int			(*fun)(int, char **);
}				t_builtin;

void			exec_stage2(t_cmdexpr *cmd, char *binpath);
void			execute_cmd(t_cmdexpr *cmd, char *dir);
int				eval_in_dir(t_cmdexpr *cmd, char *dir);
void			eval_from_path(t_cmdexpr *cmd);
void			eval_cmd(t_dlist *elem);
t_cmdexpr		*parse_subcmd(const char **line);
t_bnode			*parse_cmd(const char *line);
int				builtin_setenv(int ac, char **av);
int				builtin_env(int ac, char **av);
int				builtin_unsetenv(int ac, char **av);
int				builtin_exit(int ac, char **av);
int				builtin_echo(int ac, char **av);
int				builtin_cd(int ac, char **av);
void			free_arr(char **arr);

int				cd_step6(t_cd_opts *opts);
int				cd_step5(t_cd_opts *opts);
int				cd_step7(t_cd_opts *opts);
int				cd_step8();
int				cd_step10();
int				cd_stage2(t_cd_opts *opts);

void			print_env();
void			my_delenv(char *key);
void			my_setenv(char *key, char *val);
const char		*my_get_env(const char *key);
void			dupenv();
void			run_cd_diag();

void			l_print_env(char **env);
void			l_my_delenv(char **env, char *key);
void			l_my_setenv(char **env, char *key, char *val);
void			l_my_setenv_kv(char **env, char *kv);
const char		*l_my_get_env(char **env, const char *key);
char			**l_dupenv(char **env);

#endif
