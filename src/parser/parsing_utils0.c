/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:44:14 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/06 18:44:10 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

t_parse	*error_case(int e)
{
	if (e == 0)
		ft_putstr_fd("error: please close the quote\n", 2);
	else if (e == 1)
		ft_putstr_fd("error: no command before or after '|'\n", 2);
	else if (e == 2)
		ft_putstr_fd("syntax error near unexpected token\n", 2);
	g_exitcode = 258;
	return (0);
}

char	*ft_strjoin_nl(char *str1, char *str2)
{
	char	*spc;
	size_t	i;

	i = -1;
	spc = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (!spc)
		return (NULL);
	while (str1 && str1[++i])
		spc[i] = str1[i];
	while (str2 && *str2)
		spc[i++] = *str2++;
	spc[i] = '\0';
	return (spc);
}

char	*file_delim_quotes(char *arg, int *i, int j)
{
	char	*str;
	char	*buf;

	buf = malloc(ft_strlen(arg) + 1);
	if (!buf)
		return (NULL);
	while (arg && arg[*i] && arg[*i] != ' ' && arg[*i] != '\t'
		&& arg[*i] != '>' && arg[*i] != '|' && arg[*i] != '<')
	{
		if (arg[*i] == 34 || arg[*i] == 39)
			quote_handler(arg, buf, i, &j);
		if (arg[*i] == ' ' || arg[*i] == '\t')
			break ;
		buf[j++] = arg[*i];
		if (arg[*i])
			*i += 1;
	}
	buf[j] = '\0';
	str = ft_strdup(buf);
	free(buf);
	return (str);
}

void	quote_handler(char *line, char *buf, int *i, int *j)
{
	char	q;

	if (line && line[*i])
		q = line[*i];
	else
		return ;
	*i += 1;
	if (buf)
		while (line && line[*i] && line[*i] != q)
			buf[(*j)++] = line[(*i)++];
	else
		return ;
	*i += 1;
	if (line && line[*i] && (line[*i] == 34 || line[*i] == 39))
		quote_handler(line, buf, i, j);
}
