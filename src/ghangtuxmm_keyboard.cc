/*
 * ########################################################################
 * # File: GHangtux - ghangtuxmm_keyboard.cc                              #
 * #                                                                      #
 * # Author: Patricia Santana Cruz  <patriciasc@openismus.com>            #
 * #                                                                      #
 * # Copyright (C) 2010 Openismus GmbH                                    #
 * #                                                                      #
 * # Description: A variation of the Hangman game.                        #
 * #                                                                      #
 * # GHangtuxmm is free software; you can redistribute it and/or modify   #
 * # it under the terms of the GNU General Public License as published by #
 * # the Free Software Foundation; either version 3 of the License,       #
 * # or (at your option) any later version.                               #
 * #                                                                      #
 * # GHangtuxmm  is distributed in the hope that it will be useful,       #
 * # but WITHOUT ANY WARRANTY; without even the implied warranty of       #
 * # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    #
 * # General Public License for more details.                             #
 * #                                                                      #
 * # You should have received a copy of the GNU General Public License    #
 * # along with GHangtuxmm. If not, see <http://www.gnu.org/licenses/>.   #
 * ########################################################################
 */

#include <gtkmm.h>
#include <glibmm.h>
#include <iostream>
#include "ghangtuxmm_keyboard.h"

GHangtuxmmKeyboard::GHangtuxmmKeyboard()
{
    static const int N_ROWS = 2;
    static const int N_COLS = 13;
    char ascii = 'A';

    resize(N_ROWS, N_COLS);
    set_homogeneous();

    for(int i=0; i<N_ROWS; ++i)
    {
        for(int j=0; j<N_COLS; ++j)
        {
            Gtk::Button *pButton = manage(new Gtk::Button(Glib::ustring(sizeof(ascii), ascii)));
            ascii++;
            pButton->set_use_underline();
            pButton->set_alignment(0.5, 0.5);
            attach(*pButton, j, j+1, i, i+1);
            pButton->signal_clicked().connect(sigc::bind<Gtk::Button*>(sigc::mem_fun(*this,
                                               &GHangtuxmmKeyboard::on_button_clicked), pButton));
        }
    }
    show_all_children();
}

GHangtuxmmKeyboard::~GHangtuxmmKeyboard()
{
}

void GHangtuxmmKeyboard::on_button_clicked(Gtk::Button* button)
{
    button->set_sensitive(false);

    //Emit signal for the Keyboard.
    m_sig_button_clicked.emit(button->get_label());
}

GHangtuxmmKeyboard::T_signal_clicked GHangtuxmmKeyboard::sig_button_clicked()
{
    return m_sig_button_clicked;
}

void GHangtuxmmKeyboard::set_all_buttons_sensitive(bool sensitive)
{
    set_sensitive(sensitive);
    foreach(
      sigc::bind(
        sigc::mem_fun(*this, &GHangtuxmmKeyboard::on_foreach_button_set_sensitive),
        sensitive));
}

void GHangtuxmmKeyboard::on_foreach_button_set_sensitive(Gtk::Widget& button, bool sensitive)
{
    button.set_sensitive(sensitive);
}
