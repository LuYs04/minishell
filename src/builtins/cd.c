/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:39:18 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/01 15:00:40 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	print_cd_minus_error(void)
{
	printf ("LAbash: cd: OLDPWD is not set\n");
	g_exitcode = 1;
}

void	minus_in_pwd(t_data *dt, char *s)
{
	char	*prev;
	char	oldpwd[PATH_MAX];

	if (s && (s[1] && s[2]) && (s[1] != '-' || s[1] != '\0'))
	{
		if (s[2] && s[2] != '\0')
		{
			ft_putstr_fd("LAbash: cd: invalid option\n", 2);
			g_exitcode = 1;
			return ;
		}
	}
	prev = find_user(dt, "OLDPWD");
	getcwd(oldpwd, PATH_MAX);
	if (!chdir(prev))
	{
		find_oldpwd(&dt, oldpwd);
		if (s[1] != '-')
			pwd();
		g_exitcode = 0;
		return ;
	}
	else
		print_cd_minus_error();
}

void	just_do_cd(t_data *dt, char *user, char *olddir, char *newdir)
{
	olddir = getcwd(0, 0);
	chdir(user);
	find_variable(dt, "OLDPWD", olddir);
	newdir = getcwd(0, 0);
	find_variable(dt, "PWD", newdir);
	free(olddir);
	free(newdir);
	g_exitcode = 0;
}

char	*find_user(t_data *data, char *usr)
{
	t_env	*env;
	char	*whoisthat;

	whoisthat = ft_strjoin(usr, "=");
	env = data->env_lst;
	while (ft_strncmp(env->key, whoisthat,
			ft_strlen(env->key)) != 0
		&& ft_strncmp(env->key, whoisthat,
			ft_strlen(whoisthat)) != 0)
		env = env->next;
	free(whoisthat);
	return (env->val);
}

void	cd(t_data *dt, t_parse *pars)
{
	char	*olddir;
	char	*newdir;
	char	*user;
	char	*joined;

	olddir = NULL;
	newdir = NULL;
	user = find_user(dt, "USER");
	joined = ft_strjoin("/Users/", user);
	if (pars->cmd[1] == NULL)
		just_do_cd(dt, joined, olddir, newdir);
	else if (pars->cmd[1][0] == '-')
		minus_in_pwd(dt, pars->cmd[1]);
	else if (pars->cmd[1][0] == '~')
		tilda(dt, pars, joined);
	else if (valid_dir(pars->cmd[1]) == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		g_exitcode = 1;
	}
	else
		just_do_cd(dt, pars->cmd[1], olddir, newdir);
}
