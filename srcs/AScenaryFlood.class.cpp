/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AScenaryFlood.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:18:05 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 12:56:50 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AScenaryFlood.class.hpp"
#include <cmath>
#include <cstdlib>

//Public Funcions:
//	Constructor
AScenaryFlood::AScenaryFlood(float **Map, unsigned int sizeX, unsigned sizeY) :
	AScenary(Map, sizeX, sizeY)
{
}

//	Destructor
AScenaryFlood::~AScenaryFlood(void)
{
}

//	Scenario
void AScenaryFlood::Flood(void)
{
	double	PI = std::atan(1.0)*8;

	//	Give speed of flowing
	float	flood = 0.01;
	float	hillmin = _Map[0][0];
	float	zmin = _Map[0][0] + _CurMap[0][0].height;

	//	Check lowest point of map
	if (zmin < 1 && hillmin < 1 && hillmin > 0)
	{
		for (unsigned int x = 0; x < _sizeX && hillmin > 0; x++)
		{
			for (unsigned int y = 0; y < _sizeY && hillmin > 0; y++)
			{
				if (_Map[x][y] < hillmin)
				{
					hillmin = _Map[x][y];
					zmin = _Map[x][y] + _CurMap[x][y].height;
				}
			}
		}
	}
	zmin += flood;
	if (zmin > 1)
		zmin = 1;

	//	Add flood
	for (unsigned int x = 0; x < _sizeX; x++)
	{
		for (unsigned int y = 0; y < _sizeY; y++)
		{
			if (_Map[x][y] + _CurMap[x][y].height < zmin)
				_CurMap[x][y].height += flood;

			if (_CurMap[x][y].height == flood)
				_CurMap[x][y].dir = ((1.0 + rand()) * PI) / ((RAND_MAX + 1.0) * PI);

			//	limit flood
			if (_Map[x][y] + _CurMap[x][y].height > 1)
				_CurMap[x][y].height = 1 - _Map[x][y];
		}
	}
}
