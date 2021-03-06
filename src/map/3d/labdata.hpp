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

#ifndef __AR_LABDATA_HPP__
#define __AR_LABDATA_HPP__

#include "ar_global.hpp"
#include "map/map_defines.hpp"
#include "gfx/palette.hpp"
#include "gfx/gfxconv.hpp"
#include "gfx/scaling.hpp"
#include "conf.hpp"
#include "gfx/albion_texture.hpp"

class a2ematerial;

enum class object_light_type;
class labdata {
public:
	labdata();
	~labdata();
	
	void load(const size_t& labdata_num, const size_t& palette);
	void unload();
	
	enum AUTOGFX_TYPE {
		AGT_UNKNOWN,
		AGT_NORMAL,
		AGT_RIDDLE_MOUTH,
		AGT_TELEPORTER,
		AGT_SPINNER,
		AGT_TRAP,
		AGT_TRAP_DOOR,
		AGT_SPECIAL,
		AGT_MONSTER,
		AGT_CLOSED_DOOR,
		AGT_OPENED_DOOR,
		AGT_MERCHANT,
		AGT_TAVERN,
		AGT_CLOSED_CHEST,
		AGT_MAP_EXIT,
		AGT_OPENED_CHEST,
		AGT_TRASH_HEAP,
		AGT_NPC,
		AGT_GOTO_POINT,
		AGT_EVENT
	};

	enum WALL_TYPE {
		WT_WRITE_OVERLAY_ZERO = 0x04,
		WT_CUT_ALPHA = 0x20,
		WT_TRANSPARENT = 0x40,
		WT_JOINED = WT_WRITE_OVERLAY_ZERO|WT_CUT_ALPHA|WT_TRANSPARENT,
	};

	enum COLLISION_TYPE {
		CT_PASSABLE = 0x00,
		CT__UNKNOWN1__ = 0x02,
		CT_BLOCK = 0x08,
		CT__UNKNOWN2__ = 0x10, // possible "whole tile" <-> "part of tile" distinction (walls <-> objects)?
		CT_PASSABLE_EVENT = 0x80,
	};

	struct lab_info {
		size_t scale_1;
		size_t scale_2;
		size_t background;
		size_t camera_height;
		size_t camera_target_height;
		size_t fog_distance;
		size_t max_light_strength;
		size_t max_visible_tiles;
		size_t lighting;
	};
	
	struct lab_floor {
		COLLISION_TYPE collision = CT_PASSABLE;
		unsigned int _unknown_collision; // 2 bytes
		unsigned int tex_num { 0 };
		unsigned int animation { 1 };
		unsigned int cur_ani { 0 };
		albion_texture::albion_texture_multi_xld* tex_info { nullptr };
	};
	
	struct lab_object_info {
		unsigned char type;
		COLLISION_TYPE collision;
		unsigned int _unknown_collision; // 2 bytes
		unsigned int texture;
		unsigned int animation;
		unsigned int x_size;
		unsigned int y_size;
		unsigned int x_scale;
		unsigned int y_scale;

		unsigned int palette_shift { 0 };
		unsigned int cur_ani { 0 };
		float2* tex_coord_begin;
		float2* tex_coord_end;
	};
	
	struct lab_object {
		AUTOGFX_TYPE type;

		bool animated { false };
		size_t sub_object_count;
		ssize3 offset[8];
		size_t object_num[8];
		lab_object_info* sub_objects[8] {
			nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr, nullptr
		};
	};
	
	struct lab_wall_overlay {
		unsigned int animation;
		bool write_zero;
		unsigned int texture;
		unsigned int x_size;
		unsigned int y_size;
		unsigned int x_offset;
		unsigned int y_offset;
	};
	
	struct lab_wall {
		unsigned int type;
		COLLISION_TYPE collision;
		unsigned int _unknown_collision; // 2 bytes
		AUTOGFX_TYPE autogfx_type;
		unsigned int texture;
		unsigned int animation;
		unsigned int wall_animation;
		unsigned int palette_num; //?
		unsigned int x_size;
		unsigned int y_size;
		unsigned int overlay_count;
		vector<lab_wall_overlay> overlays;
		
		unsigned int cur_ani { 0 };
		float2* tex_coord_begin;
		float2* tex_coord_end;
	};
	
	const lab_info* get_lab_info() const { return &info; }
	const lab_object* get_object(const size_t& num) const;
	const lab_floor* get_floor(const size_t& num) const;
	const lab_wall* get_wall(const size_t& num) const;
	a2ematerial* get_fc_material() const;
	a2ematerial* get_wall_material() const;
	a2ematerial* get_object_material() const;
	
	typedef map<unsigned int, object_light_type> light_info_container;
	const map<unsigned int, light_info_container*>& get_light_objects() const;

	void handle_animations();
	
protected:
	vector<lab_object> objects;
	vector<lab_object_info> object_infos;
	
	vector<lab_floor> floors;
	vector<lab_wall> walls;

	lab_info info;

	array<lazy_xld, 3> labdata_xlds;
	size_t cur_labdata_num { ~0u };
	
	a2e_texture floors_tex;
	a2e_texture walls_tex;
	a2e_texture objects_tex;
	a2ematerial* lab_fc_material { nullptr };
	a2ematerial* lab_wall_material { nullptr };
	a2ematerial* lab_obj_material { nullptr };
	
	// 3d textures
	array<lazy_xld, 3> floor_xlds;
	array<lazy_xld, 4> object_xlds;
	array<lazy_xld, 3> overlay_xlds;
	array<lazy_xld, 2> wall_xlds;
	
	TEXTURE_FILTERING tex_filtering;
	TEXTURE_FILTERING custom_tex_filtering;
	
	// light object numbers for each labdata
	map<unsigned int, light_info_container*> light_objects;
	vector<light_info_container*> light_sets;
	
};

#endif
