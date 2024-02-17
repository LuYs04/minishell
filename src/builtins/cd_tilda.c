/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tilda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:42:41 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/05 19:36:15 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	check_plus(char *key, int *flag)
{
	char	*plus;

	plus = ft_strrchr(key, '+');
	if (plus == NULL)
	{
		*flag = 0;
		return ;
	}
	if (plus[0] == '+')
	{
		plus[0] = '\0';
		*flag = 1;
	}
	else
		*flag = 0;
}

int	check_befor_after_equol_and_plus(char **keyval, int eq, int *flag)
{
	char	*plus;

	if (eq == 1 && !keyval && !keyval[0] && !keyval[1])
	{
		ft_putstr_fd("not a valid identifier\n", 2);
		g_exitcode = 1;
		return (1);
	}
	plus = ft_strrchr(keyval[0], '+');
	if (plus && plus[0] && plus[0] == '+')
	{
		plus[0] = '\0';
		*flag = 1;
	}
	return (0);
}

void	tilda(t_data *dt, t_parse *pars, char *join)
{
	char	*valid;
	char	*olddir;
	char	*newdir;

	olddir = NULL;
	newdir = NULL;
	valid = ft_strjoin(join, pars->cmd[1] + 1);
	if (tilda_check(pars, valid) == 0)
	{
		free(valid);
		return ;
	}
	else
		just_do_cd(dt, valid, olddir, newdir);
	free(valid);
}

int	tilda_check(t_parse *pars, char *valid)
{
	(void)pars;
	if (valid_dir(valid) == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		g_exitcode = 1;
		return (0);
	}
	g_exitcode = 0;
	return (1);
}

void	find_oldpwd(t_data **data, char *oldpwd)
{
	t_env	*tmp_env;

	tmp_env = (*data)->env_lst;
	while ((*data)->env_lst)
	{
		if (ft_strncmp((*data)->env_lst->key, "OLDPWD", 6) == 0
			&& ft_strncmp((*data)->env_lst->key, "OLDPWD",
				ft_strlen((*data)->env_lst->key)) == 0)
		{
			free((*data)->env_lst->val);
			(*data)->env_lst->val = ft_strdup(oldpwd);
			break ;
		}
		(*data)->env_lst = (*data)->env_lst->next;
	}
	(*data)->env_lst = tmp_env;
}
