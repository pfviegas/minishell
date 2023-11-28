/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:45:16 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/28 14:17:57 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
 * Função para obter o diretório atual e atualizar a variável de ambiente PWD.
 * 
 * @param env Ponteiro para o array de strings com as variáveis de ambiente.
 */
void get_pwd(char ***env)
{
	char buf[PATH_MAX + 1];
	char *cmd;

//	obtem o diretorio atual
	getcwd(buf, sizeof(buf));
//	prepara a string de ambiente PWD
	cmd = ft_strjoin("PWD=", buf);
//	atualiza a variavel de ambiente PWD
	update_env(env, cmd);
//	verifica se a variavel de ambiente OLDPWD existe
	if (find_env_var(*env, "OLDPWD") == -1)
//		adiciona a variavel de ambiente OLDPWD ao array de variaveis de ambiente
		update_env(env, "OLDPWD");
	free(cmd);
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
void update_env_str(char **str, char *new, char *temp_env, char *temp_cmd)
{
	int env_var_len;
	int cmd_var_len;
	int len;
	int i;

//	atribui o tamanho das strings
	env_var_len = ft_strlen(temp_env);
	cmd_var_len = ft_strlen(temp_cmd);
//	verifica se a variavel de ambiente ja existe e se o comando é vazio	
	if ((*str)[env_var_len] != '\0' && new[cmd_var_len] == '\0')
		return;
	len = ft_strlen(*str);
//	remove o comando antigo da string de ambiente	
	while (len--)
		rm_last_char(str);
	i = 0;
//	adiciona o novo comando a string de ambiente
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

//	recupera o nome da variavel de ambiente
	temp_cmd = get_env_var_name(cmd);
	i = 0;
	while ((*env) && (*env)[i])
	{
//		recupera o nome da variavel de ambiente
		temp_env = get_env_var_name((*env)[i]);
		if (ft_strcmp(temp_env, temp_cmd) == 0)
		{
//PFV
/*
			printf("     env: %s\n", (*env)[i]);
			printf("     cmd: %s\n", cmd);
			printf("temp_env: %s\n", temp_env);
			printf("temp_cmd: %s\n", temp_cmd);
*/
			update_env_str(&(*env)[i], cmd, temp_env, temp_cmd);
			free(temp_env);
			free(temp_cmd);
			return ;
		}
		free(temp_env);
		i++;
	}
	free(temp_cmd);
//	adiciona o comando ao array de variaveis de ambiente	
	add_str_to_array(env, cmd);
}

/**
 * @brief Atualiza o valor da variável de ambiente SHLVL.
 *
 * Esta função recebe um ponteiro duplo para o array de variáveis de ambiente e uma string com o valor.
 * Ela incrementa o valor da variável SHLVL em 1 e atualiza o array de variáveis de ambiente de acordo.
 *
 * @param env O ponteiro duplo para o array de variáveis de ambiente.
 * @param value A string com o valor atual da variável SHLVL.
 */
void update_shlvl(char ***env, char *value)
{
	char *shell_level;
	char *new;

	if (!value)
		return;
//	incrementa o valor da variavel SHLVL	
	shell_level = ft_itoa(ft_atoi(value) + 1);
	new = ft_strjoin("SHLVL=", shell_level);
	free(shell_level);
//	atualiza o valor da variavel de ambiente SHLVL	
	update_env(env, new);
	free(new);
}

/**
 * @brief Recupera as variáveis de ambiente e atualiza o valor da variável "SHLVL".
 * 
 * Esta função recebe um array de strings representando 
 * as variáveis de ambiente e retorna uma versão modificada dele.
 * Ela copia o array original, itera por cada variável e 
 * verifica se o nome da variável é "SHLVL".
 * Se for, ela atualiza o valor da variável "SHLVL" e realiza operações adicionais.
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
//	copia o array de strings envp
	env = cp_array(envp);
	i = 0;
	while (env[i])
	{
//		recupera o nome da variavel de ambiente
		var = get_env_var_name(env[i]);
//		verifica se o nome da variavel é SHLVL
		if (!ft_strcmp("SHLVL", var))
		{
//			atualiza o valor da variavel SHLVL
			update_shlvl(&env, &env[i][ft_strlen(var) + 1]);
//			atualiza o valor da variavel PWD
			get_pwd(&env);
			free(var);
			return (env);
		}
		free(var);
		i++;
	}
//	adiciona a variavel de ambiente SHLVL ao array de variaveis de ambiente
	update_env(&env, "SHLVL=1");
//	atualiza o valor da variavel PWD
	get_pwd(&env);
	return (env);
}
