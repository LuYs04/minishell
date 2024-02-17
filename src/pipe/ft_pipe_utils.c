/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:48:01 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/05 18:46:26 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"

char	*search_path(char **env)
{
	char	*path;
	int		i;

	path = "PATH=";
	i = 0;
	while (env && env[i])
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
		i++;
	}
	return (0);
}

char	*not_builtin_cmd_path(t_pipex *pipex, char *argv)
{
	int		i;
	char	*path;

	i = 0;
	if (builtin_compare(argv) == 1)
		return (argv);
	if (access(argv, X_OK) == 0)
		return (argv);
	pipex->path = search_path(pipex->data->env);
	pipex->cmd_path = ft_split(pipex->path, ':');
	while (pipex->cmd_path && pipex->cmd_path[i])
	{
		pipex->cmd_path[i] = ft_strjoin(pipex->cmd_path[i], "/");
		pipex->cmd_path[i] = ft_strjoin(pipex->cmd_path[i], argv);
		if (access(pipex->cmd_path[i], X_OK) == 0)
		{
			path = pipex->cmd_path[i];
			return (path);
		}
		i++;
	}
	write(1, "command not found", 18);
	exit(127);
}

void	opening_files(t_pipex *pipex)
{
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile == -1)
		ft_putstr_fd("can't open the file", 2);
	pipex->outfile = open(pipex->argv[pipex->argc - 1],
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		ft_putstr_fd("can't open the file", 2);
		exit(0);
	}
}

void	closing_files(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmds - 1)
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		i++;
	}
	close(pipex->infile);
	close(pipex->outfile);
}
