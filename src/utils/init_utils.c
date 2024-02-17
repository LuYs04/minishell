/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:44:43 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/06 18:17:16 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

char	*check_exit_code(char *buf)
{
	char	*temp;

	temp = buf;
	if (!g_exitcode)
		buf = ft_itoa(0);
	else
		buf = ft_itoa(g_exitcode);
	free(temp);
	return (buf);
}

t_parse	*init_parse(t_parse *input)
{
	t_parse	*temp;
	t_parse	*t_input;
	t_parse	*head;
	int		size;

	t_input = input;
	size = lst_size(input);
	temp = NULL;
	head = NULL;
	if (!input)
		return (NULL);
	while (size && size--)
	{
		temp = malloc(sizeof (t_parse));
		temp->cmd = t_input->cmd;
		temp->operator = t_input->operator;
		temp->file = t_input->file;
		temp->delim = t_input->delim;
		temp->index = t_input->index;
		temp->next = NULL;
		temp->prev = NULL;
		ft_doublelist_add_back(&head, temp);
		t_input = t_input->next;
	}
	return (head);
}

void	init_cont_1(t_data *data, t_parse *input, char **str)
{
	t_parse	*input_free;

	data->env = join_key_and_val(data->env_lst);
	data->path = find_path(data->env);
	input_free = init_parse(input);
	conditions(input, data);
	unlink("heredoc");
	data->join_path = NULL;
	if (**str)
		add_history(*str);
	free2d(data->env);
	free_input(input_free, input);
	free(*str);
}

void	print_linked_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (*current->key && *current->val)
			printf("%s=%s\n", current->key, current->val);
		else if (current->flag == 1)
			printf("%s=\n", current->key);
		current = current->next;
	}
}
