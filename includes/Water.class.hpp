/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:17:55 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/23 19:51:37 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WATER_CLASS_HPP
# define WATER_CLASS_HPP

# include "Map.class.hpp"
# include "Water.h"
# include <cmath>
# include <ctime>
# include <cstdlib>

class Water {
	public:
		//Function
		//	Constructor
		Water(float ** Map, unsigned int sizeX, unsigned int sizeY);

		//	Destructor
		~Water(void);

		//	Setter
		//		No setter

		//	Getter
		t_water ** getCurMap(void);

		//	Scenario
		void Rainy(void);
		void Waves(bool n, bool s, bool e, bool w);
		void Flood(void);
		void Evapor(void);
		void DiscWorld(bool n, bool s, bool e, bool w);

		//	Clear
		void ClearCurMap(void);

		//	Flowing
		void Flow(void);
	private:
		//Function
		//	Constructor
		Water(void);

		//	Copy
		Water(const Water & water);
		Water & operator=(const Water & water);

		//	Calcul flow
		void Drop(void);
		void DropNew(unsigned int x, unsigned int y, float dir, float speed);
		void Speed(void);
		float Transfert(unsigned int x1, unsigned int y1, unsigned int x2,
				unsigned int y2, float drop);
		void NewDir(unsigned int x, unsigned int y, float dir, float speed);
		void NewSpd(unsigned int x, unsigned int y, float dir, float spd, float odir);
//		void Moving(void);

		//	Wave functions
		float WavesMin(bool n, bool s, bool e, bool w, float wave);

		//Attribute
		//	Map Data
		bool _w;
		bool _s;
		bool _e;
		bool _n;
		float ** _Map;
		unsigned int _sizeX;
		unsigned int _sizeY;
		t_water ** _CurMap;
};

#endif
