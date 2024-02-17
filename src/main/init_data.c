/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:42:52 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/01 15:04:34 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_message_for_la_bash(void)
{
	ft_putstr_fd("No such file or directory\n", 2);
	exit(EXIT_FAILURE);
}

void	child_ps(t_parse *input, t_data *data)
{
	int		status;
	pid_t	child;

	status = ft_redirect(input);
	if (status == -1)
		return ;
	child = fork();
	signal(SIGQUIT, ft_sigquit);
	signal(SIGINT, ft_sigline);
	if (child == 0)
	{
		if (!*input->cmd)
			exit(EXIT_FAILURE);
		if (!data->path && input->cmd[0][0] != '/')
			exit_message_for_la_bash();
		ft_redirect_dup(input, status);
		data->join_path = cmd_path_existence(data, input->cmd[0]);
		if (!data->join_path)
			execve(input->cmd[0], input->cmd, data->env);
		execve(data->join_path, input->cmd, data->env);
	}
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		g_exitcode = WEXITSTATUS(status);
}

void	conditions(t_parse *input, t_data *data)
{
	if (input)
	{
		if (check_pipe(input))
			ft_pipe(struct_to2arr(input), data->env, input, data);
		else if (!check_builtin_with_redirect(input, data))
			child_ps(input, data);
	}
}

int	if_is_empty__free(char *str, t_parse *input)
{
	if (*str)
		add_history(str);
	free(str);
	free(input->cmd);
	free(input->file);
	free(input->delim);
	free(input->operator);
	free(input->index);
	free(input);
	g_exitcode = 0;
	return (1);
}

void	data_init(t_data *data)
{
	char	*str;
	t_parse	*input;

	while (1)
	{
		sig_event_loop();
		str = readline(MINISHELL);
		if (!str)
			ctrl_d_exit();
		input = parsing(str, data->env_lst);
		if (input && !*input->cmd && !*input->file && !*input->delim)
		{
			if (str && if_is_empty__free(str, input))
				continue ;
		}
		init_cont_1(data, input, &str);
	}
}
