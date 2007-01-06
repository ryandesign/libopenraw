/*
 * libopenraw - endiantutils.h
 *
 * Copyright (C) 2006 Hubert Figuiere
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */





#ifndef __ENDIANUTILS_H_
#define __ENDIANUTILS_H_

#define EL16(b) \
  ((b)[0] | ((b)[1] << 8))

#define BE16(b) \
  ((b)[1] | ((b)[0] << 8))

#define EL32(b) \
  ((b)[0] | ((b)[1] << 8) | ((b)[2] << 16) | ((b)[3] << 24))

#define BE32(b) \
  ((b)[3] | ((b)[2] << 8) | ((b)[1] << 16) | ((b)[0] << 24))


#endif
