/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 18:55:47 by mmartin           #+#    #+#             */
/*   Updated: 2015/01/30 18:56:54 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_CLASS_HPP
# define DISPLAY_CLASS_HPP

class	Display
{
	public:
		Display(void);
		~Display(void);


	private:
		Display(const Display &);

		Display		&operator=(const Display &);
};

#endif
