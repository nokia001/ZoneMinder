//
// ZoneMinder Camera Class Interface, $Date$, $Revision$
// Copyright (C) 2003  Philip Coombes
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 

#ifndef ZM_CAMERA_H
#define ZM_CAMERA_H

#include "zm_image.h"

//
// Abstract base class for cameras. This is intended just to express
// common attributes
//
class Camera
{
protected:
	typedef enum { LOCAL, REMOTE } SourceType;

	SourceType		type;
	unsigned int	width;
	unsigned int	height;
	unsigned int	colours;
	bool			capture;

public:
	Camera( SourceType p_type, int p_width, int p_height, int p_colours, bool p_capture=true );
	~Camera();

	SourceType Type() const { return( type ); }
	bool IsLocal() const { return( type == LOCAL ); }
	bool IsRemote() const { return( type == REMOTE ); }
	unsigned int Width() const { return( width ); }
	unsigned int Height() const { return( height ); }
	unsigned int Colours() const { return( colours ); }
	unsigned int ImageSize() const { return( colours*width*height ); }

	virtual int PreCapture()=0;
	virtual unsigned char *PostCapture()=0;
	virtual int PostCapture( Image &image )=0;

	inline unsigned char *Capture()
	{
		PreCapture();
		return( PostCapture() );
	}
	inline int Capture( Image &image )
	{
		PreCapture();
		return( PostCapture( image ) );
	}
};

#endif // ZM_CAMERA_H