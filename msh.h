/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 00:31:16 by nbouteme          #+#    #+#             */
/*   Updated: 2016/05/08 02:25:10 by nbouteme         ###   ########.fr       */
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
	int			r_flags;
}				t_cmdexpr;

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
int				builtin_cd(int ac, char **av);
void			print_env();
void			my_delenv(char *key);
void			my_setenv(char *key, char *val);
void			dupenv();
const char		*my_get_env(const char *key);

#endif
