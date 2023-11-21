/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:35:04 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/21 11:41:19 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

struct s_global g_data;

int	main(int argc, char **argv, char **env)
{
//	t_env	*env_list;

	(void) argc;
	(void) argv;

	g_data.env = get_env(env);

	// Exemplo de uso da função lst_add_back para adicionar comandos à lista
	t_commands *commands = NULL; // Inicialize sua lista como vazia

	// Cria um novo elemento t_commands
	t_commands *novo_comando = (t_commands *)malloc(sizeof(t_commands));
	novo_comando->content = (char *[]){"echo", "paulo", NULL};
	novo_comando->path = "";
	novo_comando->fd_master[0] = 0;
	novo_comando->fd_master[1] = 1;
	novo_comando->fd[0] = 3;
	novo_comando->fd[1] = 4;
	novo_comando->fd_master_error[0] = 0;
	novo_comando->fd_master_error[1] = 0;
	novo_comando->next = NULL;
	novo_comando->prev = NULL;
	novo_comando->ft_exec = NULL;

	// Adicione o novo elemento à lista
	lst_add_back(&commands, novo_comando);
/*
	// Exemplo de outro comando
	t_commands *outro_comando = (t_commands *)malloc(sizeof(t_commands));
	outro_comando->content = (char *[]){"ls", "-al", NULL};
	outro_comando->path = "/bin/ls";
	outro_comando->fd_master[0] = 6;
	outro_comando->fd_master[1] = 7;
	outro_comando->fd[0] = 4;
	outro_comando->fd[1] = 5;
	outro_comando->fd_master_error[0] = 0;
	outro_comando->fd_master_error[1] = 0;
	outro_comando->next = NULL;
	outro_comando->prev = NULL;
	outro_comando->ft_exec = NULL;

	lst_add_back(&commands, outro_comando);
*/

	executor(commands);

	free(novo_comando);
//	free(outro_comando);

	free_env(&g_data.env);
	return (0);
}

void	executor(t_commands *command)
{
	int		status;
	pid_t	proc_id;

	execution(command);

	lst_first(&command);
	while (command)
	{
		if (command->content[0])
		{
			proc_id = waitpid(-1, &status, 0);
			if (proc_id != -1 && WIFEXITED(status))
				g_data.exit_status = WEXITSTATUS(status);
		}
		if (!command->next)
			break ;
		command = command->next;
	}
	if (check_fds(command))
		g_data.exit_status = 1;
//	free_list(&command);
}

void	execution(t_commands *command)
{
	// guarda as variaveis de ambiente
	char	**env_vars;

	// PFV
	// Exemplo de impressão da lista
	printf("\nCOMMANDS: \n");
	print_lst(command);

	command->path = NULL;
	while (command)
	{
		if (command->content[0] && !command->fd_master_error[0] && !command->fd_master_error[1])
		{
			env_vars = lst_to_arr(g_data.env);
			command->path = get_cmd_path(env_vars, command->content);
			printf("PATH: %s\n", command->path);
//			PFV
//			free_str_array(&env_vars);
			free(env_vars);-al
			choose_execution(command);
			command_execution(command);
		}
		if (!command->next)
			break ;
		command = command->next;
	}
}

// Define a funcao a executar para cada node 
// E executada atraves da instrucao "command->ft_exec(&command);"
void	choose_execution(t_commands *command)
{
	if (!ft_strncmp(command->content[0], "pwd", 3))
		command->ft_exec = execute_pwd;
	else if (!ft_strncmp(command->content[0], "cd", 2))
		command->ft_exec = execute_cd;
//		printf("executar CD\n\n");
	else if (!ft_strncmp(command->content[0], "echo", 4))
		command->ft_exec = execute_echo;
	else if (!ft_strncmp(command->content[0], "env", 3))
		command->ft_exec = execute_env;
	else if (!ft_strncmp(command->content[0], "exit", 4))
		command->ft_exec = execute_exit;
	else if (!ft_strncmp(command->content[0], "export", 6))		
		command->ft_exec = execute_export;
//		printf("executar EXPORT\n\n");
	else if (!ft_strncmp(command->content[0], "unset", 5))
		command->ft_exec = execute_unset;-al
//		printf("executar UNSET\n\n");
	else
		command->ft_exec = execute_default;
//		printf("executar DEFAULT\n\n");
}

void	command_execution(t_commands *command)
{
	if (is_built_in(command) && (lst_size(command) == 1))
	{
		command->ft_exec(&command);
		if (command->content && (!ft_strncmp(command->content[0], "exit", 5)) && \
		free_env(&g_data.env) && free_vars() && write(2, "exit\n", 5))
			exit(g_data.exit_status);
		return ;
	}
	if (fork() == 0)
	{
		if (command->prev && command->fd_master[0] < 3)
			dup2(command->fd[0], 0);
		else if (command->fd_master[0] > 2)
			dup2(command->fd_master[0], 0);
		if (command->next && command->fd_master[1] < 3)
			dup2(command->next->fd[1], 1);
		else if (command->fd_master[1] > 2)
			dup2(command->fd_master[1], 1);
		command->ft_exec(&command);
		free_env(&g_data.env);
		free_vars();
		close(0);
		exit(g_data.exit_status);
	}
	close_fds(&command, 0);
}
