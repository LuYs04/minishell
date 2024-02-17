/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:42:19 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/01 15:02:29 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	unset_valid_var_name(char *var)
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
			g_exitcode = 1;
			ft_putstr_fd("not a valid identifier\n", 2);
			return ;
		}
		if (invalid_char(var[b]) == 1)
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			g_exitcode = 1;
			return ;
		}
		b++;
	}
}

void	unset(t_data *data, t_parse *pars)
{
	t_env	*lst;
	int		i;

	i = 0;
	while (pars->cmd && pars->cmd[++i])
	{
		unset_valid_var_name(pars->cmd[i]);
		lst = data->env_lst;
		while (lst)
		{
			if (lst && !ft_strncmp(lst->key, pars->cmd[i], ft_strlen(lst->key))
				&& !ft_strncmp(lst->key, pars->cmd[i], ft_strlen(pars->cmd[i])))
			{
				free(lst->key);
				free(lst->val);
				lst->key = ft_strdup("\0");
				lst->val = ft_strdup("\0");
				g_exitcode = 0;
				break ;
			}
			lst = lst->next;
		}
	}
}
