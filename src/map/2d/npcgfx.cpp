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

#include "npcgfx.h"

/*! npcgfx constructor
 */
npcgfx::npcgfx(const pal* palettes) : palettes(palettes), cur_palette(6) {
	tsize.x = 32.0f/128.0f;
	tsize.y = 48.0f/256.0f;

	// load npc graphics
	npcgfx0 = new xld("NPCGR0.XLD");
	npcgfx1 = new xld("NPCGR1.XLD");
	npcgfx2 = new xld("PARTGR0.XLD");
	npcgfx3 = new xld("TACTICO0.XLD");
}

/*! npcgfx destructor
 */
npcgfx::~npcgfx() {
	clear();
	delete npcgfx0;
	delete npcgfx1;
	delete npcgfx2;
	delete npcgfx3;
}

void npcgfx::load_npcgfx(const size_t& npc_num) {
	const xld::xld_object* object = NULL;
	if(npc_num < 100 && npc_num < npcgfx0->get_object_count()) {
		object = npcgfx0->get_object(npc_num);
	}
	else if(npc_num < 200 && (npc_num - 100) < npcgfx1->get_object_count()) {
		object = npcgfx1->get_object(npc_num - 100);
	}
	else if(npc_num < 300 && (npc_num - 200) < npcgfx2->get_object_count()) {
		object = npcgfx2->get_object(npc_num - 200);
	}
	else if(npc_num < 400 && (npc_num - 300) < npcgfx3->get_object_count()) {
		object = npcgfx3->get_object(npc_num - 300);
	}
	else {
		return;
	}
	
	const size2 npc_size = size2(32, 48);
	const size_t object_count = object->length / (npc_size.x * npc_size.y);
	const size_t scale = 4;
	const size2 scaled_npc_size = npc_size * scale;
	const size2 surface_size = size2(512, 1024);
	const size_t offset = (object_count > 1 ? 6 : 0);
	
	unsigned int* surface = new unsigned int[surface_size.x*surface_size.y];
	memset(surface, 0, surface_size.x*surface_size.y*sizeof(unsigned int));
	
	unsigned int* data_32bpp = new unsigned int[npc_size.x*npc_size.y];
	unsigned int* scaled_data = new unsigned int[scaled_npc_size.x*scaled_npc_size.y];
	for(size_t i = 0; i < object_count; i++) {
		gfxconv::convert_8to32(&(object->data[offset + i*npc_size.x*npc_size.y]), data_32bpp, npc_size.x, npc_size.y, cur_palette);
		scaling::scale_4x(scaling::ST_NEAREST, data_32bpp, npc_size, scaled_data);
		//scaling::scale_4x(scaling::ST_HQ4X, data_32bpp, npc_size, scaled_data);

		// copy data into surface
		const size_t offset_x = (i%4) * scaled_npc_size.x;
		const size_t offset_y = (i/4) * scaled_npc_size.y;
		for(size_t y = 0; y < scaled_npc_size.y; y++) {
			memcpy(&surface[(offset_y + y) * surface_size.x + offset_x], &scaled_data[y*scaled_npc_size.x], scaled_npc_size.x*sizeof(unsigned int));
		}
	}
	delete [] scaled_data;
	delete [] data_32bpp;

	npc_graphics[npc_num] = t->add_texture(surface, surface_size.x, surface_size.y, GL_RGBA8, GL_RGBA, texture_object::TF_TRILINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_UNSIGNED_BYTE);

	delete [] surface;
}

const a2e_texture& npcgfx::get_npcgfx(const size_t& npc_num) {
	if(npc_num > 399) {
		a2e_error("invalid npc graphic #%u!", npc_num);
		//throw exception();
		return get_npcgfx(0);
	}
	
	if(npc_graphics.count(npc_num) == 0) {
		load_npcgfx(npc_num);
	}

	return npc_graphics.find(npc_num)->second;
}

void npcgfx::draw_npc(const size_t& npc_num, const size_t& frame, const float& x, const float& y) {
	const float scale = conf::get<float>("global.scale");
	draw_size.set(32.0f * scale, 48.0f * scale);
	size_t npc_frame = 0;
	switch(frame & 0xF7) {
		case S_BACK1: npc_frame = 0; break;
		case S_BACK2: npc_frame = 1; break;
		case S_BACK3: npc_frame = 2; break;
		case S_RIGHT1: npc_frame = 3; break;
		case S_RIGHT2: npc_frame = 4; break;
		case S_RIGHT3: npc_frame = 5; break;
		case S_FRONT1: npc_frame = 6; break;
		case S_FRONT2: npc_frame = 7; break;
		case S_FRONT3: npc_frame = 8; break;
		case S_LEFT1: npc_frame = 9; break;
		case S_LEFT2: npc_frame = 10; break;
		case S_LEFT3: npc_frame = 11; break;
		case S_SIT_BACK: npc_frame = 12; break;
		case S_SIT_RIGHT: npc_frame = 13; break;
		case S_SIT_FRONT: npc_frame = 14; break;
		case S_SIT_LEFT: npc_frame = 15; break;
		case S_LAY: npc_frame = 16; break;
		default: npc_frame = 17; break;
	}
	
	float ty = (float(npc_frame / 4) * 48.0f * 4.0f) / 1024.0f;
	float tx = (float(npc_frame % 4) * 32.0f * 4.0f) / 512.0f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, get_npcgfx(npc_num)->tex());
	glTranslatef(0.0f, 0.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_BLEND);

	glBegin(GL_QUADS);
		glTexCoord2f(tx, ty);
		glVertex2f(x, y);
		glTexCoord2f(tx, ty + tsize.y);
		glVertex2f(x, y + draw_size.y);
		glTexCoord2f(tx + tsize.x, ty + tsize.y);
		glVertex2f(x + draw_size.x, y + draw_size.y);
		glTexCoord2f(tx + tsize.x, ty);
		glVertex2f(x + draw_size.x, y);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void npcgfx::clear() {
	npc_graphics.clear();
}

void npcgfx::set_palette(const size_t& palette_num) {
	if(palette_num >= 56) {
		a2e_error("invalid palette #%u!", palette_num);
		return;
	}
	
	if(cur_palette != palette_num) clear();
	
	cur_palette = palette_num;
}