/*
* Tilengine - The 2D retro graphics engine with raster effects
* Copyright (C) 2015-2018 Marc Palacios Domenech <mailto:megamarc@hotmail.com>
* All rights reserved
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.
*
* You should have received a copy of the GNU Library General Public
* License along with this library. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _ENGINE_H
#define _ENGINE_H

#include "Tilengine.h"
#include "Sprite.h"
#include "Layer.h"
#include "Animation.h"
#include "Bitmap.h"
#include "Blitters.h"

/* motor */
typedef struct Engine
{
	uint32_t	header;		/* object signature to identify as engine context */
	uint8_t*	priority;	/* scanline que recibe los tiles con prioridad */
	uint16_t*	collision;	/* scanline con IDs de colision de sprites */
	uint8_t*	tmpindex;	/* indices temporales para capas transformadas con transparencia */
	int			numsprites;	/* n� de sprites */
	Sprite*		sprites;	/* puntero a los sprites */
	int			numlayers;	/* n� de capas */
	Layer*		layers;		/* puntero a las capas */
	int			numanimations;
	Animation*	animations;
	bool		dopriority;
	TLN_Error	error;		/* ultimo error */
	TLN_LogLevel log_level;	/* logging level */

	uint32_t	bgcolor;	/* color de fondo */
	TLN_Bitmap	bgbitmap;	/* bitmap de fondo */
	TLN_Palette	bgpalette;	/* paleta de fondo */
	ScanBlitPtr	blit_fast;	/* blitter para bitmap de fondo */
	uint8_t*	mod_table;	/* tabla de modulacion */
	void		(*raster)(int);
	void		(*frame)(int);
	int line;				/* l�nea actual */

	struct
	{
		int		width;
		int		height;
		int		pitch;
		uint8_t*	data;
	}
	framebuffer;
}
Engine;

extern Engine* engine;

extern void tln_trace(TLN_LogLevel log_level, const char* format, ...);

#define GetFramebufferLine(line) \
	(engine->framebuffer.data + (line*engine->framebuffer.pitch))

#endif
