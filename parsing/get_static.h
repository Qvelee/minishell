/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_static.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 10:35:00 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:05:57 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_STATIC_H
# define GET_STATIC_H
# include "structs.h"

t_envp	**get_envp(void);
t_line	*get_line(void);
t_coor	get_term_size(void);
t_coor	*get_cursor(void);
t_coor	*savecursor(void);
t_coor	get_cursor_start(void);
#endif
