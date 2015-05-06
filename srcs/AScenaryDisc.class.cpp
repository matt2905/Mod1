/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AScenaryDisc.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:18:05 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 12:56:50 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AScenaryDisc.class.hpp"
#include <cmath>

//Public Funcions:
//	Constructor
AScenaryDisc::AScenaryDisc(float **Map, unsigned int sizeX, unsigned sizeY) :
	AScenary(Map, sizeX, sizeY)
{
}

//	Destructor
AScenaryDisc::~AScenaryDisc(void)
{
}

//	Scenario
void AScenaryDisc::DiscWorld(bool n, bool s, bool e, bool w)
{
	double	PI = std::atan(1.0);

	//	North fall
	for (unsigned int x = 0; x < _sizeX && n; x++)
	{
		_CurMap[x][0].height = 0;
		_CurMap[x][0].speed = 0;
		_CurMap[x][0].dir = PI; 
	}
	//	South fall
	for (unsigned int x = 0; x < _sizeX && s; x++)
	{
		_CurMap[x][_sizeY-1].height = 0;
		_CurMap[x][_sizeY-1].speed = 0;
		_CurMap[x][_sizeY-1].dir = 5 * PI;
	}
	//	Est fall
	for (unsigned int y = 0; y < _sizeY && e; y++)
	{
		_CurMap[0][y].height = 0;
		_CurMap[0][y].speed = 0;
		_CurMap[0][y].dir = 3 * PI;
	}
	//	West fall
	for (unsigned int y = 0; y < _sizeY && w; y++)
	{
		_CurMap[_sizeX-1][y].height = 0;
		_CurMap[_sizeX-1][y].speed = 0;
		_CurMap[_sizeX-1][y].dir = 7 * PI;
	}
}


