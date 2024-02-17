/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:42:09 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/06 18:52:57 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	export_env(t_env *begining)
{
	t_env	*current;

	current = begining;
	while (current != NULL)
	{
		if (current->val && *current->val && *current->key)
			printf("declare -x %s=\"%s\"\n", current->key, current->val);
		else if (current->flag == 0 && *current->key)
			printf("declare -x %s\n", current->key);
		else if (current->flag == 1)
		{
			if (!*current->key && !*current->val)
				printf("%s", current->key);
			else
				printf("declare -x %s=\"\"\n", current->key);
		}
		current = current->next;
	}
	g_exitcode = 0;
}

char	**env_split(char *str, char lim)
{
	char	**split;
	int		i;

	split = malloc(sizeof(char *) * 3);
	if (!split)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		if (str[i] == lim)
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	if (!str)
		return (NULL);
	split[0] = ft_strdup(str);
	split[1] = ft_strdup(str + i + 1);
	split[2] = NULL;
	return (split);
}

void	for_export(t_data *data, char *line)
{
	t_env	*lst;
	char	**keyvalue;
	int		flag;
	int		eq;

	flag = 0;
	lst = data->env_lst;
	if (line && ft_strchr(line, '=') == '\0')
		eq = 0;
	else if (line)
		eq = 1;
	keyvalue = env_split(line, '=');
	if (!keyvalue)
		return ;
	check_plus(keyvalue[0], &flag);
	while (lst)
	{
		if (ft_strncmp(lst->key, keyvalue[0], ft_strlen(keyvalue[0])) == 0
			&& ft_strncmp(lst->key, keyvalue[0], ft_strlen(lst->key)) == 0)
			return (for_export_1(flag, lst, keyvalue, eq));
		lst = lst->next;
	}
	env_addback(&data->env_lst, env_new(keyvalue[0], keyvalue[1], eq));
	free(keyvalue);
	g_exitcode = 0;
}

void	for_export_1(int flag, t_env *lst, char **keyvalue, int eq)
{
	char	*tmp;

	if (eq == 0)
		return ;
	else
		lst->flag = 1;
	if (flag == 0)
	{
		free(lst->val);
		lst->val = NULL;
		lst->val = ft_strdup(keyvalue[1]);
	}
	else
	{
		tmp = lst->val;
		lst->val = NULL;
		lst->val = ft_strjoin(tmp, keyvalue[1]);
		free(tmp);
	}
	free2d(keyvalue);
	g_exitcode = 0;
}

void	ft_export(t_data *data, t_parse *pars)
{
	int		i;
	char	*tmp;
	char	**keyvalue;

	if (pars->cmd[1] == NULL)
		return (export_env(data->env_lst));
	tmp = ft_strdup(pars->cmd[1]);
	keyvalue = ft_split(tmp, '=');
	i = 1;
	while (pars->cmd && pars->cmd[i])
	{
		if (!keyvalue[0])
			ft_putstr_fd("not a valid identifier\n", 2);
		if (!keyvalue[0] || !valid_var_name(keyvalue[0]))
		{
			free(tmp);
			free2d(keyvalue);
			g_exitcode = 1;
			return ;
		}
		for_export(data, pars->cmd[i++]);
	}
	free2d(keyvalue);
	free(tmp);
}
