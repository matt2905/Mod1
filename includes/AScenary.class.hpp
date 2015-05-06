/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AScenary.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:17:55 by tbalea            #+#    #+#             */
/*   Updated: 2015/03/26 13:05:53 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASCENARY_CLASS_HPP
# define ASCENARY_CLASS_HPP

# include "mod1.h"

class	AScenary
{
	public:
		//Function
		//	Constructor
		AScenary(float **, unsigned int, unsigned int);

		//	Destructor
		virtual ~AScenary(void);

		//	Setter
		//		No setter

		//	Getter
		t_water			**getCurMap(void) const;

		//	Clear
		virtual void	ClearCurMap(void) = 0;

		//	Flowing
		virtual void	Flow(void) = 0;

	protected:
		//Attribute
		//	Map Data
		bool			_w;
		bool			_s;
		bool			_e;
		bool			_n;
		float			**_Map;
		unsigned int	_sizeX;
		unsigned int	_sizeY;
		t_water			**_CurMap;

	private:
		//Function
		//	Constructor
		AScenary(void);

		//	Copy
		AScenary(const AScenary &);
		AScenary	&operator=(const AScenary &);
};

#endif
