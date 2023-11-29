/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:53:35 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/29 17:34:40 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct	s_std
{
	int	in;
	int	out;
}	t_std;

typedef struct s_command
{
	bool	built_in;
	bool	here_doc;
	int		red_error;
	pid_t	proc_id;
	char	**cmd;
	char	**red;
	char	**red_flags;
	char	**in;
	char	**out;
	char	**here;
	bool	append;
	int		pipe_fd[2];
	t_std	std;
}	t_command;

void	parsing(char *input);
int		pipe_sintax(char *input);
int		check_pipe(char *input);
void	init_command(t_command *seg);
int		is_in_set(char c, char *search_set);
int		is_great_less(char c);
char	*replace_pipe(char *str, char find_set, char replace_char);
char	**trim_parse(char **str);
char	*parse_redirection(char *seg, int *curr_pos);
void	add_char_string(char **str, char c);
char	*parse_word(char *seg, int *curr_pos, char *red);
void	expand_var(char *old_str, char **new_str, int *curr_pos);
t_list	*get_tokens(char *input_command);


int		is_token(char c);
void	add_str_to_array(char ***array, char *str);
void	readline_error(char *error, int code, bool need_free);

#endif