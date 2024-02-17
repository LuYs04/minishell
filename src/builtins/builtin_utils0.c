/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:31:56 by luatshem          #+#    #+#             */
/*   Updated: 2024/01/31 19:45:04 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

t_env	*env_new(char *key, char *value, int flag)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	new->key = key;
	new->val = value;
	new->flag = flag;
	return (new);
}

void	env_addback(t_env **head, t_env *to_push)
{
	if (head)
	{
		if (*head)
			env_last(*head)->next = to_push;
		else
			*head = to_push;
	}
}

t_env	*env_last(t_env *head)
{
	if (head)
	{
		while (head->next)
			head = head->next;
	}
	return (head);
}

int	env_size(t_env *head)
{
	size_t	counter;
	t_env	*lst;

	lst = head;
	counter = 0;
	while (lst)
	{
		lst = lst->next;
		++counter;
	}
	return (counter);
}

void	env_scan(char **envp, t_data *data)
{
	char	**key_val;

	while (*envp)
	{
		key_val = ft_split(*envp, '=');
		if (key_val[0][0] == 'O' && ft_strncmp(key_val[0], "OLDPWD", 6) == 0
		&& ft_strncmp(key_val[0], "OLDPWD", ft_strlen(key_val[0])) == 0)
		{
			env_addback(&data->env_lst, env_new(ft_strdup("OLDPWD"),
					ft_strdup("\0"), 0));
			free2d(key_val);
			envp++;
			continue ;
		}
		key_val = shlvl(key_val);
		env_addback(&data->env_lst, env_new(key_val[0], key_val[1], 0));
		free(key_val);
		envp++;
	}
}
