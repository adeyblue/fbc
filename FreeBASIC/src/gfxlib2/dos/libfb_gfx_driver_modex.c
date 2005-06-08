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
 * vga.c -- Mode X gfx driver
 *
 * Mode X setting code derived from original Michael Abrash article in Dr. Dobb's Journal/Graphics Programming Black Book
 *
 * chng: apr/2005 written [DrV]
 *
 */

#include "fb_gfx_dos.h"

static int driver_init(char *title, int w, int h, int depth, int refresh_rate, int flags);
static void driver_update(void);

GFXDRIVER fb_gfxDriverModeX =
{
	"ModeX",		/* char *name; */
	driver_init,		/* int (*init)(char *title, int w, int h, int depth, int refresh_rate, int flags); */
	fb_dos_exit,		/* void (*exit)(void); */
	fb_dos_lock,		/* void (*lock)(void); */
	fb_dos_unlock,		/* void (*unlock)(void); */
	fb_dos_vga_set_palette,	/* void (*set_palette)(int index, int r, int g, int b); */
	fb_dos_vga_wait_vsync,	/* void (*wait_vsync)(void); */
	fb_dos_get_mouse,	/* int (*get_mouse)(int *x, int *y, int *z, int *buttons); */
	fb_dos_set_mouse,	/* void (*set_mouse)(int x, int y, int cursor); */
	fb_dos_set_window_title,/* void (*set_window_title)(char *title); */
	NULL			/* void (*flip)(void); */
};

#define SC_INDEX	0x3C4
#define CRTC_INDEX	0x3D4
#define MISC_OUTPUT	0x3C2

static unsigned short CRTParams[] = {	0x0D06,	/* vertical total */
					0x3E07,	/* overflow (bit 8 of vertical counts) */
					0x4109, /* cell height (2 to double scan) */
					0xEA10, /* v sync start */
					0xAC11, /* v sync end and protect cr0-cr7 */
					0xDF12, /* vertical displayed */
					0x0014, /* turn off dword mode */
					0xE715, /* v blank start */
					0x0616, /* v blank end */
					0xE317  /* turn on byte mode */

					};

#define CRT_PARM_LENGTH sizeof(CRTParams) / sizeof(short)


/*:::::*/
static int driver_init(char *title, int w, int h, int depth, int refresh_rate, int flags)
{
	int i;
	
	fb_dos_detect();
	
	if (flags & DRIVER_OPENGL)
		return -1;
	
	if ((w != 320) || (h != 240) || (depth != 8)) {
		return -1;
	}
	
	/* set base video mode */
	fb_dos.regs.x.ax = 0x13;
	__dpmi_int(0x10, &fb_dos.regs);
	
	/* tweak to Mode X */
	outportw(SC_INDEX, 0x0604);	/* disable chain4 */
	
	outportw(SC_INDEX, 0x0100);	/* synchronous reset */
	outportb(MISC_OUTPUT, 0xE3);	/* select 25 MHz dot clock & 60 Hz scanning rate */
	outportw(SC_INDEX, 0x0300);	/* undo reset (restart sequencer) */
	
	outportb(CRTC_INDEX, 0x11);	/* VSync End reg contains register write protect bit */
	outportb(CRTC_INDEX+1, inportb(CRTC_INDEX+1) & 0x7F);	/* remove write protect on various CRTC registers */
	
	for (i = 0; i < CRT_PARM_LENGTH; i++) {
		outportw(CRTC_INDEX, CRTParams[i]);
	}
	
	outportw(SC_INDEX, 0x0F02);	/* enable writes to all four planes */
	
	fb_dos.update = driver_update;
	
	fb_dos_init(title, w, h, depth, 60, flags);
	
	return 0;

}

/*:::::*/
static void driver_update(void)
{
	int plane;
	unsigned long screen;
	unsigned char *buffer;
	int x, y;
	
	fb_dos_update_mouse();
	
	fb_dos.draw_mouse();
	
	_farsetsel(_dos_ds);
	for (plane = 0; plane < 4; plane++) {
		buffer = (unsigned char *)fb_mode->framebuffer + plane;
		outportw(SC_INDEX, (0x100 << plane) | 0x02);		/* set write plane */
		screen = 0xA0000;
		for (y = 0; y < fb_dos.h; y++) {
			if (fb_mode->dirty[y]) {
				for (x = 0; x < fb_dos.w; x += 4, screen++) {
					_farnspokeb(screen, buffer[x]);
				}
			} else {
				screen += fb_dos.w / 4;
			}
			buffer += fb_dos.w;
		}
	}

	fb_hMemSet(fb_mode->dirty, FALSE, fb_dos.h);
	
	fb_dos.undraw_mouse();
}
