/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 13:45:14 by mmartin           #+#    #+#             */
/*   Updated: 2015/01/28 16:23:45 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <list>
#include <iostream>
#include <fstream>
#include "map.h"
#include "Map.hpp"

void	ft_get_coord(char *str, std::list<t_map> *map)
{
	char	*tmp;
	int		i;
	t_map	coord;

	i = 0;
	tmp = strtok(str, ",");
	while (tmp)
	{
		if (i == 0)
			coord.x = strtoul(tmp, NULL, 10);
		else if (i == 1)
			coord.y = strtoul(tmp, NULL, 10);
		else
			coord.z = strtoul(tmp, NULL, 10);
		i++;
		tmp = strtok(NULL, ",");
	}
	map->push_back(coord);
}

void	ft_parse(char *argv, std::list<t_map> *map)
{
	std::ifstream	ifs(argv);
	std::string		line;
	char			*str;
	char			*ptr;

	while (getline(ifs, line))
	{
		if (!line.length())
			continue ;
		str = strtok_r(const_cast<char *>(line.c_str()), " ()", &ptr);
		while (str)
		{
			ft_get_coord(str, map);
			str = strtok_r(NULL, " ()", &ptr);
		}
	}
}

int		main(int argc, char **argv)
{
	std::list<t_map>	mapHill;
	Map					map;
	unsigned int		**osef;

	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " file" << std::endl;
		return (1);
	}
	ft_parse(argv[1], &mapHill);
	map.setMapHill(mapHill);

	osef = map.getMap();
	for (int y = 0; y < 1000; y++)
	{
		for (int x = 0; x < 1000; x++)
		{
			if (osef[y][x])
				std::cout << "y: " << y << ", x: " << x << ", z: " << osef[y][x] << std::endl;
		}
	}
	return (0);
}
