/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:42:41 by luatshem          #+#    #+#             */
/*   Updated: 2024/01/31 19:45:04 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	dt;

	(void)av;
	dt.env_lst = NULL;
	if (ac > 1)
	{
		printf("Don't sent any arguments!\n");
		return (1);
	}
	env_scan(env, &dt);
	g_exitcode = 0;
	data_init(&dt);
	return (0);
}
