#############################################################################
# File: GHangtuxmm - configure.ac                                           #
#                                                                           #
# Author: Patricia Santana Cruz  <patriciasc@openismus.com>                 #
#                                                                           #
# Copyright (C) 2010 Openismus GmbH                                         #
#                                                                           #
# Version 0.1                                                               #
#                                                                           #
# GHangtuxmm is free software; you can redistribute it and/or modify        #
# it under the terms of the GNU General Public License as published         #
# by the Free Software Foundation; either version 3 of the License,         #
# or (at your option) any later version.                                    #
#                                                                           #
# GHangtuxmm is distributed in the hope that it will be useful,             #
# but WITHOUT ANY WARRANTY; without even the implied warranty of            #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             #
# GNU General Public License for more details.                              #
#                                                                           #
# You should have received a copy of the GNU General Public License         #
# along with GHangtuxmm. If not, see <http://www.gnu.org/licenses/>.        #
#############################################################################

AC_PREREQ([2.59])
AC_INIT([ghangtuxmm], [0.1], [patriciasc@openismus.com], [ghangtuxmm], [http://openismus.com/])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.11 -Wall -Werror no-define subdir-objects])
AC_CONFIG_HEADERS([src/config.h])

AC_PROG_CXX
PKG_CHECK_MODULES([DEP], [gtk+-2.0 >= 2.20
                          gtkmm-2.4 >= 2.20
                          gio-2.0  >= 2.24 
                          glib-2.0 >= 2.24 
                          glibmm-2.4 >= 2.24
                          pangomm-1.4 >= 2.26
                          gmodule-export-2.0])

AC_LANG([C++])
DK_ARG_ENABLE_WARNINGS([GHANGTUX_WARNING_FLAGS],
                       [-Wall -w1],
                       [-pedantic -Wall -Wextra -w1],
                       [GTK GTKMM GDK GDKMM GDK_PIXBUF G GLIBMM PANGOMM])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
