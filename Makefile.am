#############################################################################
# File: GHangtuxmm - Makefile.am                                            #
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
#                                                                           #
# This project does not use recursive make, but a single toplevel Makefile  #
# to build the entire tree (excluding the po subdirectory as gettext comes  #
# with its own build system).  Read Peter Miller's excellent paper to learn #
# why recursive make invocations are both slow and error-prone:             #
# http://www.cse.iitb.ac.in/~soumen/teach/cs699a1999/make.html              #
#############################################################################

# ===========================
# -- CONFIGURATION OPTIONS --
# ===========================
#
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

# =================
# -- TARGET LIST --
# =================

bin_PROGRAMS = ghangtuxmm
ghangtuxmm_SOURCES = src/ghangtuxmm.cc \
			   src/ghangtuxmm_app.h \
			   src/ghangtuxmm_app.cc \
			   src/ghangtuxmm_keyboard.h \
			   src/ghangtuxmm_keyboard.cc 

ghangtuxmm_CPPFLAGS = $(DEP_CFLAGS) -DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\" $(GHANGTUXMM_WARNING_FLAGS)
ghangtuxmm_LDADD = $(DEP_LIBS)

# ================
# -- FILE LISTS --
# ================

imagesdir = $(pkgdatadir)/images
dist_images_DATA = data/images/Tux0.png \
				   data/images/Tux1.png \
				   data/images/Tux2.png \
				   data/images/Tux3.png \
				   data/images/Tux4.png \
				   data/images/Tux5.png \
				   data/images/Tux6.png \
				   data/images/Tux7.png \
				   data/images/Tux8.png

iconsdir = $(pkgdatadir)/icons/hicolor
appicon48dir = $(iconsdir)/48x48/apps
dist_appicon48_DATA = data/icons/48x48/ghangtuxmm.png
appicon200dir = $(iconsdir)/200x200/apps
dist_appicon200_DATA = data/icons/200x200/ghangtuxmm.png

themesdir = $(pkgdatadir)/themes
dist_themes_DATA = data/themes/THEME_FILMS.txt \
				   data/themes/THEME_PERSONS.txt \
				   data/themes/THEME_OBJECTS.txt

uidir = $(pkgdatadir)/ui
dist_ui_DATA = data/ui/ghangtuxmm.glade

desktopdir = $(datadir)/applications
desktop_in_files = ghangtuxmm.desktop
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
	@INTLTOOL_DESKTOP_RULE@

INTLTOOL_FILES = intltool-extract.in \
				 intltool-merge.in \
				 intltool-update.in

DISTCLEANFILES = intltool-extract \
				 intltool-merge \
				 intltool-update \
				 po./intltool-merge-cache

dist_noinst_DATA = $(desktop_in_files)
dist_noinst_SCRIPTS = autogen.sh \
					  $(INTLTOOL_FILES)

SUBDIRS = po
