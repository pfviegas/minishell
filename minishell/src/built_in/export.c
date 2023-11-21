/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:29:15 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/20 11:42:54 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_export(char **array)
{
	int	i;
	int	j;
	int	quotes;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
	{
		printf("declare -x ");
		j = 0;
		quotes = 0;
		while (array[i][j])
		{
			printf("%c", array[i][j]);
			if (array[i][j] == '=' && !quotes)
			{
				printf("\"");
				quotes = 1;
			}
			j++;
		}
		printf("\"\n");
	}
}

void	export_error(t_commands **lst, char **str, int i)
{
	write(2, "minishell: export: \'", 21);
	write(2, ((*lst)->content[i]), ft_strlen((*lst)->content[i]));
	write(2, "\' not a valid identifier\n", 26);
	free_str_array(&str);
	g_data.exit_status = 1;
}

void	core_export(t_commands **lst, char **str, int i)
{
	t_env	*lst_env_export;

	lst_env_export = NULL;
	if (!str || !str[0])
	{
		export_error(lst, str, i);
		return ;
	}
	lst_env_export = env_search(str[0]);
	if (!lst_env_export)
		env_add_back(&(g_data.env), \
		env_new(ft_strdup((*lst)->content[i])));
	if (lst_env_export)
	{
		if (str[1])
		{
			free(lst_env_export->data);
			lst_env_export->data = ft_strdup((*lst)->content[i]);
		}
	}
	g_data.exit_status = 0;
	free_str_array(&str);
}

void	export_only(void)
{
	char	**char_env;

	char_env = lst_to_arr(g_data.env);
	sort_array(char_env, strlen_array(char_env));
	print_export(char_env);
//	PFV	
//	free_str_array(&char_env);
	return ;
}

void	execute_export(t_commands **command)
{
	char	**var;
	int		i;
	// verifica se so existe uma variavel a exportar [0] ou seja se [1] e nulo
	if (!(*command)->content[1])
		export_only();
	i = 1;

	while ((*command)->content[i])
	{
		var = ft_split((*command)->content[i], '=');
		if ((*command)->content[i][0] == '=' || (var && !str_is_alphanum(var[0])) \
		|| ft_isdigit((*command)->content[i][0]))
			export_error(command, var, i);
		else
			core_export(command, var, i);
		i++;
	}

}