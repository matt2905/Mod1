/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScenaryDisc.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:17:55 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 13:05:53 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENARYDisc_CLASS_HPP
# define SCENARYDisc_CLASS_HPP

# include "AScenary.class.hpp"

class	AScenaryDisc: public virtual AScenary
{
	public:
		//Function
		//	Constructor
		AScenaryDisc(float **, unsigned int, unsigned int);

		//	Destructor
		virtual ~AScenaryDisc(void);

		//	SCenario
		void	DiscWorld(bool, bool, bool, bool);

	private:
		//Function
		//	Constructor
		AScenaryDisc(void);

		//	Copy
		AScenaryDisc(const AScenaryDisc &);
		AScenaryDisc	&operator=(const AScenaryDisc &);
};

#endif
