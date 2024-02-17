/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:53:19 by armgevor          #+#    #+#             */
/*   Updated: 2024/02/01 15:05:27 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	check_both_quotes_existence(char *line, int i)
{
	char	q;

	if (!ft_strchr(line, 34) && !ft_strchr(line, 39))
		return (1);
	while (line && line[++i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			q = line[i++];
			while (line[i] != q && line[i])
				i++;
			if (line[i] == '\0')
				return (0);
		}
	}
	return (1);
}

int	check_operators_in_a_row(char *line, int i)
{
	char	q;
	char	c;

	while (line && line[++i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			c = line[i];
			if (line[i + 1] == c)
				i++;
			i++;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			if (line[i] == '>' || line[i] == '<'
				|| line[i] == '|' || line[i] == '\0')
				return (0);
		}
		if (line[i] == 34 || line[i] == 39)
		{
			q = line[i++];
			while (line[i] && line[i] != q)
				i++;
		}
	}
	return (1);
}

int	check_operator_after_pipe(char *line, int i)
{
	char	q;
	char	*str;

	while (line && line[++i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			q = line[i++];
			while (line[i] && line[i] != q)
				i++;
		}
		if (line[i] == '|')
		{
			while ((line[++i] == ' ' || line[i] == '\t') && line[i])
				;
			if (line[i] == '\0' || line[i] == '|')
				return (0);
		}
	}
	str = ft_strtrim(line, " ");
	if (*str == '|')
		return (free(str), 0);
	return (free(str), 1);
}

t_parse	*parsing(char *line, t_env *env)
{
	t_parse	*splited;
	char	*true_line;

	if (!check_both_quotes_existence(line, -1))
		return (error_case(0));
	if (!check_operator_after_pipe(line, -1))
		return (error_case(1));
	if (!check_operators_in_a_row(line, -1))
		return (error_case(2));
	if (ft_strchr(line, 36))
		true_line = analyze_dollar(line, env, 0, 0);
	else
		true_line = ft_strdup(line);
	splited = pipe_split(true_line);
	free(true_line);
	true_line = NULL;
	return (splited);
}
