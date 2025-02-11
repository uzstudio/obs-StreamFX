// FFMPEG Video Encoder Integration for OBS Studio
// Copyright (c) 2019 Michael Fabian Dirks <info@xaymar.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include "common.hpp"

#include "warning-disable.hpp"
#include <utility>
#include "warning-enable.hpp"

extern "C" {
#include "warning-disable.hpp"
#include <libavutil/pixfmt.h>
#include <libswscale/swscale.h>
#include "warning-enable.hpp"
}

namespace streamfx::ffmpeg {
	class swscale {
		std::pair<uint32_t, uint32_t> source_size;
		AVPixelFormat                 source_format     = AV_PIX_FMT_NONE;
		bool                          source_full_range = false;
		AVColorSpace                  source_colorspace = AVCOL_SPC_UNSPECIFIED;

		std::pair<uint32_t, uint32_t> target_size;
		AVPixelFormat                 target_format     = AV_PIX_FMT_NONE;
		bool                          target_full_range = false;
		AVColorSpace                  target_colorspace = AVCOL_SPC_UNSPECIFIED;

		SwsContext* context = nullptr;

		public:
		swscale();
		~swscale();

		void                          set_source_size(uint32_t width, uint32_t height);
		void                          get_source_size(uint32_t& width, uint32_t& height);
		std::pair<uint32_t, uint32_t> get_source_size();
		uint32_t                      get_source_width();
		uint32_t                      get_source_height();
		void                          set_source_format(AVPixelFormat format);
		AVPixelFormat                 get_source_format();
		void                          set_source_color(bool full_range, AVColorSpace space);
		void                          set_source_colorspace(AVColorSpace space);
		AVColorSpace                  get_source_colorspace();
		void                          set_source_full_range(bool full_range);
		bool                          is_source_full_range();

		void                          set_target_size(uint32_t width, uint32_t height);
		void                          get_target_size(uint32_t& width, uint32_t& height);
		std::pair<uint32_t, uint32_t> get_target_size();
		uint32_t                      get_target_width();
		uint32_t                      get_target_height();
		void                          set_target_format(AVPixelFormat format);
		AVPixelFormat                 get_target_format();
		void                          set_target_color(bool full_range, AVColorSpace space);
		void                          set_target_colorspace(AVColorSpace space);
		AVColorSpace                  get_target_colorspace();
		void                          set_target_full_range(bool full_range);
		bool                          is_target_full_range();

		bool initialize(int flags);
		bool finalize();

		int32_t convert(const uint8_t* const source_data[], const int source_stride[], int32_t source_row,
						int32_t source_rows, uint8_t* const target_data[], const int target_stride[]);
	};
} // namespace streamfx::ffmpeg
