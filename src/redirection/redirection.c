/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:48:25 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/01 15:04:19 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int	ft_redirect_in(t_parse *lst)
{
	lst->fd_in = open(*lst->file, O_RDONLY);
	if (lst->fd_in == -1)
	{
		close(lst->fd_in);
		ft_putstr_fd("No such file or directory\n", 2);
		g_exitcode = 1;
		return (1);
	}
	return (0);
}

int	ft_redirect_heredoc(t_parse *lst)
{
	char	*str;
	char	*lim;

	lim = *lst->delim;
	lst->fd_in = open("heredoc", O_RDWR | O_CREAT, 0644);
	while (1)
	{
		str = readline("> ");
		if (!str || (ft_strncmp(lim, str, ft_strlen(str)) == 0
				&& ft_strncmp(lim, str, ft_strlen(lim)) == 0))
		{
			free(str);
			break ;
		}
		write(lst->fd_in, str, ft_strlen(str));
		if (*str != '\n')
			write(lst->fd_in, "\n", 1);
		free(str);
	}
	close(lst->fd_in);
	lst->fd_in = open("heredoc", O_RDONLY);
	return (2);
}

int	ft_redirect_out(t_parse *lst)
{
	lst->fd_out = open(*lst->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (3);
}

int	ft_redirect_out_append(t_parse *lst)
{
	lst->fd_out = open(*lst->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (4);
}

int	ft_redirect(t_parse *lst)
{
	int	status;

	status = 0;
	if ((!lst && !lst->operator) || !*lst->operator)
		return (0);
	while (*lst->operator)
	{
		ft_redirect_cmp(lst, &status);
		if (status == -1)
			return (status);
		lst->operator++;
	}
	return (status);
}
