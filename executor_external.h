/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:05:06 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/28 09:51:35 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_EXTERNAL_H
# define EXECUTOR_EXTERNAL_H

# include "structs.h"

int			do_command(char **args, t_envp **envp_list);
char		*envp_get_var_value(t_envp *envp, char *variable);

#endif
