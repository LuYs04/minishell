/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:26 by armgevor          #+#    #+#             */
/*   Updated: 2024/02/06 18:42:31 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	dir_exists(const char *name)
{
	DIR	*directory;

	directory = opendir(name);
	if (directory != NULL)
	{
		closedir(directory);
		return (0);
	}
	return (-1);
}

char	*find_path(char **env)
{
	char	*path;
	int		i;

	path = "PATH=";
	i = -1;
	while (env && env[++i])
	{
		if (*env[i] == 'P')
		{
			if (!(ft_strncmp(path, env[i], 5)))
			{
				path = env[i];
				while (*path != '/')
					path++;
				return (path);
			}
		}
	}
	return (0);
}

void	check_dir(char *argv)
{
	if (!ft_strncmp(argv, ".", 1) && ft_strlen(argv) == 1)
	{
		ft_putstr_fd("LAbash: not enough arguments\n", 2);
		exit(2);
	}
	if (dir_exists(argv) == 0)
	{
		ft_putstr_fd("LAbash: is a directory\n", 2);
		exit(126);
	}
}

char	*cmd_path_existence(t_data *data, char *argv)
{
	int		i;
	char	*path;

	i = -1;
	if (!data->path)
		return (NULL);
	data->cmd_path = ft_split(data->path, ':');
	check_dir(argv);
	if (access(argv, X_OK) == 0)
		return (argv);
	while (data->cmd_path && data->cmd_path[++i] && *argv)
	{
		data->cmd_path[i] = ft_strjoin(data->cmd_path[i], "/");
		data->cmd_path[i] = ft_strjoin(data->cmd_path[i], argv);
		if (access(data->cmd_path[i], X_OK) == 0)
		{
			path = data->cmd_path[i];
			return (path);
		}
	}
	ft_putstr_fd("LAbash: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}
