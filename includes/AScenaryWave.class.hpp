/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AScenaryWave.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:17:55 by tbalea            #+#    #+#             */
/*   Updated: 2015/05/07 12:48:01 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASCENARYWAVE_CLASS_HPP
# define ASCENARYWAVE_CLASS_HPP

# include "AScenary.class.hpp"

class	AScenaryWave: virtual AScenary
{
	public:
		//Function
		//	Constructor
		AScenaryWave(float **, unsigned int, unsigned int);

		//	Destructor
		~AScenaryWave(void);

		//	Scenario
		void	Waves(bool, bool, bool, bool);

	private:
		//Function
		//	Constrcutor
		AScenaryWave(void);

		//	Copy
		AScenaryWave(const AScenaryWave &);
		AScenaryWave	&operator=(const AScenaryWave &);

		//	Wave functions
		float WavesMin(bool n, bool s, bool e, bool w);
};

#endif
