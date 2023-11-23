/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:41:02 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/23 14:15:07 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Retorna uma lista encadeada contendo as variáveis de ambiente.
 * 
 * Esta função recebe um array de strings contendo as variáveis de ambiente e
 * cria uma lista encadeada do tipo t_env, onde cada nó contém uma variável de
 * ambiente.
 * 
 * @param env O array de strings contendo as variáveis de ambiente.
 * @return Um ponteiro para o primeiro nó da lista encadeada.
 */
t_env	*get_env_var(char **env)
{
	int     i;
	char    *env_var;
	t_env   *res;

	i = 0;
	res = NULL;
	while (env[i])
	{
		env_var = ft_strdup(env[i]);
		env_add_back(&res, env_new(env_var));
		i++;
	}
	return (res);
}

// Replica o comando env do bash 
void	execute_env(t_commands **command)
{
	if (command && (*command)->content[1])
	{
		write(2, "env: '", 6);
		write(2, (*command)->content[1], ft_strlen((*command)->content[1]));
		write(2, "': No such file or directory\n", 29);
		g_var.exit_status = 127;
		return ;
	}
	while (g_var.env && g_var.env->data)
	{
		if (ft_strchr(g_var.env->data, '='))
			printf("%s\n", g_var.env->data);
		if (!g_var.env->next)
			break ;
		g_var.env = g_var.env->next;
	}
	env_first(&g_var.env);
	g_var.exit_status = 0;
}

