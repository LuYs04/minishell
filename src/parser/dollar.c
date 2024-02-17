/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:31:56 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/06 18:10:53 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

char	*write_dollar(char *val, char *str, char *dol, int flag)
{
	char	*temp;
	char	*buf;

	if (flag == 2)
	{
		temp = ft_strjoin_nl(str, "$");
		free(str);
		str = ft_strjoin_nl(temp, dol);
		free(temp);
	}
	else
	{
		buf = malloc(dollar_word_len(val) + 1);
		if (ft_strlen(dol) == 1 && *dol == '?')
			buf = check_exit_code(buf);
		else
			buf = fill_dollar_buf(buf, val, 0, 0);
		if (!str)
			temp = ft_strdup(buf);
		else
			temp = ft_strjoin_nl(str, buf);
		return (free(str), free(buf), temp);
	}
	return (str);
}

int	check_dollar_1(char *line, int i)
{
	while (line && line[i] && line[i] != '$' && line[i] != ' '
		&& line[i] != '=' && line[i] != '@' && line[i] != '\t'
		&& line[i] != 92 && line[i] != '?'
		&& !(line[i] >= 33 && line[i] <= 47))
		i++;
	return (i);
}

char	*check_dollar_2(char *dol, char *str, int flag)
{
	dol = ft_strdup("?");
	str = write_dollar("$", str, dol, flag);
	return (free(dol), str);
}

char	*check_dollar(char *line, t_env *env, char *str, int flag)
{
	t_env	*tmp;
	char	*dol;
	int		i;

	dol = NULL;
	i = 1;
	tmp = env;
	i = check_dollar_1(line, i);
	if (line && line[i] == '?' && line[i - 1] == '$')
		return (check_dollar_2(dol, str, flag));
	dol = ft_substr(line, 1, i - 1);
	while (tmp && tmp->key)
	{
		if (dol[0] != '\0' && !ft_strncmp(dol, tmp->key, ft_strlen(dol))
			&& !ft_strncmp(dol, tmp->key, ft_strlen(tmp->key)))
		{
			str = write_dollar(tmp->val, str, dol, flag);
			return (free(dol), str);
		}
		tmp = tmp->next;
	}
	if (!*dol && line[i] != '$')
		str = write_dollar("$", str, dol, flag);
	return (free(dol), str);
}

char	*analyze_dollar(char *line, t_env *env, int i, int j)
{
	t_dol	doll;

	doll.flag = 0;
	doll.str = NULL;
	doll.buf = malloc((ft_strlen(line) + 1) * sizeof(char));
	while (line && line[i])
	{
		if (line[i] && line[i] == '$')
		{
			doll.str = check_dollar(&line[i], env, doll.str, doll.flag);
			i++;
			i = analyze_dollar_1(line, i);
		}
		while (line[i] && line[i] != '$')
		{
			if (line[i] == 34 || line[i] == 39)
				doll.q = analyze_dollar_2(line, doll.q, &doll.flag, &i);
			doll.buf[j++] = line[i++];
		}
		doll.str = join_dollar(doll.str, doll.buf, j);
		j = 0;
	}
	return (free(doll.buf), doll.str);
}
