/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:47:53 by luatshem          #+#    #+#             */
/*   Updated: 2024/01/31 20:17:24 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPE_H
# define FT_PIPE_H
# define INT_PIPEX 4242

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

# include "../main/minishell.h"
# include "../../libft/libft.h"

typedef struct s_parse	t_parse;
typedef struct s_data	t_data;

typedef struct s_pipex
{
	pid_t	pid1;
	int		fd[INT_PIPEX][2];
	int		infile;
	int		outfile;
	int		cmds;
	int		argc;
	char	*path;
	char	**cmd_path;
	char	**argv;
	t_data	*data;
}		t_pipex;

char	*not_builtin_cmd_path(t_pipex *pipex, char *argv);
void	opening_files(t_pipex *pipex);
void	closing_files(t_pipex *pipex);
void	ft_pipe(char **argv, char **env, t_parse *cmd, t_data *data);
void	pip(t_pipex *pipex);
void	doing_pipe(t_pipex *pipex, int i, t_parse *cmd);
void	check_i(t_pipex *pipex, int i, t_parse *cmd);
char	*search_path(char **env);

#endif