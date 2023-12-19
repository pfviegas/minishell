/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:53:35 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/19 21:25:03 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_std
{
	int	in;
	int	out;
}	t_std;

typedef struct s_command
{
	bool	built_in;
	bool	here_doc;
	int		redirect_error;
	pid_t	proc_id;
	char	**cmd;
	char	**red;
	char	**redirect_flags;
	char	**in;
	char	**out;
	char	**here;
	int		pipe_fd[2];
	t_std	std;
}	t_command;

void	parsing(char *input);
int		pipex(char *input);
int		check_pipe(char *input);
void	init_command(t_command *seg);
char	*replace_pipe(char *str, char find_set, char replace_char);
char	**trim_parse(char **str);
char	*parse_redirection(char *seg, int *curr_pos);
void	add_char_string(char **str, char c);
char	*parse_word(char *seg, int *curr_pos);
void	expand_var(char *old_str, char **new_str, int *curr_pos);
t_list	*get_tokens(char *input_command);
void	get_tokens_2(char *input_command, int *i, t_command *new_seg);
int		get_here_doc(t_list *lst);
void	get_redirects(t_list *lst);
void	parsing_2(char *line_prompt, t_list *head);
void	free_temp(char *temp_prompt, char **parse);
void	here_doc_red(int i, t_command *token);
void	get_redirects_2(t_command *seg, int *i);
void	get_redirects_3(t_command *seg, int *i);
int		check_red_pos(char *seg, int *curr_pos);
void	get_tokens_3(char *temp, char *input_command, int *i, \
t_command *new_seg);

#endif