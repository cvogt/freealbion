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
 
#ifndef __AR_ALBION_UI_H__
#define __AR_ALBION_UI_H__

#include "global.h"
#include "map_handler.h"

/*! @class agui
 *  @brief albion gui
 *  @author flo
 *  
 *  albion gui
 */

class albion_ui {
public:
	albion_ui(map_handler* mh);
	~albion_ui();

	void open_goto_map_wnd();

protected:
	map_handler* mh;

	//
	a2eui_window* albion_dbg;
	gui_button* b_goto_map;
	gui_input* i_goto_map;
	
	//
	void handle_b_goto_map_button(event::GUI_EVENT_TYPE type, GUI_ID id);
	void handle_i_goto_map_selected(event::GUI_EVENT_TYPE type, GUI_ID id);

};

#endif