/*
 *  Albion Remake
 *  Copyright (C) 2007 - 2010 Florian Ziesche
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#ifndef __AR_MAIN_H__
#define __AR_MAIN_H__

#include "global.h"
#include "conf.h"

#include "albion_ui.h"
#include "xld.h"
#include "palette.h"
#include "tileset.h"
#include "npcgfx.h"
#include "player.h"
#include "scaling.h"

#include "map_handler.h"

image* img;
map_handler* mh;
albion_ui* aui;

bool done = false;

SDL_Event sevent;

stringstream caption;
stringstream tmp;

#endif