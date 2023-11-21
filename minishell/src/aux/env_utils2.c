/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:17:19 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/09 16:01:48 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	search_number(char *s1, char *s2)
{
	int	res;
	int	i;

	res = ft_strlen(s2);
	i = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	if (i > res)
		return (i);
	return (res);
}

// Procura na variavel env a string cujo nome da
// variavel seja o segundo argumento str */
char	*env_search_str(char **env, char *str)
{
	int		i;
	char	*temp;

	i = 0;
	while (env && env[i] && \
		ft_strncmp(env[i], str, search_number(env[i], str)))
		i++;
	if (*str == '?')
		return (ft_itoa(g_data.exit_status));
	if (!env[i] || !str || !*str)
		return ("");
	temp = (env[i] + ft_strlen(str));
	if (*temp == '=')
		temp++;
	return (temp);
}

size_t	var_len(char *env_str)
{
	int	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	return (i);
}

// Procura na linked list se existe um node com o nome do argumento
t_env	*env_search(char *input_var)
{
	t_env	*lst_env;

	lst_env = g_data.env;
	env_first(&lst_env);
	while (lst_env && lst_env->data)
	{
		lst_env = lst_env->next;
		if (!lst_env)
			break ;
		if (!ft_strncmp(lst_env->data, input_var, ft_strlen(input_var)) \
			&& var_len(lst_env->data) == ft_strlen(input_var))
			return (lst_env);
	}
	return (NULL);
}

/* Calcula o tamanho da lista */
int	env_lst_size(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
