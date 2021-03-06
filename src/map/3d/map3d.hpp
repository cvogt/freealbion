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

#ifndef __AR_MAP3D_HPP__
#define __AR_MAP3D_HPP__

#include "ar_global.hpp"
#include "conf.hpp"
#include "map/map_defines.hpp"
#include "map/3d/labdata.hpp"
#include "map/map_npcs.hpp"
#include "map/map_events.hpp"
#include "map_objects.hpp"
#include "map/3d/map_tiles.hpp"
#include "map/3d/background3d.hpp"

class npc3d;
class object_light_base;

class map3d {
public:
	map3d(labdata* lab_data, array<lazy_xld, 3>& maps);
	~map3d();

	void load(const size_t& map_num);
	void unload();
	
	void handle();
	void draw() const;
	
	bool4 collide(const MOVE_DIRECTION& direction, const size2& cur_position, const CHARACTER_TYPE& char_type) const;
	
	map_events& get_map_events();
	
	labdata* get_active_lab_data() const;

	// DEBUG: for debugging purposes
	const ssize3 get_tile() const;
	
protected:
	labdata* lab_data;
	array<lazy_xld, 3>& map_xlds;

	background3d* bg3d;
	bool bg_loaded;
	
	// npcs data
	vector<npc3d*> npcs;
	map_npcs* mnpcs;
	map_events mevents;
	float3* npcs_vertices;
	float3* npcs_ws_positions;
	float2* npcs_tex_coords;
	uint3** npcs_indices;
	unsigned int npc_object_count;
	map_objects* npcs_model;
	
	unsigned int* ow_tiles;
	unsigned int* floor_tiles;
	unsigned int* ceiling_tiles;
	
	enum WALL_SIDE {
		WS_NORTH	= 1 << 0,
		WS_EAST		= 1 << 1,
		WS_SOUTH	= 1 << 2,
		WS_WEST		= 1 << 3,
	};
	unsigned char* wall_sides;

	// gl
	// floors/ceilings
	float3* fc_vertices;
	float2* fc_tex_coords;
	uint3** fc_indices;
	unsigned int fc_tile_count;
	map_tiles* fc_tiles_model;
	
	// walls
	float3* wall_vertices;
	float2* wall_tex_coords;
	uint3** wall_indices;
	unsigned int wall_tile_count;
	map_tiles* wall_model;

	// objects
	float3* obj_vertices;
	float3* obj_ws_positions;
	float2* obj_tex_coords;
	uint3** obj_indices;
	map_objects* objects_model;
	
	// lights
	object_light_base* player_light;
	light* sun_light;
	float sun_distance;
	bool active_sun_light;
	vector<float3> sun_color_table;
	vector<object_light_base*> object_lights;
	unsigned int object_light_ani_time;

	//
	bool map_loaded;
	size_t cur_map_num;
	size_t cur_labdata_num;
	size2 map_size;
	size_t map_palette;
	
	//
	unsigned int last_tile_animation;
	unsigned int fc_ani_count;
	unsigned int fc_ani_offset;
	unsigned int wall_ani_count;
	unsigned int wall_ani_offset;
	unsigned int obj_ani_count;
	unsigned int obj_ani_offset;
	// <type, tile number, pos> (type: 0 = floor/ceiling, 1 = wall, 2 = object)
	vector<tuple<unsigned int, unsigned int, uint2>> animated_tiles;
	
	//
	clock_callback clock_cb;
	void clock_tick(size_t ticks);

};

#endif
