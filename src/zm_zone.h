//
// ZoneMinder Zone Class Interfaces, $Date$, $Revision$
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

#ifndef ZM_ZONE_H
#define ZM_ZONE_H

#include "zm_rgb.h"
#include "zm_coord.h"
#include "zm_box.h"
#include "zm_image.h"
#include "zm_event.h"

class Monitor;

//
// This describes a 'zone', or an area of an image that has certain
// detection characteristics.
//
class Zone
{
public:
	typedef enum { ACTIVE=1, INCLUSIVE, EXCLUSIVE, INACTIVE } ZoneType;

protected:
	// Inputs
	Monitor			*monitor;

	int				id;
	char			*label;
	ZoneType		type;
	Box				limits;
	Rgb				alarm_rgb;

	int				alarm_threshold;
	int				min_alarm_pixels;
	int				max_alarm_pixels;

	Coord			filter_box;
	int				min_filter_pixels;
	int				max_filter_pixels;

	int				min_blob_pixels;
	int				max_blob_pixels;
	int				min_blobs;
	int				max_blobs;

	// Outputs/Statistics
	bool			alarmed;
	int				alarm_pixels;
	int				alarm_filter_pixels;
	int				alarm_blob_pixels;
	int				alarm_blobs;
	int				min_blob_size;
	int				max_blob_size;
	Box				alarm_box;
	unsigned int	score;
	Image			*image;

protected:
	void Setup( Monitor *p_monitor, int p_id, const char *p_label, ZoneType p_type, const Box &p_limits, const Rgb p_alarm_rgb, int p_alarm_threshold, int p_min_alarm_pixels, int p_max_alarm_pixels, const Coord &p_filter_box, int p_min_filter_pixels, int p_max_filter_pixels, int p_min_blob_pixels, int p_max_blob_pixels, int p_min_blobs, int p_max_blobs );

public:
	Zone( Monitor *p_monitor, int p_id, const char *p_label, ZoneType p_type, const Box &p_limits, const Rgb p_alarm_rgb, int p_alarm_threshold=15, int p_min_alarm_pixels=50, int p_max_alarm_pixels=75000, const Coord &p_filter_box=Coord( 3, 3 ), int p_min_filter_pixels=50, int p_max_filter_pixels=50000, int p_min_blob_pixels=10, int p_max_blob_pixels=0, int p_min_blobs=0, int p_max_blobs=0 )
	{
		Setup( p_monitor, p_id, p_label, p_type, p_limits, p_alarm_rgb, p_alarm_threshold, p_min_alarm_pixels, p_max_alarm_pixels, p_filter_box, p_min_filter_pixels, p_max_filter_pixels, p_min_blob_pixels, p_max_blob_pixels, p_min_blobs, p_max_blobs );
	}
	Zone( Monitor *p_monitor, int p_id, const char *p_label, const Box &p_limits, const Rgb p_alarm_rgb, int p_alarm_threshold=15, int p_min_alarm_pixels=50, int p_max_alarm_pixels=75000, const Coord &p_filter_box=Coord( 3, 3 ), int p_min_filter_pixels=50, int p_max_filter_pixels=50000, int p_min_blob_pixels=10, int p_max_blob_pixels=0, int p_min_blobs=0, int p_max_blobs=0 )
	{
		Setup( p_monitor, p_id, p_label, Zone::ACTIVE, p_limits, p_alarm_rgb, p_alarm_threshold, p_min_alarm_pixels, p_max_alarm_pixels, p_filter_box, p_min_filter_pixels, p_max_filter_pixels, p_min_blob_pixels, p_max_blob_pixels, p_min_blobs, p_max_blobs );
	}
	Zone( Monitor *p_monitor, int p_id, const char *p_label, const Box &p_limits )
	{
		Setup( p_monitor, p_id, p_label, Zone::INACTIVE, p_limits, RGB_BLACK, 0, 0, 0, Coord( 0, 0 ), 0, 0, 0, 0, 0, 0 );
	}

public:
	~Zone();

	inline const char *Label() const { return( label ); }
	inline ZoneType Type() const { return( type ); }
	inline bool IsActive() const { return( type == ACTIVE ); }
	inline bool IsInclusive() const { return( type == INCLUSIVE ); }
	inline bool IsExclusive() const { return( type == EXCLUSIVE ); }
	inline bool IsInactive() const { return( type == INACTIVE ); }
	inline Image &AlarmImage() const { return( *image ); }
	inline const Box &Limits() const { return( limits ); }
	inline bool Alarmed() const { return( alarmed ); }
	inline void SetAlarm() { alarmed = true; }
	inline void ClearAlarm() { alarmed = false; }
	inline unsigned int Score() const { return( score ); }

	inline void ResetStats()
	{
		alarmed = false;
		alarm_pixels = 0;
		alarm_filter_pixels = 0;
		alarm_blob_pixels = 0;
		alarm_blobs = 0;
		min_blob_size = 0;
		max_blob_size = 0;
		score = 0;
	}
	void RecordStats( const Event *event );
	bool CheckAlarms( const Image *delta_image );
	bool DumpSettings( char *output, bool verbose );

	static int Load( Monitor *monitor, Zone **&zones );
};

#endif // ZM_ZONE_H