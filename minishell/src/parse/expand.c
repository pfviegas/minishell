/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:41:11 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/23 15:52:07 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief This function is responsible for expanding the input string by replacing
 *        any occurrences of the dollar sign ($) with the corresponding value.
 * 
 * @param input The input string to be expanded.
 * @param buf The buffer to store the expanded string.
 * @param i The index used for iterating through the input string.
 * @param j The index used for iterating through the buffer.
 */
void chg_dollar_loop(char **input, char **buf, int *i, int *j)
{
	while (input && input[0] && input[0][++i[0]])
	{
		if (input[0][i[0]] == '$' || j[0])
			buf[0][j[0]++] = input[0][i[0]];
		if ((j[0] && !ft_isalnum(input[0][i[0] + 1]) && \
			!(j[0] == 1 && input[0][i[0] + 1] == '?')) || buf[0][1] == '?')
		{
			if (j[0] == 1)
			{
				buf[0][0] = 0;
				j[0] = 0;
			}
			else
				break ;
		}
	}
}

/**
 * @brief Replaces occurrences of environment variables starting with a dollar sign ($) 
 * in the input string.
 * 
 * This function replaces environment variables in the input string with their 
 * corresponding values from the env array.
 * It recursively calls itself to handle nested environment variables.
 * 
 * @param input The input string to be processed.
 * @param env The array of environment variables.
 * @return The modified string with replaced environment variables.
 */
char	*chg_dollar(char *input, char **env)
{
	char	*buf;
	char	*new;
	char	*temp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	buf = ft_calloc(1024, 1);
	chg_dollar_loop(&input, &buf, &i, &j);
	if (!j)
	{
		free(buf);
		return (input);
	}
	temp = env_search_str(env, buf + 1);
	new = replace_str(input, buf, temp);
	if (*(buf + 1) == '?')
		free(temp);
	free(input);
	free(buf);
	return (chg_dollar(new, env));
}

/**
 * Expands variables and concatenates strings in the given division array.
 * 
 * @param division The array of strings to be expanded and concatenated.
 * @param env The environment variables.
 * @param i The current index in the division array.
 * @param k The number of divisions to be concatenated.
 */
void	expander_aux_loop(char ***division, char **env, int *i, int *k)
{
	int		j;
	char	**temp;
	char	*old;

	temp = NULL;
	temp = split_by_quotes(division[0][i[0]]);
	j = -1;
	while (temp[++j])
	{
		if (*temp[j] != '\'')
			temp[j] = chg_dollar(temp[j], env);
	}
	j = -1;
	while (temp[++j])
	{
		old = division[0][i[0] - k[0]];
		division[0][i[0] - k[0]] = ft_strjoin(old, temp[j]);
		free(old);
	}
	free_str_array(&temp);
}

/**
 * Expands the given division array by replacing variables enclosed in 
 * single quotes or double quotes with their corresponding values from 
 * the environment.
 * 
 * @param division The array of strings to be expanded.
 * @param env The array of environment variables.
 * @param i The index used for iteration.
 * @param k The index used for tracking the number of removed elements.
 */
void expander_aux(char ***division, char **env, int *i, int *k)
{
	while (division[0][++i[0]])
	{
		if (ft_strchr(division[0][i[0]], '\'') || ft_strchr(division[0][i[0]], '\"'))
			expander_aux_loop(division, env, i, k);
		else
			division[0][i[0] - k[0]] = chg_dollar(division[0][i[0]], env);
		if (!division[0][i[0] - k[0]][0])
			free(division[0][i[0] - k[0]++]);
	}
}

/**
 * Expands the given division array by replacing environment variables 
 * with their values.
 * 
 * @param division The array of strings to be expanded.
 * @param env The array of environment variables.
 * @return The expanded array of strings.
 */
char **expander(char **division, char **env)
{
	int i;
	int k;

	i = -1;
	k = 0;
	expander_aux(&division, env, &i, &k);
	while (k)
		!(division[--i] = NULL) && k--;
	free_str_array(&env);
	return division;
}