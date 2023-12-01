/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:55:55 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/01 13:42:18 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Retorna uma string formatada contendo o diretório atual 
 * no formato de variável de ambiente.
 *
 * @return   A string formatada contendo o diretório atual 
 * no formato "PWD=diretorio_atual".
 */
char *get_pwd_env_format(void)
{
	char buf[PATH_MAX + 1];
	char *cmd;

	getcwd(buf, sizeof(buf));
	cmd = ft_strjoin("PWD=", buf);
	return cmd;
}

/**
 * Procura uma variável de ambiente em um array de strings.
 *
 * @param env   O array de strings contendo as variáveis de ambiente.
 * @param var   A variável de ambiente a ser procurada.
 * @return      O índice no array, ou -1 se não for encontrada.
 */
int find_var(char **env, char *var)
{
	char *temp;
	int i;

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
 * Função para atualizar a variável de ambiente "PWD".
 * Verifica se a variável "PWD" já existe no ambiente.
 * Se existir, atualiza a variável "OLDPWD" com o valor atual de "PWD" 
 * e atualiza "PWD" com o novo valor.
 * Se não existir, apenas atualiza "OLDPWD" com o valor atual de "PWD".
 * 
 * @param void
 * @return void
 */
void update_pwd_var(void)
{
	char ***ch_env;
	char *new_pwd;
	char *temp;

//	guarda as variáveis de ambiente em um ponteiro para ponteiro de char
	ch_env = &shell()->env;
//	cria uma string formatada contendo o diretório atual
	new_pwd = get_pwd_env_format();
//	verifica se a variável "PWD" já existe no ambiente
	if (find_var(shell()->env, "PWD") == -1)
	{
//		se não existir, atualiza apenas a variável "OLDPWD"
		if (find_var(*ch_env, "OLDPWD") != -1)
			update_env(ch_env, "OLDPWD");
	}
	else
	{
//		se existir, atualiza a variável "OLDPWD" e "PWD"
		if (find_var(*ch_env, "OLDPWD") != -1)
		{
			temp = ft_strjoin("OLDPWD=", &(*ch_env)[find_var(shell()->env, "PWD")][4]);
			update_env(ch_env, temp);
			free(temp);
			update_env(ch_env, new_pwd);
		}
		else
			update_env(ch_env, new_pwd);
	}
	free(new_pwd);
}

/**
 * Função para navegar até o diretório HOME do usuário.
 * 
 * @return 0 se a navegação for bem-sucedida
 *        -1 caso contrário.
 */
int cd_home(void)
{
	int		i;
	char	*msg;
	char	*msg_aux;

//	procura a variavel HOME no ambiente
	i = find_var(shell()->env, "HOME");
//	se a variavel for encontrada, navega até o diretório
	if (i != -1)
	{
//		verifica se o diretório existe
		if (chdir(&shell()->env[i][5]) == -1)
		{
			msg_aux = ft_strjoin("minishell: cd: ", &shell()->env[i][5]);
			msg = ft_strjoin(msg_aux, ": No such file or directory");
			free(msg_aux);
			display_error(1, msg, true);
			free(msg);
//PFV
//			perror("Error:");
//			shell()->exit_code = 1;
			return (-1);
		}
		return (0);
	}
	printf("var Home disabled\n");
	return (-1);
}

/**
 * Função responsável por executar o comando "cd" (change directory).
 * 
 * @param command Um array de strings contendo o comando e seus argumentos.
 */
void execute_cd(char **command)
{
	int		i;
	char	*msg;
	char	*msg_aux;

	i = 0;
//	verifica se o comando possui argumentos
	while (command[i])
		i++;
//	se o comando não possuir argumentos, navega até o diretório HOME
	if (i == 1)
	{
		cd_home();
		return;
	}
//	se o comando possuir mais de 2 argumentos, exibe uma mensagem de erro	
	else if (i > 2)
	{
		display_error(1, "minishell: cd: too many arguments", true);
		return;
	}
//	se o comando possuir 2 argumentos, navega até o diretório especificado
	else
	{
		if (chdir(command[1]) == -1)
		{
			msg_aux = ft_strjoin("minishell: cd: ", command[1]);
			msg = ft_strjoin(msg_aux, ": No such file or directory");
			free(msg_aux);
			display_error(1, msg, true);
			free(msg);
			shell()->exit_code = 1;
			return;
		}
	}
	update_pwd_var();
	shell()->exit_code = 0;
}
