/*
 *  libgfx2 - FreeBASIC's alternative gfx library
 *	Copyright (C) 2005 Angelo Mottola (a.mottola@libero.it)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
 * palette.c -- palette management
 *
 * chng: jan/2005 written [lillo]
 *
 */

#include "fb_gfx.h"

const unsigned char fb_cga_palette[12][3] = {
 {   0,   0,   0 }, {  84, 252, 252 }, { 252,  84, 252 }, { 252, 252, 252 },	/* Mode 1, default palette */
 {  42, 126,  42 }, { 126,  42,  42 }, { 126, 126,  42 },			/* Mode 1, palette 0 */
 {  42, 126, 126 }, { 126,  42, 126 }, { 126, 126, 126 },			/* Mode 1, palette 1 */
 {   0,   0,   0 }, { 255, 255, 255 }						/* Mode 2, default palette */
};

const unsigned char fb_ega_palette[80][3] = {
 {   0,   0,   0 }, {   0,   0,  42 }, {   0,  42,   0 }, {   0,  42,  42 }, {  42,   0,   0 }, {  42,   0,  42 }, {  42,  42,   0 }, {  42,  42,  42 },
 {   0,   0,  21 }, {   0,   0,  63 }, {   0,  42,  21 }, {   0,  42,  63 }, {  42,   0,  21 }, {  42,   0,  63 }, {  42,  42,  21 }, {  42,  42,  63 },
 {   0,  21,   0 }, {   0,  21,  42 }, {   0,  63,   0 }, {   0,  63,  42 }, {  42,  21,   0 }, {  42,  21,  42 }, {  42,  63,   0 }, {  42,  63,  42 },
 {   0,  21,  21 }, {   0,  21,  63 }, {   0,  63,  21 }, {   0,  63,  63 }, {  42,  21,  21 }, {  42,  21,  63 }, {  42,  63,  21 }, {  42,  63,  63 },
 {  21,   0,   0 }, {  21,   0,  42 }, {  21,  42,   0 }, {  21,  42,  42 }, {  63,   0,   0 }, {  63,   0,  42 }, {  63,  42,   0 }, {  63,  42,  42 },
 {  21,   0,  21 }, {  21,   0,  63 }, {  21,  42,  21 }, {  21,  42,  63 }, {  63,   0,  21 }, {  63,   0,  63 }, {  63,  42,  21 }, {  63,  42,  63 },
 {  21,  21,   0 }, {  21,  21,  42 }, {  21,  63,   0 }, {  21,  63,  42 }, {  63,  21,   0 }, {  63,  21,  42 }, {  63,  63,   0 }, {  63,  63,  42 },
 {  21,  21,  21 }, {  21,  21,  63 }, {  21,  63,  21 }, {  21,  63,  63 }, {  63,  21,  21 }, {  63,  21,  63 }, {  63,  63,  21 }, {  63,  63,  63 },
 {   0,   0,   0 }, {   0,   0, 170 }, {   0, 170,   0 }, {   0, 170, 170 }, { 170,   0,   0 }, { 170,   0, 170 }, { 170,  85,   0 }, { 170, 170, 170 },
 {  85,  85,  85 }, {  85,  85, 255 }, {  85, 255,  85 }, {  85, 255, 255 }, { 255,  85,  85 }, { 255,  85, 255 }, { 255, 255,  85 }, { 255, 255, 255 },
};

const unsigned char fb_vga_palette[256][3] = {
 {   0,   0,   0 }, {   0,   0, 170 }, {   0, 170,   0 }, {   0, 170, 170 }, { 170,   0,   0 }, { 170,   0, 170 }, { 170,  85,   0 }, { 170, 170, 170 },
 {  85,  85,  85 }, {  85,  85, 255 }, {  85, 255,  85 }, {  85, 255, 255 }, { 255,  85,  85 }, { 255,  85, 255 }, { 255, 255,  85 }, { 255, 255, 255 },
 {   0,   0,   0 }, {  20,  20,  20 }, {  32,  32,  32 }, {  44,  44,  44 }, {  56,  56,  56 }, {  68,  68,  68 }, {  80,  80,  80 }, {  97,  97,  97 },
 { 113, 113, 113 }, { 129, 129, 129 }, { 145, 145, 145 }, { 161, 161, 161 }, { 182, 182, 182 }, { 202, 202, 202 }, { 226, 226, 226 }, { 255, 255, 255 },
 {   0,   0, 255 }, {  64,   0, 255 }, { 125,   0, 255 }, { 190,   0, 255 }, { 255,   0, 255 }, { 255,   0, 190 }, { 255,   0, 125 }, { 255,   0,  64 },
 { 255,   0,   0 }, { 255,  64,   0 }, { 255, 125,   0 }, { 255, 190,   0 }, { 255, 255,   0 }, { 190, 255,   0 }, { 125, 255,   0 }, {  64, 255,   0 },
 {   0, 255,   0 }, {   0, 255,  64 }, {   0, 255, 125 }, {   0, 255, 190 }, {   0, 255, 255 }, {   0, 190, 255 }, {   0, 125, 255 }, {   0,  64, 255 },
 { 125, 125, 255 }, { 157, 125, 255 }, { 190, 125, 255 }, { 222, 125, 255 }, { 255, 125, 255 }, { 255, 125, 222 }, { 255, 125, 190 }, { 255, 125, 157 },
 { 255, 125, 125 }, { 255, 157, 125 }, { 255, 190, 125 }, { 255, 222, 125 }, { 255, 255, 125 }, { 222, 255, 125 }, { 190, 255, 125 }, { 157, 255, 125 },
 { 125, 255, 125 }, { 125, 255, 157 }, { 125, 255, 190 }, { 125, 255, 222 }, { 125, 255, 255 }, { 125, 222, 255 }, { 125, 190, 255 }, { 125, 157, 255 },
 { 182, 182, 255 }, { 198, 182, 255 }, { 218, 182, 255 }, { 234, 182, 255 }, { 255, 182, 255 }, { 255, 182, 234 }, { 255, 182, 218 }, { 255, 182, 198 },
 { 255, 182, 182 }, { 255, 198, 182 }, { 255, 218, 182 }, { 255, 234, 182 }, { 255, 255, 182 }, { 234, 255, 182 }, { 218, 255, 182 }, { 198, 255, 182 },
 { 182, 255, 182 }, { 182, 255, 198 }, { 182, 255, 218 }, { 182, 255, 234 }, { 182, 255, 255 }, { 182, 234, 255 }, { 182, 218, 255 }, { 182, 198, 255 },
 {   0,   0, 113 }, {  28,   0, 113 }, {  56,   0, 113 }, {  85,   0, 113 }, { 113,   0, 113 }, { 113,   0,  85 }, { 113,   0,  56 }, { 113,   0,  28 },
 { 113,   0,   0 }, { 113,  28,   0 }, { 113,  56,   0 }, { 113,  85,   0 }, { 113, 113,   0 }, {  85, 113,   0 }, {  56, 113,   0 }, {  28, 113,   0 },
 {   0, 113,   0 }, {   0, 113,  28 }, {   0, 113,  56 }, {   0, 113,  85 }, {   0, 113, 113 }, {   0,  85, 113 }, {   0,  56, 113 }, {   0,  28, 113 },
 {  56,  56, 113 }, {  68,  56, 113 }, {  85,  56, 113 }, {  97,  56, 113 }, { 113,  56, 113 }, { 113,  56,  97 }, { 113,  56,  85 }, { 113,  56,  68 },
 { 113,  56,  56 }, { 113,  68,  56 }, { 113,  85,  56 }, { 113,  97,  56 }, { 113, 113,  56 }, {  97, 113,  56 }, {  85, 113,  56 }, {  68, 113,  56 },
 {  56, 113,  56 }, {  56, 113,  68 }, {  56, 113,  85 }, {  56, 113,  97 }, {  56, 113, 113 }, {  56,  97, 113 }, {  56,  85, 113 }, {  56,  68, 113 },
 {  80,  80, 113 }, {  89,  80, 113 }, {  97,  80, 113 }, { 105,  80, 113 }, { 113,  80, 113 }, { 113,  80, 105 }, { 113,  80,  97 }, { 113,  80,  89 },
 { 113,  80,  80 }, { 113,  89,  80 }, { 113,  97,  80 }, { 113, 105,  80 }, { 113, 113,  80 }, { 105, 113,  80 }, {  97, 113,  80 }, {  89, 113,  80 },
 {  80, 113,  80 }, {  80, 113,  89 }, {  80, 113,  97 }, {  80, 113, 105 }, {  80, 113, 113 }, {  80, 105, 113 }, {  80,  97, 113 }, {  80,  89, 113 },
 {   0,   0,  64 }, {  16,   0,  64 }, {  32,   0,  64 }, {  48,   0,  64 }, {  64,   0,  64 }, {  64,   0,  48 }, {  64,   0,  32 }, {  64,   0,  16 },
 {  64,   0,   0 }, {  64,  16,   0 }, {  64,  32,   0 }, {  64,  48,   0 }, {  64,  64,   0 }, {  48,  64,   0 }, {  32,  64,   0 }, {  16,  64,   0 },
 {   0,  64,   0 }, {   0,  64,  16 }, {   0,  64,  32 }, {   0,  64,  48 }, {   0,  64,  64 }, {   0,  48,  64 }, {   0,  32,  64 }, {   0,  16,  64 },
 {  32,  32,  64 }, {  40,  32,  64 }, {  48,  32,  64 }, {  56,  32,  64 }, {  64,  32,  64 }, {  64,  32,  56 }, {  64,  32,  48 }, {  64,  32,  40 },
 {  64,  32,  32 }, {  64,  40,  32 }, {  64,  48,  32 }, {  64,  56,  32 }, {  64,  64,  32 }, {  56,  64,  32 }, {  48,  64,  32 }, {  40,  64,  32 },
 {  32,  64,  32 }, {  32,  64,  40 }, {  32,  64,  48 }, {  32,  64,  56 }, {  32,  64,  64 }, {  32,  56,  64 }, {  32,  48,  64 }, {  32,  40,  64 },
 {  44,  44,  64 }, {  48,  44,  64 }, {  52,  44,  64 }, {  60,  44,  64 }, {  64,  44,  64 }, {  64,  44,  60 }, {  64,  44,  52 }, {  64,  44,  48 },
 {  64,  44,  44 }, {  64,  48,  44 }, {  64,  52,  44 }, {  64,  60,  44 }, {  64,  64,  44 }, {  60,  64,  44 }, {  52,  64,  44 }, {  48,  64,  44 },
 {  44,  64,  44 }, {  44,  64,  48 }, {  44,  64,  52 }, {  44,  64,  60 }, {  44,  64,  64 }, {  44,  60,  64 }, {  44,  52,  64 }, {  44,  48,  64 },
 {   0,   0,   0 }, {   0,   0,   0 }, {   0,   0,   0 }, {   0,   0,   0 }, {   0,   0,   0 }, {   0,   0,   0 }, {   0,   0,   0 }, {   0,   0,   0 }
};


/*:::::*/
unsigned int fb_hMakeColor(int index, int r, int g, int b)
{
	unsigned int color;

	if (fb_mode->bpp == 2)
		color = (b >> 3) | ((g << 3) & 0x07E0) | ((r << 8) & 0xF800);
	else
		color = index;

	return color;
}


/*:::::*/
unsigned int fb_hFixColor(unsigned int color)
{
	return fb_hMakeColor(color, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF) & fb_mode->color_mask;
}


/*:::::*/
static void set_color(int index, unsigned int color)
{
	color = (color & 0x3F3F3F) << 2;

	fb_mode->palette[index] = color;
	fb_mode->driver->set_palette(index, color & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF);
}


/*:::::*/
FBCALL void fb_GfxPalette(int index, unsigned int color)
{
	int i, r, g, b;
	const unsigned char *palette;

	if ((!fb_mode) || (fb_mode->depth > 8))
		return;

	fb_mode->driver->lock();

	if (index < 0) {
		palette = fb_mode->default_palette;
		for (i = 0; i < (1 << fb_mode->depth); i++) {
			fb_mode->palette[i] = (unsigned int)palette[0] | ((unsigned int)palette[1] << 8) | ((unsigned int)palette[2] << 16);
			fb_mode->driver->set_palette(i, palette[0], palette[1], palette[2]);
			palette += 3;
		}
	}
	else if (index < 256) {
		if (fb_mode->default_palette == fb_ega_palette[64]) {
			color &= 0x3F;
			color = fb_ega_palette[color][0] | (fb_ega_palette[color][1] << 8) | (fb_ega_palette[color][2] << 16);
		}
		set_color(index, color);
	}

	fb_hMemSet(fb_mode->dirty, TRUE, fb_mode->h);

	fb_mode->driver->unlock();
}


/*:::::*/
FBCALL void fb_GfxPaletteUsing(int *data)
{
	int i;

	if ((!fb_mode) || (fb_mode->depth > 8))
		return;

	fb_mode->driver->lock();

	for (i = 0; i < (1 << fb_mode->depth); i++) {
		if (data[i] >= 0)
			set_color(i, data[i]);
	}

	fb_hMemSet(fb_mode->dirty, TRUE, fb_mode->h);

	fb_mode->driver->unlock();
}
