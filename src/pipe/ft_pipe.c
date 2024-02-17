/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:43 by luatshem          #+#    #+#             */
/*   Updated: 2024/01/31 20:17:02 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"

void	check_i(t_pipex *pipex, int i, t_parse *cmd)
{
	if (*cmd->operator && **cmd->operator == '<'
		&& *(*cmd->operator + 1) == '<')
		return ;
	if (i == 2)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->fd[i - 2][1], STDOUT_FILENO);
	}
	else if (i == pipex->cmds - 1)
	{
		i--;
		dup2(pipex->outfile, STDOUT_FILENO);
		dup2(pipex->fd[i - 2][0], STDIN_FILENO);
	}
	else
	{
		dup2(pipex->fd[i - 3][0], STDIN_FILENO);
		dup2(pipex->fd[i - 2][1], STDOUT_FILENO);
	}
}

void	doing_pipe(t_pipex *pipex, int i, t_parse *cmd)
{
	char	**args;
	char	*path;
	int		status;

	sig_event_loop();
	status = ft_redirect(cmd);
	signal(SIGQUIT, ft_sigquit);
	signal(SIGINT, ft_sigline);
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
	{
		opening_files(pipex);
		args = ft_split(pipex->argv[i], ' ');
		path = not_builtin_cmd_path(pipex, args[0]);
		check_i(pipex, i, cmd);
		ft_redirect_dup(cmd, status);
		closing_files(pipex);
		if (check_builtin(cmd, pipex->data) == 1)
			exit(EXIT_SUCCESS);
		execve(path, args, pipex->data->env);
	}
}

void	pip(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmds - 1)
		pipe(pipex->fd[i++]);
}

void	ft_pipe(char **argv, char **env, t_parse *cmd, t_data *data)
{
	t_pipex	pipex;
	int		i;
	int		status;

	(void)env;
	pipex.argc = lst_size(cmd) + 3;
	pipex.argv = argv;
	pipex.data = data;
	i = 2;
	pipex.cmds = pipex.argc - 1;
	pip(&pipex);
	while (i < pipex.cmds)
	{
		doing_pipe(&pipex, i++, cmd);
		cmd = cmd->next;
	}
	closing_files(&pipex);
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		g_exitcode = WEXITSTATUS(status);
	free2d(argv);
}
