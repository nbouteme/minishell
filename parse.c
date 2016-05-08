/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 02:03:48 by nbouteme          #+#    #+#             */
/*   Updated: 2016/05/08 02:22:10 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_cmdexpr	*parse_subcmd(const char **line)
{
	const char	*d;
	const char	*f;
	t_cmdexpr	*ret;

	ret = malloc(sizeof(*ret));
	f = *line;
	while (*f && ft_isspace(*f))
		++f;
	d = f;
	while (*d && !ft_isspace(*d))
		++d;
	ret->cmd = ft_strsub(f, 0, d - f);
	ret->args = ft_strsplitv(*line, ft_isspace);
	while (*d)
		++d;
	*line = d;
	return (ret);
}

t_bnode		*parse_cmd(const char *line)
{
	t_bnode *ret;

	ret = ftext_lstnew();
	while (*line && ft_isspace(*line))
		++line;
	while (*line)
		ftext_lstpush_back(ret, ftext_lstnewelemown(parse_subcmd(&line), 0));
	return (ret);
}
