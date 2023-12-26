/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:12:04 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/26 17:48:43 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	prompt_user_input(t_command *cmd, int *i)
// {
// 	char	*line;

// 	line = NULL;
// 	while (true)
// 	{
// 		write(0, "> ", 2);
// 		line = ft_get_next_line(0);
// 		printf("cmd->here[%d] = %s\n",*i, cmd->here[*i]);
// 		if (!line)
// 		{
// 			here_doc_error(cmd->here[*i]);
// 			break ;
// 		}
// 		printf("ft_strncmp = %d\n",ft_strncmp(line, cmd->here[*i], ft_strlen(cmd->here[*i])));
// 		if (!(ft_strncmp(line, cmd->here[*i], ft_strlen(cmd->here[*i]))))
// 		{
// 			printf("saida cmd->here[%d] = %s\n",*i, cmd->here[*i]);
// 			free(line);
// 			break ;
// 		}
// 		if (cmd->here[*i + 1] == NULL)
// 		{
// 			printf("i= %d\n" , *i);
// 			here_doc_expand_var(&line, cmd);
// 			write(shell()->here_doc_fd[1], line, ft_strlen(line));
// 		}
// 		free(line);
// 		line = NULL;
// 	}
// }

/**
 * Função responsável por lidar com a entrada do here document.
 * 
 * @param cmd O comando que contém as informações do here document.
 */
void	here_doc_input(t_command *cmd)
{
	char	*line;

	line = NULL;
	while (true)
	{
		write(0, "> ", 2);
		line = ft_get_next_line(0);
		if (!line)
		{
			here_doc_error(cmd->here[*i]);
			break ;
		}
		if (!(ft_strncmp(line, cmd->here[*i], ft_strlen(cmd->here[*i]))))
		{
			free(line);
			break ;
		}
		if (cmd->here[*i + 1] == NULL)
		{
			here_doc_expand_var(&line, cmd);
			write(shell()->here_doc_fd[1], line, ft_strlen(line));
		}
		free(line);
		line = NULL;
	}
}

char	*remove_quotes(char *str)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc(len - 1);
	if (new_str)
	{
		ft_memcpy(new_str, &str[1], len - 2);
		new_str[len - 2] = '\0';
	}
	printf("%s\n", new_str);
	return (new_str);
}

/**
 * Função que executa o redirecionamento de entrada usando o "here document".
 * 
 * @param cmd O comando a ser executado.
 * @return O descritor de arquivo para leitura do "here document".
 */
int	here_doc(t_command *cmd)
{
	pid_t	pid;

	shell()->in_here_doc = true;
	if (pipe(shell()->here_doc_fd) < 0)
		perror("pipe error");
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_here_doc);
		if (cmd->here[0][0] == '"' && cmd->here[0][ft_strlen(cmd->here[0]) - 1] == '"')
			cmd->here[0] = remove_quotes(cmd->here[0]);
		here_doc_input(cmd);
		signals_behavior();
		close_here_doc();
		exit(0);
	}
	wait(&pid);
	close(shell()->here_doc_fd[1]);
	shell()->in_here_doc = false;
	return (shell()->here_doc_fd[0]);
}
