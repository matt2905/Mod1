/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicalDisplay.class.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 19:33:30 by mmartin           #+#    #+#             */
/*   Updated: 2015/03/21 16:34:08 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICALDISPLAY_CLASS_HPP
# define GRAPHICALDISPLAY_CLASS_HPP

# include <list>
# include "Map.class.hpp"
# include "Water.class.hpp"
# include "map.h"

class	GraphicalDisplay
{
	public:
		GraphicalDisplay(unsigned int, unsigned int);
		~GraphicalDisplay(void);

		Map					*getMap(void) const;
		Water				*getWater(void) const;

		bool				setMap(std::list<t_map> &);
		bool				setWater(void);
		void				setBackground(void);

		bool				run();
		void				draw(float **);
		void				drawWater(float **);

	private:
		unsigned int	_width;
		unsigned int	_height;
		Map				*_map;
		Water			*_water;
//		Display			*_dis;
//		Window			_win;
//		XEvent			_report;
//		GC				_gc;

//		XImage			*_image;
//		char			*_data;
//		XImage			*_imageWater;
//		char			*_dataWater;
//		XImage			*_greyBG;
//		char			*_dataGrey;
//		XImage			*_whiteBG;
//		char			*_dataWhite;

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

		float				getColor(float, float, int *, int *, int *);

		void				expose(void);
//		bool				buttonEvent(XEvent);

};

typedef struct			s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_color;

#endif
