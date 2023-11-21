/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:03:23 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/11/17 18:10:37 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void start_parse(t_prompt *parse, char *p_input)
// {
// 	char **token;
// 	t_listm *list;

// 	count_tokens(parse, p_input);
// 	token = start_list(parse, p_input);
// 	list = update_list(parse, token);	
// 	print_lst(list);
// }

void start_new(char *p_input)
{
	t_prompt2 parse;
	t_mini	*mini;
	//char **prompt_arr;
	//int i = 0;
	
	mini = init_data(&parse);
	count_quote(&parse, p_input);
	split_prompt(mini, &parse, p_input);
	// while(mini->full_cmd)
	// {
	// 	printf("%d = %s\n",i , mini->full_cmd[i]);
	// 	i++;
	// }
	
	
}

void split_prompt(t_mini *mini, t_prompt2 *parse, char *p_input)
{
	int		i;
	int 	j;
	const char	*p;
	
	i = -1;
	j = 0;
	p = p_input;
	count_words(parse, p_input, ' ');
	mini->full_cmd = (char **)malloc(sizeof(char *) * (parse->mini->n_words + 1));
	if (!p_input || !parse->mini->full_cmd)
		return ;
	alloc_input(mini, parse, p_input);
	split_input(mini, parse, p_input);
	}
void split_input(t_mini *mini, t_prompt2 *parse, char *p_input)
{
	int i;
	int j;
	int n;

	i = 0;
	j = 0;
	while(i < parse->mini->n_words)
	{
		n = 0;
		if(p_input[j] == '\"')
		{
			while(p_input[++j] != '\"')
			{
				mini->full_cmd[i][n] = p_input[j];
				printf("%d = %c\n",i , mini->full_cmd[i][n]);
				n++;
				//j++;
			}
		}
		else if(p_input[j] == '\'')
		{
			while(p_input[++j] != '\'')
			{
				mini->full_cmd[i][n] = p_input[j];
				//printf("%d = %c\n",i , mini->full_cmd[i][n]);
				n++;
				//j++;
			}
		}
		else
        {
             while (p_input[j] && p_input[j] != ' ' && p_input[j] != '\'' && p_input[j] != '\"')
            {
				mini->full_cmd[i][n] = p_input[j];
			//	printf("%d = %c\n",i , mini->full_cmd[i][n]);
				n++;
				j++;
			}
			//j++;
        }
		
		printf("%d = %s\n",i , mini->full_cmd[i]);
		i++;
	}
}

void alloc_input(t_mini *mini, t_prompt2 *parse, char *p_input)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < parse->mini->n_words)
	{
		if(p_input[j++] == '\"')
		{
			while(p_input[j] != '\"')
				j++;
			if(p_input[j + 1] == ' ')
				j++;
		}
		else if(p_input[j++] == '\'')
		{
			while(p_input[j] != '\'')
				j++;
			if(p_input[j + 1] == ' ')
				j++;	
		}
		else
        {
             while (p_input[j] && p_input[j] != ' ' && p_input[j] != '\'' && p_input[j] != '\"')
                j++;
        }
		mini->full_cmd[i] = (char *)malloc(sizeof(char *) * j + 1);
		i++;	
	}
}

void	count_words(t_prompt2 *parse, const char *s, char c)
{
	int i;

    i = 0;
    while (s && s[i])
    {
		if (s[i++] == '\"' && parse->d_quote != 0)
        {
            while (s[i] != '\"')
                i++;
			if(s[i + 1] == c)
				i++;
            parse->d_quote -= 2;
        }
		else if (s[i++] == '\'' && parse->s_quote != 0)
        {
            while (s[i] != '\'')
                i++;
			if(s[i + 1] == c)
				i++;
			parse->s_quote -= 2;
        }
        else
        {
             while (s[i] && s[i] != c && s[i] != '\'' && s[i] != '\"')
                i++;
        }
        parse->mini->n_words++;
		i++;
    }
}

char	*next_word(const char **s, char c)
{
	const char	*start;
	char		*word;

	while (**s && **s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	word = ft_substr(start, 0, *s - start);
	if (!word)
	{
		free(word);
		return (NULL);
	}
	if (**s)
		(*s)++;
	return (word);
}

void count_quote(t_prompt2 *parse, char *p_input)
{
	int i;

	i = 0;
	while(p_input && p_input[i])
	{
		if(p_input[i] == '\"')
			parse->d_quote++;
		if(p_input[i] == '\'')
			parse->s_quote++;	
		i++;
	}
	if(parse->d_quote % 2 != 0 || parse->s_quote % 2 != 0)
	{
		printf("dquote>\n");
		exit (1);
	}
}

t_mini *init_data(t_prompt2 *parse)
{
	t_mini	*mini;
	
	mini = (t_mini *)malloc(sizeof(t_mini));
	if(!mini)
		return (NULL) ;
	parse->cmds = NULL;
	parse->envp = NULL;
	parse->mini = mini;
	parse->pid= 0;
	parse->d_quote = 0;
	parse->s_quote = 0;
	mini->full_path = NULL;
	mini->outfile = 0;
	mini->infile = 0;
	mini->n_words = 0;
	mini->full_cmd = NULL;
	mini->full_cmd = (char **)malloc(sizeof(char *));
	if(!mini->full_cmd)
		return (NULL) ;

return (mini);
}
	 
	
