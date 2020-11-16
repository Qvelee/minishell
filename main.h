/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:07:08 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/16 18:03:37 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define YELLOW	"\x1b[33m"
# define GREEN	"\x1b[32m"
# define RESET	"\x1b[0m"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

// delete this!
#include <stdio.h>

/*
**	Utils headers.
*/


typedef struct	s_envp
{
	char			*variable;
	int				type;
	struct s_envp	*next;
}				t_envp;

int		do_command(char **args, t_envp **envp_list);
t_envp	*envp_create_list(char **_envp);
void	envp_lst_clear(t_envp **envp_list, void (*delete)(void*));

void	free_matrix(char **memory);
void	exit_minishell(int code, char **args, t_envp **envp_list);
char	*envp_get_var_value(t_envp *envp_list, char *variable);

#endif
