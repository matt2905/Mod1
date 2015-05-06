/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScenaryFlood.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:17:55 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 13:05:53 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENARYFLOOD_CLASS_HPP
# define SCENARYFLOOD_CLASS_HPP

# include "AScenary.class.hpp"

class	AScenaryFlood: public virtual AScenary
{
	public:
		//Function
		//	Constructor
		AScenaryFlood(float **, unsigned int, unsigned int);

		//	Destructor
		virtual ~AScenaryFlood(void);

		//	SCenario
		void	Flood(void);

	private:
		//Function
		//	Constructor
		AScenaryFlood(void);

		//	Copy
		AScenaryFlood(const AScenaryFlood &);
		AScenaryFlood	&operator=(const AScenaryFlood &);
};

#endif
