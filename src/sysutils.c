/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sysutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 23:47:22 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/19 00:04:57 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <sys/stat.h>

int		is_dir(const char *path)
{
	struct stat s;

	stat(path, &s);
	return (S_ISDIR(s.st_mode));
}

void	run_cd_diag(void)
{
	extern char *g_curp;

	ft_putstr("cd: ");
	if (access(g_curp, F_OK) == -1)
		ft_putstr("no such file or directory: ");
	else if (!is_dir(g_curp))
		ft_putstr("not a directory: ");
	else if (access(g_curp, R_OK | X_OK) == -1)
		ft_putstr("permission denied: ");
	puts(g_curp);
}
