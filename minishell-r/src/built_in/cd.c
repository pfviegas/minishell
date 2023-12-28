/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:55:55 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/28 13:30:01 by pviegas          ###   ########.fr       */
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
char	*get_working_directory(void)
{
	char	buf[PATH_MAX + 1];
	char	*cmd;

	getcwd(buf, sizeof(buf));
	cmd = ft_strjoin("PWD=", buf);
	return (cmd);
}

/**
 * Procura uma variável de ambiente em um array de strings.
 *
 * @param env   O array de strings contendo as variáveis de ambiente.
 * @param var   A variável de ambiente a ser procurada.
 * @return      O índice no array, ou -1 se não for encontrada.
 */
int	find_var(char **env, char *var)
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
 * Função para atualizar a variável de ambiente "PWD".
 * Verifica se a variável "PWD" já existe no ambiente.
 * Se existir, atualiza a variável "OLDPWD" com o valor atual de "PWD" 
 * e atualiza "PWD" com o novo valor.
 * Se não existir, apenas atualiza "OLDPWD" com o valor atual de "PWD".
 * 
 * @param void
 * @return void
 */
void	update_pwd_var(void)
{
	char	***ch_env;
	char	*new_pwd;
	char	*temp;

	ch_env = &shell()->env;
	new_pwd = get_working_directory();
	if (find_var(shell()->env, "PWD") == -1)
	{
		if (find_var(*ch_env, "OLDPWD") != -1)
			update_env(ch_env, "OLDPWD");
	}
	else
	{
		if (find_var(*ch_env, "OLDPWD") != -1)
		{
			temp = ft_strjoin("OLDPWD=", \
					&(*ch_env)[find_var(shell()->env, "PWD")][4]);
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
int	cd_home(void)
{
	int		i;
	char	*msg;
	char	*msg_aux;

	i = find_var(shell()->env, "HOME");
	if (i != -1)
	{
		if (chdir(&shell()->env[i][5]) == -1)
		{
			msg_aux = ft_strjoin("minishell: cd: ", &shell()->env[i][5]);
			msg = ft_strjoin(msg_aux, ": No such file or directory");
			free(msg_aux);
			display_error(1, msg, true);
			free(msg);
			return (-1);
		}
		return (0);
	}
	printf("minishell: cd: HOME not set\n");
	return (-1);
}

/**
 * Função responsável por executar o comando "cd" (change directory).
 * 
 * @param command Um array de strings contendo o comando e seus argumentos.
 */
void	execute_cd(char **command)
{
	int	i;
	int	arguments;

	i = 0;
	arguments = 0;
	while (command[++i])
	{
		if (command[i][0] != '\0')
			arguments++;
	}
	if (i == 1)
		cd_home();
	else if (arguments == 0)
		return ;
	else if (i > 3 && arguments >= 1)
		display_error(1, "minishell: cd: too many arguments", true);
	else
	{
		if (chdir(command[1]) == -1)
			execute_cd_error(command[1]);
		else
		{
			update_pwd_var();
			shell()->exit_code = 0;
		}
	}
}
