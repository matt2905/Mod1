/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AScenaryRain.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:18:05 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 12:56:50 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AScenaryRain.class.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>

//Public Funcions:
//	Constructor
AScenaryRain::AScenaryRain(float **Map, unsigned int sizeX, unsigned sizeY) :
	AScenary(Map, sizeX, sizeY)
{
}

//	Destructor
AScenaryRain::~AScenaryRain(void)
{
}

//	Scenario
void AScenaryRain::Rainy(void)
{
	double	PI = std::atan(1.0)*8;

	//	Give speed of flowing
	float			rainy = 0.01;

	//	Give density (lowest is the number, higher is the density)
	unsigned int	density = 1000;
	unsigned int	precipitate = (_sizeX * _sizeY) / density;
	unsigned int	x;
	unsigned int	y;

	std::srand(std::time(NULL));
	for (unsigned int rain = 0; rain < precipitate; rain++)
	{
		x = rand() % _sizeX;
		y = rand() % _sizeY;
		if (_Map[x][y] + _CurMap[x][y].height + rainy < 1)
		{
			_CurMap[x][y].height += rainy;

			//	Give random direction
			if (_CurMap[x][y].height == rainy)
				_CurMap[x][y].dir = ((rand() + 1.0) * PI) / ((1.0 + RAND_MAX) * PI);
		}
	}
}


