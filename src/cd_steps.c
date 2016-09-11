/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 23:47:09 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/19 00:43:52 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <sys/param.h>

extern char *g_curp;

int		cd_step6(t_cd_opts *opts)
{
	g_curp = ft_strdup(opts->dir_op);
	return (cd_step7(opts));
}

int		cd_step5(t_cd_opts *opts)
{
	return (cd_step6(opts));
}

int		cd_step7(t_cd_opts *opts)
{
	char		*tmp;
	char		*tmp2;
	const char	*pwd;

	if (opts->physical)
		return (cd_step10());
	if (g_curp[0] != '/')
	{
		pwd = my_get_env("PWD");
		pwd = pwd ? pwd : ".";
		if (pwd[ft_strlen(pwd) - 1] != '/')
			tmp2 = ft_strjoin(pwd, "/");
		else
			tmp2 = ft_strdup(pwd);
		tmp = ft_strjoin(tmp2, g_curp);
		free(g_curp);
		free(tmp2);
		g_curp = tmp;
	}
	return (cd_step10());
}

int		cd_step10(void)
{
	char *buf;

	if (chdir(g_curp) != -1)
	{
		buf = ft_strnew(MAXPATHLEN);
		getcwd(buf, MAXPATHLEN);
		my_setenv("PWD", buf);
		free(buf);
		return (0);
	}
	run_cd_diag();
	return (1);
}

int		cd_stage2(t_cd_opts *opts)
{
	if (opts->dir_op[0] == '/')
	{
		g_curp = ft_strdup(opts->dir_op);
		return (cd_step7(opts));
	}
	else if (opts->dir_op[0] == '.')
		return (cd_step6(opts));
	return (cd_step5(opts));
}
