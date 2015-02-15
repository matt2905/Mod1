/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:33:30 by mmartin           #+#    #+#             */
/*   Updated: 2015/02/15 18:31:59 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICALDISPLAY_CLASS_HPP
# define GRAPHICALDISPLAY_CALL_HPP

# include <X11/Xlib.h>
# include <list>
# include "Map.class.hpp"
# include "map.h"

class	GraphicalDisplay
{
	public:
		GraphicalDisplay(unsigned int, unsigned int);
		~GraphicalDisplay(void);

		bool				setMap(std::list<t_map> &);

		void				run(void);
		void				draw(float **);
		void				setBackground(void);

		void				expose(GC gc);
		bool				buttonEvent(GC, XEvent);

	private:
		unsigned int	_width;
		unsigned int	_height;
		Map				*_map;
		Display			*_dis;
		Window			_win;
		XEvent			_report;
		XImage			*_image;
		char			*_data;
		XImage			*_greyBG;
		char			*_dataGrey;
		XImage			*_whiteBG;
		char			*_dataWhite;

		bool			rise;
		bool			south;
		bool			east;
		bool			north;
		bool			west;
		bool			rain;
		bool			evaporate;

		GraphicalDisplay(void);
		GraphicalDisplay(const GraphicalDisplay &);

		GraphicalDisplay	&operator=(const GraphicalDisplay &);

};

#endif
