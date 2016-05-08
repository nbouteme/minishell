/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 00:23:59 by nbouteme          #+#    #+#             */
/*   Updated: 2016/05/08 02:21:41 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	main(void)
{
	char	*line;
	t_bnode	*cmd;

	dupenv();
	while (write(1, "$> ", 3) && get_next_line(0, &line) > 0)
	{
		cmd = parse_cmd(line);
		ftext_lstiter(cmd, eval_cmd);
		free(line);
	}
	ft_putchar(10);
	ft_putchar('\e');
	ft_putchar('=');
}
