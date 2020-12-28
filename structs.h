/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 05:46:49 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/28 22:13:39 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define MSH 11
# define BUFF_SIZE 1024

typedef struct			s_shell
{
	char	**command;
	int		mode;
	int		flag;
	int		lvl;
}						t_shell;

typedef struct			s_coor
{
	int x;
	int y;
}						t_coor;

typedef struct			s_history
{
	char				*str;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct			s_line
{
	char	*str;
	int		*i;
	char	sig;
	int		size;
}						t_line;

typedef struct			s_envp
{
	char			*variable;
	int				type;
	struct s_envp	*next;
}						t_envp;

typedef struct termios	t_term;

#endif
