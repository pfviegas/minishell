/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:37:51 by paulo             #+#    #+#             */
/*   Updated: 2023/12/27 17:21:58 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// trocar o cabeçalho

#ifndef UTILS_H
# define UTILS_H

void	free_array(char ***array);
char	**cp_array(char **array);
void	rm_last_char(char **str);
void	free_all(bool free_env, bool free_cmd_lst, bool std_files, bool f_exit);
void	free_lst(t_list *lst);
void	add_char(char **str, char c);
void	add_str_to_array(char ***array, char *str);
char	**create_array(char *str);
void	display_error(int exit_code, char *str, bool error);
int		is_in_set(char c, char *search_set);
int		end_word(char c, int quote);
int		end_var(char c);
void	expand_exit(char **new, int *curr_pos);
void	expander(char *old, char **new, int start, int *curr_pos);
int		get_var_size(char *str);
void	print_lst(t_list *lst);
void	init_built_in_flags(t_list *lst);
int		is_built_in(char *str);

#endif