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
 
#ifndef __AR_MAP2D_H__
#define __AR_MAP2D_H__

#include "global.h"
#include "conf.h"
#include "map_defines.h"
#include "xld.h"
#include "tileset.h"

/*! @class map2d
 *  @brief displays 2d maps
 *  @author flo
 *  
 *  opens and displays 2d maps
 */

class map2d {
public:
	map2d(tileset* tilesets);
	~map2d();

	void load(const size_t& map_num);
	void unload();
	bool is_2d_map(const size_t& map_num) const;
	
	void handle();
	void draw(bool type) const;

	//void add_npc(const size_t& id, const size_t& x, const size_t& y);
	//void move_npc(const size_t& id, const size_t& x, const size_t& y);


	void set_pos(const size_t& x, const size_t& y);
	const size2& get_player_offset() const;
	const size2& get_size() const;
	const float get_tile_size() const;
	const size_t& get_palette() const;
	const float2& get_screen_position() const;

	bool collide(const MOVE_DIRECTION& direction, const size2& cur_position) const;

	// DEBUG: for debugging purposes
	tileset::tile_object* get_tile(unsigned int type);

protected:
	tileset* tilesets;

	xld* maps1;
	xld* maps2;
	xld* maps3;

	//
	size_t cur_map_num;
	size_t cur_tileset_num;
	size2 map_size;
	size_t map_palette;
	unsigned char* cur_map_data;
	unsigned int* underlay_tiles;
	unsigned int* overlay_tiles;
	
	// ogl buffers
	struct map_layer {
		GLuint vertices_vbo;
		GLuint tex_coords_vbo;
		GLuint indices_vbo;
		float2* vertices;
		float2* tex_coords;
		index4* indices;
		size_t index_count;
		
		void clear() {
			if(glIsBuffer(vertices_vbo)) glDeleteBuffers(1, &vertices_vbo);
			if(glIsBuffer(tex_coords_vbo)) glDeleteBuffers(1, &tex_coords_vbo);
			if(glIsBuffer(indices_vbo)) glDeleteBuffers(1, &indices_vbo);
			
			if(vertices != NULL) {
				delete [] vertices;
				vertices = NULL;
			}
			if(tex_coords != NULL) {
				delete [] tex_coords;
				tex_coords = NULL;
			}
			if(indices != NULL) {
				delete [] indices;
				indices = NULL;
			}
			index_count = 0;
		}
		
		map_layer() : vertices_vbo(0), tex_coords_vbo(0), indices_vbo(0), vertices(NULL), tex_coords(NULL), indices(NULL), index_count(0) {}
		~map_layer() { clear(); }
	};
	map_layer layers[2]; // under/overlay
	size_t* row_offsets;

	//
	ssize2 position;
	ssize2 next_position;
	float2 screen_position;
	
	size2 player_offset;
	size2 player_position;
	ssize2 normal_player_offset;

	bool map_loaded;

	vector<npc*> npcs;

};

#endif