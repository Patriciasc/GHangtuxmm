/*
 * ########################################################################
 * # File: GHangtux - ghangtuxmm_keyboard.c                               #
 * #                                                                      #
 * # Author: Patricia Santana Cruz  <patriciasc@openismus.com>            #
 * #                                                                      #
 * # Copyright (C) 2010 Openismus GmbH                                    #
 * #                                                                      #
 * # Version: 0.1                                                         #
 * #                                                                      #
 * # Description: A variation of the Hangman game.                        #
 * #                                                                      #
 * # GHangtux is free software; you can redistribute it and/or modify     #
 * # it under the terms of the GNU General Public License as published by #
 * # the Free Software Foundation; either version 3 of the License,       #
 * # or (at your option) any later version.                               #
 * #                                                                      #
 * # GHangtux  is distributed in the hope that it will be useful,         #
 * # but WITHOUT ANY WARRANTY; without even the implied warranty of       #
 * # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    #
 * # General Public License for more details.                             #
 * #                                                                      #
 * # You should have received a copy of the GNU General Public License    #
 * # along with GHangtux. If not, see <http://www.gnu.org/licenses/>.     #
 * ########################################################################
 */

#include <gtkmm.h>
#include "ghangtuxmm_keyboard.h"

#define N_ROWS 2
#define N_COLS 13

// This function is still not working since
// the structure of the .h file will be
// changed in the near future
GHangtuxmmKeyboard::GHangtuxmmKeyboard()
{
    float align = 0.50;
    int ascii_int = 65; /* ascci A=65 */
    Glib::ustring ascii_char; 

    resize(N_ROWS, N_COLS);
    set_homogeneous(true);

    for(int i=0; i<N_ROWS; ++i)
    {
        for(int j=0; j<N_COLS; ++j)
        {
            ascii_char = Glib::ustring::compose("%1%%",ascii_int); 
            ascii_int++;

            m_button.set_label(ascii_char);
            m_button.set_use_underline();
            m_button.set_alignment(align, align);
            //m_button.signal_clicked()?

            attach(m_button, j, j+1, i, i+1);
            m_button.show();
        }
     }
}

GHangtuxmmKeyboard::~GHangtuxmmKeyboard()
{
}

static void set_key_insensitive()
{
}

void GHangtuxmmKeyboard::set_sensitive(bool sensitive)
{
}

void GHangtuxmmKeyboard::on_key_clicked(const Glib::ustring key_name)
{
}
