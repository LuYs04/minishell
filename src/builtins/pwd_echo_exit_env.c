/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_echo_exit_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:43:27 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/01 15:04:08 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void	pwd(void)
{
	char	dir[PATH_MAX];

	getcwd(dir, PATH_MAX);
	printf("%s\n", dir);
	g_exitcode = 0;
}

void	echo(char **a)
{
	int	i;
	int	j;
	int	t;

	i = 1;
	t = 0;
	while (a && a[i] && a[i][0] != '\0' && !ft_strncmp(a[i], "-n", 2))
	{
		j = 1;
		while (a[i][j] && a[i][j] == 'n')
			j++;
		if (a[i] && ft_strncmp(a[i] + j, "n", ft_strlen(a[i] + j)) != 0)
			break ;
		t = 1;
		i++;
	}
	while (a && a[i])
	{
		printf("%s", a[i++]);
		if (a[i])
			printf(" ");
	}
	if (!t)
		printf("\n");
	g_exitcode = 0;
}

int	ft_exit(t_parse *input)
{
	int	i;

	i = 0;
	if (input->cmd[1])
	{
		if (ft_atoi_exit(input->cmd[1]) == 255 || ft_strncmp(input->cmd[1],
				"9223372036854775807", ft_strlen(input->cmd[1])) > 0
			|| ft_strlen(input->cmd[1]) > ft_strlen("9223372036854775807"))
		{
			ft_putstr_fd("exit\nNumeric argument required\n", 2);
			exit(255);
		}
	}
	if (input->cmd[1] && *input->cmd[1] && input->cmd[2] && *input->cmd[2])
	{
		ft_putstr_fd("exit\nToo many arguments\n", 2);
		g_exitcode = 1;
		return (1);
	}
	if (input->cmd[1])
	{
		printf("exit\n");
		exit(ft_atoi_exit(input->cmd[1]));
	}
	exit(0);
}

void	env(t_data *data, t_parse *pars)
{
	if (pars->cmd[1])
	{
		ft_putstr_fd("No such file or directory\n", 2);
		g_exitcode = 127;
	}
	else
	{
		print_linked_list(data->env_lst);
		g_exitcode = 0;
	}
}
