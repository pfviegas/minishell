/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:29:15 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/28 16:30:38 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_export_conditions(char *str)
{
	int	i;

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 0;
	while (str[++i] && str[i] != '=')
	{
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i] || str[i] == '_')))
			return (0);
	}
	return (1);
}

//copy an array and sort it (allocates memory)
char	**sort_alpha_array(char **array)
{
	char	**new;
	char	*temp;
	int		i;
	int		j;

	new = cp_array(array);
	i = -1;
	while (new && new[++i] && new[i + 1])
	{
		j = -1;
		while (new && new[++j] && new[j + 1])
		{
			if (ft_strcmp(new[j], new[j + 1]) > 0)
			{
				temp = new[j];
				new[j] = new[j + 1];
				new[j + 1] = temp;
			}
		}
	}
	return (new);
}

void	print_export(char **sorted_env)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (sorted_env[++i])
	{
		temp = get_env_var_name(sorted_env[i]);
		if (ft_strcmp(temp, "_") != 0)
		{
			printf("declare -x %s", temp);
			j = 0;
			while (temp[j])
				j++;
			if (sorted_env[i][j] == '=')
				printf("=\"%s\"\n", &sorted_env[i][j + 1]);
			else
				printf("\n");
		}
		free(temp);
	}
}

void	execute_export(char	**cmd)
{
	int		i;
	char	**export_array;

	i = 0;
//PFV	
//	if (!cmd || ft_strcmp(cmd[0], "export") != 0)
//		return ;
	if (!cmd[1])
	{
		export_array = sort_alpha_array(shell()->env);
		print_export(export_array);
		free_array(&export_array);
	}
	else
	{
		while (cmd[++i])
		{
			if (!check_export_conditions(cmd[i]))
			{
				write(STDERR_FILENO, " not a valid identifier\n", 24);
				shell()->exit_code = 1;
			}
			else
				update_env(&shell()->env, cmd[i]);
		}
	}
}
