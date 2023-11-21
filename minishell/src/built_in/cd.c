/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:55:55 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/20 12:31:41 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/* Esta funcao muda o diretorio e atualiza a variavel de
ambiente OLDPWD caso seja necessario. Em caso de sucesso chdir retorna 0 */

int	update_pwd_oldpwd(char *str)
{
	char	buf[PATH_MAX];
	t_env	*temp_env;
	char	*temp_char;
	char	*temp_char_2;

	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		temp_env = env_search(str);
		if (temp_env)
		{
			if (temp_env->data)
				free(temp_env->data);
			temp_char = ft_strdup(buf);
			temp_char_2 = ft_strjoin(str, "=");
			temp_env->data = ft_strjoin(temp_char_2, temp_char);
			free(temp_char_2);
			free(temp_char);
			return (0);
		}
	}
	return (1);
}

int	change_dir(char *path)
{
	update_pwd_oldpwd("OLDPWD");
	if (!chdir(path) && update_pwd_oldpwd("PWD"))
		g_data.exit_status = 0;
	else
	{
		if (access(path, F_OK) == -1)
			write(2, "minishell: cd: no such file or directory\n", 42);
		else if (access(path, R_OK | W_OK | X_OK) == -1)
			write(2, "minishell: cd: permission denied\n", 34);
		else
			write(2, "minishell: cd: not a directory\n", 32);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		g_data.exit_status = 1;
	}
	return (1);
}

//void	finish_cd(char **env_char)
void	finish_cd(void)
{
//	free_str_array(&env_char);
	g_data.exit_status = 0;
	return ;
}

/* Esta funcao replica o comando cd apenas com path relativo ou absoluto.
   Existem os seguintes caos: "cd" ; "cd --" ; "cd -" ; "cd <algum caminho>" */
void	execute_cd(t_commands **command)
{
	char	*path_home;
	char	**env_char;

	lst_first(command);
	if (strlen_array((*command)->content) > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		g_data.exit_status = 1;
		return ;
	}
	env_char = lst_to_arr(g_data.env);
	path_home = env_search_str(env_char, "HOME");
	if (!(*command)->content[1] && change_dir(path_home))
//		PFV	
//		return (finish_cd(env_char));
		return (finish_cd());
	else
	{
		if (!ft_strcmp((*command)->content[1], "--") && change_dir(path_home))
//		PFV
//			return (finish_cd(env_char));
			return (finish_cd());
		change_dir((*command)->content[1]);
	}
	free_str_array(&env_char);
	return ;
}

// R_OK: Verifica se o arquivo pode ser lido.
// W_OK: Verifica se o arquivo pode ser escrito.
// X_OK: Verifica se o arquivo pode ser executado.
// F_OK: Verifica se o arquivo existe. 
