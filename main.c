/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 00:23:59 by nbouteme          #+#    #+#             */
/*   Updated: 2016/07/18 00:38:11 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void free_arr(char **arr)
{
	char **tmp;

	tmp = arr;
	while (*tmp)
		free(*tmp++);
	free(arr);
}

void free_cmd(void *data, size_t n)
{
	t_cmdexpr	*cmd;

	(void)n;
	cmd = data;
	free(cmd->cmd);
	free_arr(cmd->args);
	free(cmd);
}

void free_globs()
{
	extern char *curp;
	extern char *oldp;

	free(curp);
	free(oldp);
}

int	main(void)
{
	extern char **environ;
	char	*line;
	t_bnode	*cmd;

	dupenv();
	while (write(1, "$> ", 3) && get_next_line(0, &line) > 0)
	{
		cmd = parse_cmd(line);
		ftext_lstiter(cmd, eval_cmd);
		ftext_lstdel(&cmd, free_cmd);
		free(line);
	}
	free(line);
	free_arr(environ);
	free_globs();
	ft_putchar(10);
	ft_putchar('\e');
	ft_putchar('=');
}
