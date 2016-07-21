/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 01:30:18 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/21 02:45:31 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	eval_from_current(t_cmdexpr *cmd)
{
	int error;
	char *last_com;
	char *name;

	last_com = 0;
	error = 0;
	if (!(last_com = ft_strrchr(cmd->cmd, '/')))
		return (0);
	name = ft_strsub(last_com, 1, (cmd->cmd + ft_strlen(cmd->cmd)) - last_com);
	last_com = ft_strsub(cmd->cmd, 0, last_com - cmd->cmd);
	error = (is_dir(last_com));
	if (error)
	{
		execute_cmd(cmd, 0);
		return (1);
	}
	free(last_com);
	free(name);
	return (error);
}
