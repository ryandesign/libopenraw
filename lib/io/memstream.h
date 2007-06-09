/*
 * libopenraw - memstream.h
 *
 * Copyright (C) 2007 Hubert Figuière
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef __IO_MEMSTREAM_H__
#define __IO_MEMSTREAM_H__


#include "io/stream.h"

namespace OpenRaw {
	namespace IO {
		
		class MemStream
			: public Stream
		{
		public:
			MemStream(void *ptr, size_t s);

			virtual ~MemStream()
				{}

			virtual or_error open();
			virtual int close();
			virtual int seek(off_t offset, int whence);
			virtual int read(void *buf, size_t count);
			virtual off_t filesize();


	private:
			void * m_ptr;
			size_t m_size;
			unsigned char * m_current;
		};

	}
}

#endif
