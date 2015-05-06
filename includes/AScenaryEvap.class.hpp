/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScenaryEvap.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:17:55 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 13:05:53 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENARYEvap_CLASS_HPP
# define SCENARYEvap_CLASS_HPP

# include "AScenary.class.hpp"

class	AScenaryEvap: public virtual AScenary
{
	public:
		//Function
		//	Constructor
		AScenaryEvap(float **, unsigned int, unsigned int);

		//	Destructor
		virtual ~AScenaryEvap(void);

		//	SCenario
		void	Evapor(void);

	private:
		//Function
		//	Constructor
		AScenaryEvap(void);

		//	Copy
		AScenaryEvap(const AScenaryEvap &);
		AScenaryEvap	&operator=(const AScenaryEvap &);
};

#endif
