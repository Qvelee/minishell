/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_static.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 10:35:00 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/28 11:01:16 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_STATIC_H
# define GET_STATIC_H
# include "structs.h"

char	**c_str(void);
t_envp	**get_envp(void);
t_line	*g_line(void);
t_coor	get_term_size(void);
t_coor	*get_cursor(void);
t_coor	*savecursor(void);
t_coor	get_cursor_start(void);
#endif
