/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/31 11:56:04 by mmartin           #+#    #+#             */
/*   Updated: 2015/01/31 11:59:07 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtkmm/window.h>

int		display(int &argc, char **&argv)
{
	argc = 1;
	Glib::RefPtr<Gtk::Application>	app = Gtk::Application::create(argc, argv, "Mod 1");
	Gtk::Window						win;

/*	MyArea		area;
	win.add(area);
	area.show();
*/
	return (app->run(win));
}
