/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 13:58:17 by mmartin           #+#    #+#             */
/*   Updated: 2015/01/31 12:10:15 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <list>

typedef struct		s_map
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
}					t_map;

int					display(int &, char **&, std::list<t_map>);

#endif
