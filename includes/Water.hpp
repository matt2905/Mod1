/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:17:55 by tbalea            #+#    #+#             */
/*   Updated: 2015/02/13 22:28:31 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WATER_HPP
# define WATER_HPP

# include "Map.hpp"
# include "Water.h"
# include <cmath>

class Water {
	public:
		//Function
		//	Constructor
		Water( float ** Map, unsigned int sizeX, unsigned int sizeY);

		//	Destructor
		~Water( void );

		//	Setter
		//		No setter

		//	Getter
		t_water ** getCurMap( void );

		//	Scenario
		void Rainy( void );
		void Waves( bool n, bool s, bool e, bool w );
		void Flood( void );

		//	Flowing
		void Flow( void );
	private:
		//Function
		//	Constructor
		Water( void );

		//	Copy
		Water( const Water & water );
		Water & operator=( const Water & water );

		//	Calcul flow
		void Speed( void );
		void Drop( void );
//		void Moving( void );

		//	Clear
		void ClearCurMap( void );

		//Attribute
		//	Map Data
		float **& _Map;
		unsigned int _sizeX;
		unsigned int _sizeY;
		t_water ** _curMap;
};

#endif
