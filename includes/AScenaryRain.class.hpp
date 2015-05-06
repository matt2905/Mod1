/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScenaryRain.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:17:55 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 13:05:53 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENARYRAIN_CLASS_HPP
# define SCENARYRAIN_CLASS_HPP

# include "AScenary.class.hpp"

class	AScenaryRain: public virtual AScenary
{
	public:
		//Function
		//	Constructor
		AScenaryRain(float **, unsigned int, unsigned int);

		//	Destructor
		virtual ~AScenaryRain(void);

		//	Scenario
		void	Rainy(void);

	private:
		//Function
		//	Constructor
		AScenaryRain(void);

		//	Copy
		AScenaryRain(const AScenaryRain &);
		AScenaryRain	&operator=(const AScenaryRain &);
};

#endif
