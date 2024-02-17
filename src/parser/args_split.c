/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:32:14 by luatshem          #+#    #+#             */
/*   Updated: 2024/01/31 19:53:24 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	op_file_delim_split(char *line, t_parse *split, int *i)
{
	int		start;
	char	c;
	char	*str;

	if (line && line[*i] && (line[*i] == '>' || line[*i] == '<'))
	{
		c = line[*i];
		start = *i;
		if (line[*i + 1] == c)
			*i += 1;
		split->operator[split->index->op]
			= ft_substr(line, start, (*i - start + 1));
		*i += 1;
		while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
			*i += 1;
		str = file_delim_quotes(line, i, 0);
		if (ft_strncmp(split->operator[split->index->op++], "<<", 2) == 0)
			split->delim[split->index->lm++] = ft_strdup(str);
		else
			split->file[split->index->fl++] = ft_strdup(str);
		free (str);
	}
}

char	*args_split_1(char *line, char *buf_ind, t_parse *split)
{
	split->cmd = malloc((count_cmd(0, 0, line) + 1) * sizeof(char *));
	split->file = malloc((count_file(0, 0, line) + 1) * sizeof(char *));
	split->delim = malloc((count_delim(0, 0, line) + 1) * sizeof(char *));
	split->operator = malloc((count_oper(0, 0, line) + 1) * sizeof(char *));
	buf_ind = malloc((count_buf(0, 0, line) + 1) * sizeof(char));
	buf_ind[count_buf(0, 0, line)] = '\0';
	return (buf_ind);
}

void	args_split_2(char *line, char *buf_ind, t_parse *split, int *i)
{
	if (line[*i] == '|')
	{
		split->operator[split->index->op++] = ft_strdup("|");
		*i += 1;
	}
	if (*split->operator)
		split->operator[split->index->op] = NULL;
	if (*split->file)
		split->file[split->index->fl] = NULL;
	if (*split->delim)
		split->delim[split->index->lm] = NULL;
	if (*split->cmd)
		split->cmd[split->index->cmd] = NULL;
	free(buf_ind);
	buf_ind = NULL;
}

int	args_split_3(char *line, char *buf, t_parse *split, int *j)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t'
		&& line[i] != '>' && line[i] != '<' && line[i] != '|')
	{
		if (line[i] == 34 || line[i] == 39)
			quote_handler(line, buf, &i, j);
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '>' && line[i] != '<' && line[i] != '|')
			buf[*j] = line[i];
		if (line[i] && line[i] != ' ' && line[i] != '\t')
		{
			i++;
			*j += 1;
		}
	}
	buf[*j] = '\0';
	split->cmd[split->index->cmd++] = ft_strdup(buf);
	buf = &buf[*j];
	*j = 0;
	return (i);
}

int	args_split(char *line, t_parse *split, int i, int j)
{
	char	*buf;
	char	*buf_ind;

	buf_ind = NULL;
	buf_ind = args_split_1(line, buf_ind, split);
	if (!split->cmd || !split->file || !split->delim
		|| !split->operator || !buf_ind)
		return (0);
	buf = buf_ind;
	while (line && line[i] && line[i] != '|')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '>'
			&& line[i] != '<' && line[i] != '|' && line[i])
			i += args_split_3(&line[i], buf, split, &j);
		else
			op_file_delim_split(line, split, &i);
	}
	return (args_split_2(line, buf_ind, split, &i), i);
}
