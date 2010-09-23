/*
 * ########################################################################
 * # File: GHangtuxmm - ghangtuxmm.h                                      #
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

#ifndef GHANGTUXMM_H__
#define GHANGTUXMM_H__

#include <gtkmm.h>
#include <glibmm.h>

/* Game widgets and control elements. */
class GHangtuxApp : public Gtk::Window
{
public:
    GHangtuxApp();
    ~GHangtuxApp();

private:
    Glib::RefPtr<Gtk::Builder> builder;  /* App Builder */
    Glib::ustring sentence;              /* Games's sentence */
    Glib::ustring display_sentence;      /* Displayed sentence */
    const gchar *valid_chars;            /* Player asserted characters */
    Gtk::Label display_label;            /* Label for display_sentence */
    Gtk::Label title_label;              /* Title label */
    Gtk::Image image;                    /* Displayed image */
    gint n_img;                          /* Current image number */
    //keyboard;      
    gint theme_id;                       /* Current theme's identifier */
    Gdk::Pixbuf *logo;                   /* Application's logo */
};

#endif /* GHANGTUXMM_H__ */
