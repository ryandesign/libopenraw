/* -*- tab-width:4; c-basic-offset:4 -*- */
/*
 * libopenraw - rafcontainer.cpp
 *
 * Copyright (C) 2011-2016 Hubert Figuiere
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include <cstdint>
#include <string>
#include <utility>

#include "metavalue.hpp"
#include "rafmetacontainer.h"
#include "io/stream.h"

namespace OpenRaw {
namespace Internals {

RafMetaValue::RafMetaValue(uint16_t tag, uint16_t size, const MetaValue & v)
	: m_tag(tag)
	, m_size(size)
	, m_value(v)
{
}

RafMetaValue::~RafMetaValue()
{
}

RafMetaContainer::RafMetaContainer(const IO::Stream::Ptr &_file)
	: RawContainer(_file, 0)
	, m_count(0)
{
	setEndian(ENDIAN_BIG);
}

uint32_t RafMetaContainer::count()
{
	if(m_count == 0) {
		_read();
	}
	return m_count;
}

RafMetaValue::Ref RafMetaContainer::getValue(uint16_t tag)
{
	if(m_tags.empty()) {
		_read();
	}
	std::map<uint16_t, RafMetaValue::Ref>::const_iterator iter = m_tags.find(tag);
	if(iter != m_tags.end()) {
		return iter->second;
	}
	return RafMetaValue::Ref();
}

void RafMetaContainer::_read()
{
	readUInt32(m_file, m_count);
	for(uint32_t i = 0; i < m_count; i++) {
		uint16_t tag;
		uint16_t size;
		readUInt16(m_file, tag);
		readUInt16(m_file, size);
		MetaValue::value_t v;
		if(size == 4) {
			uint32_t intVal;
			if(readUInt32(m_file, intVal)) {
				v = MetaValue::value_t(intVal);
			}
		}
		else {
			char *content;
			content = (char*)calloc(1, size + 1);
			content[size] = 0;
			m_file->read(content, size);
			v = MetaValue::value_t(std::string(content));
			free(content);
		}

		RafMetaValue::Ref value(new RafMetaValue(tag, size, MetaValue(v)));
		m_tags.insert(std::make_pair(tag, value));

//		printf("RAF: tag %x of size %u\n", tag, size);
	}
}

}
}
