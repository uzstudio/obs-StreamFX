/*
 * Modern effects for a modern Streamer
 * Copyright (C) 2017 Michael Fabian Dirks
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "gs-sampler.hpp"

#include "warning-disable.hpp"
#include <stdexcept>
#include "warning-enable.hpp"

streamfx::obs::gs::sampler::sampler()
{
	_dirty         = true;
	_sampler_info  = {GS_FILTER_LINEAR, GS_ADDRESS_WRAP, GS_ADDRESS_WRAP, GS_ADDRESS_WRAP, 1, 0};
	_sampler_state = nullptr;
}

streamfx::obs::gs::sampler::~sampler()
{
	if (_sampler_state)
		gs_samplerstate_destroy(_sampler_state);
}

void streamfx::obs::gs::sampler::set_filter(gs_sample_filter v)
{
	_dirty               = true;
	_sampler_info.filter = v;
}

gs_sample_filter streamfx::obs::gs::sampler::get_filter()
{
	return _sampler_info.filter;
}

void streamfx::obs::gs::sampler::set_address_mode_u(gs_address_mode v)
{
	_dirty                  = true;
	_sampler_info.address_u = v;
}

gs_address_mode streamfx::obs::gs::sampler::get_address_mode_u()
{
	return _sampler_info.address_u;
}

void streamfx::obs::gs::sampler::set_address_mode_v(gs_address_mode v)
{
	_dirty                  = true;
	_sampler_info.address_v = v;
}

gs_address_mode streamfx::obs::gs::sampler::get_address_mode_v()
{
	return _sampler_info.address_v;
}

void streamfx::obs::gs::sampler::set_address_mode_w(gs_address_mode v)
{
	_dirty                  = true;
	_sampler_info.address_w = v;
}

gs_address_mode streamfx::obs::gs::sampler::get_address_mode_w()
{
	return _sampler_info.address_w;
}

void streamfx::obs::gs::sampler::set_max_anisotropy(int32_t v)
{
	_dirty                       = true;
	_sampler_info.max_anisotropy = v;
}

int32_t streamfx::obs::gs::sampler::get_max_anisotropy()
{
	return _sampler_info.max_anisotropy;
}

void streamfx::obs::gs::sampler::set_border_color(uint32_t v)
{
	_dirty                     = true;
	_sampler_info.border_color = v;
}

void streamfx::obs::gs::sampler::set_border_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	_dirty                     = true;
	_sampler_info.border_color = (static_cast<uint32_t>(a) << 24) | (static_cast<uint32_t>(r) << 16)
								 | (static_cast<uint32_t>(g) << 8) | static_cast<uint32_t>(b);
}

uint32_t streamfx::obs::gs::sampler::get_border_color()
{
	return _sampler_info.border_color;
}

uint8_t streamfx::obs::gs::sampler::get_border_color(bool r, bool g, bool b, bool a)
{
	if (a)
		return (_sampler_info.border_color >> 24) & 0xFF;
	if (r)
		return (_sampler_info.border_color >> 16) & 0xFF;
	if (g)
		return (_sampler_info.border_color >> 8) & 0xFF;
	if (b)
		return _sampler_info.border_color & 0xFF;
	return 0;
}

gs_sampler_state* streamfx::obs::gs::sampler::refresh()
{
	gs_samplerstate_destroy(_sampler_state);
	_sampler_state = gs_samplerstate_create(&_sampler_info);
	_dirty         = false;
	return _sampler_state;
}

gs_sampler_state* streamfx::obs::gs::sampler::get_object()
{
	if (_dirty)
		return refresh();
	return _sampler_state;
}
