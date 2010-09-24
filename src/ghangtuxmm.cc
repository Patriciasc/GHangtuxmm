/*
 * ########################################################################
 * # File: GHangtuxmm - ghangtuxmm.cc                                     #
 * #                                                                      #
 * # Author: Patricia Santana Cruz  <patriciasc@openismus.com>            #
 * #                                                                      #
 * # Copyright (C) 2010 Openismus GmbH                                    #
 * #                                                                      #
 * # Version: 0.1                                                         #
 * #                                                                      #
 * # Description: A variation of the Hangman game.                        #
 * #                                                                      #
 * # GHangtuxmm is free software; you can redistribute it and/or modify   #
 * # it under the terms of the GNU General Public License as published by #
 * # the Free Software Foundation; either version 3 of the License,       #
 * # or (at your option) any later version.                               #
 * #                                                                      #
 * # GHangtuxmm is distributed in the hope that it will be useful,        #
 * # but WITHOUT ANY WARRANTY; without even the implied warranty of       #
 * # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    #
 * # General Public License for more details.                             #
 * #                                                                      #
 * # You should have received a copy of the GNU General Public License    #
 * # along with GHangtuxmm. If not, see <http://www.gnu.org/licenses/>.   #
 * ########################################################################
 */

#include "ghangtuxmm.h"
#include <gtkmm.h>
#include <iostream>

GHangtuxApp::GHangtuxApp()
:image(0)
{
    //Builder
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create(); 

    try
    {
        builder->add_from_file("ghangtux.glade");
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }

    //FIX THIS: I am using the window I am inheriting from
    //and not the glade file window!

    //Hangtux image area
    builder->get_widget("hangtux_area", image);
    image->set("Tux0.png");
    image->show();
}

GHangtuxApp::~GHangtuxApp()
{
}
