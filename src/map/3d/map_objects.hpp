/*
 *  Albion Remake
 *  Copyright (C) 2007 - 2015 Florian Ziesche
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

#ifndef __AR_MAP_OBJECTS_HPP__
#define __AR_MAP_OBJECTS_HPP__

#include "ar_global.hpp"
#include "conf.hpp"
#include "map/map_defines.hpp"
#include "map/3d/map_tiles.hpp"

class map_objects : public map_tiles {
public:
	map_objects();
	virtual ~map_objects();
	
	void set_ws_positions(float3* ws_positions, GLenum usage = GL_STATIC_DRAW);
	const GLuint& get_vbo_ws_position_id() { return vbo_ws_position_id; }

protected:
	float3* ws_positions;
	GLuint vbo_ws_position_id;
	
	virtual const string select_shader(const DRAW_MODE& draw_mode) const;
	virtual void pre_draw_geometry(gl_shader& shd, VERTEX_ATTRIBUTE& attr_array_mask, a2ematerial::TEXTURE_TYPE& texture_mask);
	virtual void pre_draw_material(gl_shader& shd, VERTEX_ATTRIBUTE& attr_array_mask, a2ematerial::TEXTURE_TYPE& texture_mask);

};

#endif
