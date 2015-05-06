/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AScenaryEvap.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:18:05 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 12:56:50 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AScenaryEvap.class.hpp"

//Public Funcions:
//	Constructor
AScenaryEvap::AScenaryEvap(float **Map, unsigned int sizeX, unsigned sizeY) :
	AScenary(Map, sizeX, sizeY)
{
}

//	Destructor
AScenaryEvap::~AScenaryEvap(void)
{
}

//	Scenario
void AScenaryEvap::Evapor(void)
{
	//	Give evaporate speed;
	float	hot = 0.01;

	for (unsigned int x = 0; x < _sizeX; x++)
	{
		for (unsigned int y = 0; y < _sizeY; y++)
	{
			_CurMap[x][y].height -= hot;
			if (_CurMap[x][y].height <= 0.0)
			{
				_CurMap[x][y].height = 0;
				_CurMap[x][y].speed = 0;
			}
		}
	}

}
