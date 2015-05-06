/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Water.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:17:55 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 13:05:53 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WATER_CLASS_HPP
# define WATER_CLASS_HPP

# include <cmath>
# include <ctime>
# include <cstdlib>
# include "AScenaryRain.class.hpp"
# include "AScenaryWave.class.hpp"
# include "AScenaryFlood.class.hpp"
# include "AScenaryEvap.class.hpp"
# include "AScenaryDisc.class.hpp"
# include "mod1.h"

class Water: public AScenaryRain, public AScenaryWave, public AScenaryFlood, public AScenaryEvap, public AScenaryDisc
{
	public:
		//Function
		//	Constructor
		Water(float ** Map, unsigned int sizeX, unsigned int sizeY);

		//	Destructor
		virtual ~Water(void);

		//	Clear
		virtual void ClearCurMap(void);

		//	Flowing
		virtual void Flow(void);
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

};

#endif
