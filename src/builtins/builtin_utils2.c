/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:41:29 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/01 15:02:29 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	invalid_char(int c)
{
	if ((c >= 33 && c <= 35)
		|| (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 94 && c <= 96)
		|| (c >= 123 && c <= 126))
		return (1);
	return (0);
}

int	valid_dir(char *path)
{
	struct stat	buf;

	return (stat(path, &buf));
}

char	**shlvl(char **key_val)
{
	char	*tmp;
	int		i;

	if (key_val[0][0] == 'S' && ft_strncmp(key_val[0], "SHLVL", 5) == 0
		&& ft_strncmp(key_val[0], "SHLVL", ft_strlen(key_val[0])) == 0)
	{
		if (!key_val[1])
			key_val[1] = ft_strdup("1");
		else
		{
			tmp = ft_strdup(key_val[1]);
			free(key_val[1]);
			i = ft_atoi(tmp) + 1;
			key_val[1] = ft_itoa(i);
			free(tmp);
		}
	}
	return (key_val);
}

int	valid_var_name(char *var)
{
	int	b;

	b = 0;
	while (var && var[b])
	{
		if (var[b] == '+' && var[b + 1] == '\0')
			b++;
		if ((ft_isalpha(var[0]) == 0 && var[0] != '_')
			|| (var[b] >= 36 && var[b] <= 47))
		{
			ft_putstr_fd("not a valid identifier\n", 2);
			return (0);
		}
		if (invalid_char(var[b]))
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			return (0);
		}
		if (var[b])
			b++;
	}
	return (1);
}

void	find_variable(t_data	*data, char *line, char *pointer)
{
	t_env	*lst;
	char	*tmp;
	char	*s;

	lst = data->env_lst;
	while (lst && lst->next
		&& ft_strncmp(lst->key, line, ft_strlen(lst->key)) != 0
		&& ft_strncmp(lst->key, line, ft_strlen(line)) != 0)
		lst = lst->next;
	s = ft_strjoin(line, "=");
	tmp = s;
	s = ft_strjoin(tmp, pointer);
	free(tmp);
	for_export(data, s);
	free(s);
}
