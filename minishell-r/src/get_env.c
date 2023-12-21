/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:45:16 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/21 11:16:16 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Procura uma variável de ambiente em um array de strings.
 *
 * @param env O array de strings contendo as variáveis de ambiente.
 * @param var A variável de ambiente a ser procurada.
 * @return O índice da variável de ambiente encontrada, ou -1 se não 
 * for encontrada.
 */
int	find_env_var(char **env, char *var)
{
	char	*temp;
	int		i;

	i = -1;
	while (env[++i])
	{
		temp = get_env_var_name(env[i]);
		if (!ft_strcmp(temp, var))
		{
			free(temp);
			return (i);
		}
		free(temp);
	}
	return (-1);
}

/**
 * Atualiza a string de ambiente com uma nova variável de ambiente
 * e um novo comando.
 *
 * @param str A string de ambiente a ser atualizada.
 * @param new A nova variável de ambiente a ser adicionada.
 * @param temp_env A variável de ambiente temporária.
 * @param temp_cmd O comando temporário.
 */
void	update_env_str(char **str, char *new, char *temp_env, char *temp_cmd)
{
	int	env_var_len;
	int	cmd_var_len;
	int	len;
	int	i;

	env_var_len = ft_strlen(temp_env);
	cmd_var_len = ft_strlen(temp_cmd);
	if ((*str)[env_var_len] != '\0' && new[cmd_var_len] == '\0')
		return ;
	len = ft_strlen(*str);
	while (len--)
		rm_last_char(str);
	i = 0;
	while (new[i])
	{
		add_char(str, new[i]);
		i++;
	}
}

/**
 * @brief Atualiza a variável de ambiente com o comando fornecido.
 * 
 * Esta função procura pela variável de ambiente correspondente ao comando
 * e atualiza o seu valor. Se a variável de ambiente não existir, adiciona
 * uma nova entrada ao array de ambiente.
 * 
 * @param env Um ponteiro para o array de ambiente.
 * @param cmd O comando para atualizar a variável de ambiente.
 */
void	update_env(char	***env, char *cmd)
{
	char	*temp_env;
	char	*temp_cmd;
	int		i;

	temp_cmd = get_env_var_name(cmd);
	i = 0;
	while ((*env) && (*env)[i])
	{
		temp_env = get_env_var_name((*env)[i]);
		if (ft_strcmp(temp_env, temp_cmd) == 0)
		{
			update_env_str(&(*env)[i], cmd, temp_env, temp_cmd);
			free(temp_env);
			free(temp_cmd);
			return ;
		}
		free(temp_env);
		i++;
	}
	free(temp_cmd);
	add_str_to_array(env, cmd);
}

/**
 * @brief Atualiza o valor da variável de ambiente SHLVL.
 *
 * Esta função recebe um ponteiro duplo para o array de variáveis 
 * de ambiente e uma string com o valor.
 * Ela incrementa o valor da variável SHLVL em 1 e atualiza o array
 *  de variáveis de ambiente de acordo.
 *
 * @param env O ponteiro duplo para o array de variáveis de ambiente.
 * @param value A string com o valor atual da variável SHLVL.
 */
void	update_shlvl(char ***env, char *value)
{
	char	*shell_level;
	char	*new;

	if (!value)
		return ;
	shell_level = ft_itoa(ft_atoi(value) + 1);
	new = ft_strjoin("SHLVL=", shell_level);
	free(shell_level);
	update_env(env, new);
	free(new);
}

/**
 * @brief Recupera as variáveis de ambiente e atualiza o valor
 * da variável "SHLVL".
 * 
 * Esta função recebe um array de strings representando 
 * as variáveis de ambiente e retorna uma versão modificada dele.
 * Ela copia o array original, itera por cada variável e 
 * verifica se o nome da variável é "SHLVL".
 * Se for, ela atualiza o valor da variável "SHLVL" e realiza 
 * operações adicionais.
 * Por fim, ela retorna o array modificado de variáveis de ambiente.
 * 
 * @param envp O array de strings representando as variáveis de ambiente.
 * @return O array modificado de variáveis de ambiente.
 */
char	**get_env_vars(char **envp)
{
	char	**env;
	char	*var;
	int		i;

	if (!envp)
		return (NULL);
	env = cp_array(envp);
	i = 0;
	while (env[i])
	{
		var = get_env_var_name(env[i]);
		if (!ft_strcmp("SHLVL", var))
		{
			update_shlvl(&env, &env[i][ft_strlen(var) + 1]);
			get_pwd(&env);
			free(var);
			return (env);
		}
		free(var);
		i++;
	}
	update_env(&env, "SHLVL=1");
	get_pwd(&env);
	return (env);
}
