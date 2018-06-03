# This file is part of xitool.
# Copyright 2018 Andy Pieters
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>. 
bin_PROGRAMS=xitool

xitool_SOURCES=xitool.c xitool.h error.c error.h resources.h resources.c modules.h modules.c versionhelp.c versionhelp.h xiversion.h xiversion.c list.c list.h colours.h colours.c table.h table.c state.h state.c props.h props.c

AM_CFLAGS=$(XINPUT_CFLAGS)

xitool_LDADD=$(XINPUT_LIBS)
