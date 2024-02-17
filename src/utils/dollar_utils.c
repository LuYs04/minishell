/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:09 by armgevor          #+#    #+#             */
/*   Updated: 2024/02/01 14:30:20 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	analyze_dollar_1(char *line, int i)
{
	if (line && line[i] && line[i] == '?' && line[i - 1] == '$')
		return (i + 1);
	while ((line[i] == '?' && line[i - 1] == '$')
		|| (line[i] && line[i] != '$' && line[i] != ' ' && line[i] != 92
			&& line[i] != '=' && line[i] != '@' && line[i] != '\t'
			&& line[i] != '?' && !(line[i] >= 33 && line[i] <= 47)))
		i++;
	return (i);
}

char	analyze_dollar_2(char *line, char q, int *flag, int *i)
{
	if (flag && line[*i] && line[*i] == q)
	{
		q = 0;
		*flag = 0;
	}
	else if (line[*i] == 34 && *flag != 2)
	{
		q = line[*i];
		*flag = 1;
	}
	else if (*flag != 1)
	{
		q = line[*i];
		*flag = 2;
	}
	return (q);
}

char	*join_dollar(char *str, char *buf, int j)
{
	char	*temp;

	buf[j] = '\0';
	if (!str)
		temp = ft_strdup(buf);
	else
		temp = ft_strjoin_nl(str, buf);
	free(str);
	return (temp);
}

int	dollar_word_len(char *val)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	while (val && val[i])
	{
		if (val[i] && (val[i] == '>' || val[i] == '<' || val[i] == '|'))
		{
			while (val[i] && (val[i] == '>' || val[i] == '<' || val[i] == '|'))
			{
				i++;
				w++;
			}
			w += 2;
		}
		else
		{
			i++;
			w++;
		}
	}
	return (w);
}

char	*fill_dollar_buf(char *buf, char *val, int i, int j)
{
	while (val && val[i])
	{
		if (val[i] && (val[i] == '>' || val[i] == '<' || val[i] == '|'))
		{
			buf[j++] = 39;
			while (val[i] && (val[i] == '>' || val[i] == '<' || val[i] == '|'))
				buf[j++] = val[i++];
			buf[j++] = 39;
		}
		if (val[i])
			buf[j++] = val[i++];
	}
	buf[j] = '\0';
	return (buf);
}
