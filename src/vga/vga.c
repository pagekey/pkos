#include "vga.h"
#include "../kernel/kernel.h"
#include "../screen/screen.h"

void vga_enter_text_mode() {
	write_regs(g_80x25_text);
}

void vga_test() {
    println("Attempting to switch modes...", 29);
    write_regs(g_320x200x256);
    vga_clear_screen();
	// draw some faces
	draw_happy_face(10,10);
	draw_happy_face(100,100);
	draw_happy_face(300,150);
	// bounds
	vga_plot_pixel(0, 0, 15);
	vga_plot_pixel(319, 199, 0xf);
	// see some colors
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 100; j++) {
			vga_plot_pixel(i, 50+j, i);
		}
	}
}

void draw_happy_face(int x, int y) {
	// eye
	vga_plot_pixel(x,y,0xf);
	// eye
	vga_plot_pixel(x+10,y,0xf);
	// mouth
	vga_plot_pixel(x,	y+8,0xf);
	vga_plot_pixel(x+1,	y+9,0xf);
	vga_plot_pixel(x+2,	y+10,0xf);
	vga_plot_pixel(x+3,	y+10,0xf);
	vga_plot_pixel(x+4,	y+10,0xf);
	vga_plot_pixel(x+5,	y+10,0xf);
	vga_plot_pixel(x+6,	y+10,0xf);
	vga_plot_pixel(x+7,	y+10,0xf);
	vga_plot_pixel(x+8,	y+10,0xf);
	vga_plot_pixel(x+9,	y+9,0xf);
	vga_plot_pixel(x+10,y+8,0xf);
}

void vga_clear_screen() {
    // Note: "clear_screen" name conflicted with something in screen.h
    // Now I see why namespacing is a thing
    for (int i = 0; i < 320; i++) {
        for (int j = 0; j < 200; j++) {
            vga_plot_pixel(i,j,0);
        }
    }
}

void vga_plot_pixel(int x, int y, unsigned short color) {
    unsigned short offset = x + 320 * y;
    unsigned char *VGA = (unsigned char*) VGA_ADDRESS; // TODO snippet has "far" keyword?? what is that
    VGA[offset] = color;
}

// Begin copied code
// Source: https://files.osdev.org/mirrors/geezer/osd/graphics/modes.c
// Changes:
// - Initial: only grabbed code I thought was relevant to changing mode and displaying our first pixel (`write_regs`)
// - Changed ioport_in, ioport_out funcs to instead point to ioport_in, ioport_out funcs defined in kernel.asm
// - Grabbed write_font and 80x25 text mode reg values so we can switch back from VGA to text
unsigned char g_320x200x256[] =
{
/* MISC */
	0x63,
/* SEQ */
	0x03, 0x01, 0x0F, 0x00, 0x0E,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
	0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x9C, 0x0E, 0x8F, 0x28,	0x40, 0x96, 0xB9, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	0x41, 0x00, 0x0F, 0x00,	0x00
};
unsigned char g_80x25_text[] =
{
/* MISC */
	0x67,
/* SEQ */
	0x03, 0x00, 0x03, 0x00, 0x02,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81, 0xBF, 0x1F,
	0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x50,
	0x9C, 0x0E, 0x8F, 0x28, 0x1F, 0x96, 0xB9, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00
};

void write_regs(unsigned char *regs)
{
	unsigned i;

/* write MISCELLANEOUS reg */
	ioport_out(VGA_MISC_WRITE, *regs);
	regs++;
/* write SEQUENCER regs */
	for(i = 0; i < VGA_NUM_SEQ_REGS; i++)
	{
		ioport_out(VGA_SEQ_INDEX, i);
		ioport_out(VGA_SEQ_DATA, *regs);
		regs++;
	}
/* unlock CRTC registers */
	ioport_out(VGA_CRTC_INDEX, 0x03);
	ioport_out(VGA_CRTC_DATA, ioport_in(VGA_CRTC_DATA) | 0x80);
	ioport_out(VGA_CRTC_INDEX, 0x11);
	ioport_out(VGA_CRTC_DATA, ioport_in(VGA_CRTC_DATA) & ~0x80);
/* make sure they remain unlocked */
	regs[0x03] |= 0x80;
	regs[0x11] &= ~0x80;
/* write CRTC regs */
	for(i = 0; i < VGA_NUM_CRTC_REGS; i++)
	{
		ioport_out(VGA_CRTC_INDEX, i);
		ioport_out(VGA_CRTC_DATA, *regs);
		regs++;
	}
/* write GRAPHICS CONTROLLER regs */
	for(i = 0; i < VGA_NUM_GC_REGS; i++)
	{
		ioport_out(VGA_GC_INDEX, i);
		ioport_out(VGA_GC_DATA, *regs);
		regs++;
	}
/* write ATTRIBUTE CONTROLLER regs */
	for(i = 0; i < VGA_NUM_AC_REGS; i++)
	{
		(void)ioport_in(VGA_INSTAT_READ);
		ioport_out(VGA_AC_INDEX, i);
		ioport_out(VGA_AC_WRITE, *regs);
		regs++;
	}
/* lock 16-color palette and unblank display */
	(void)ioport_in(VGA_INSTAT_READ);
	ioport_out(VGA_AC_INDEX, 0x20);
}
// #if defined(__TURBOC__)
#define	pokew(S,O,V)		poke(S,O,V)
#define	_vmemwr(DS,DO,S,N)	movedata(FP_SEG(S), FP_OFF(S), DS, DO, N)
// #endif
static unsigned get_fb_seg(void)
{
	unsigned seg;

	ioport_out(VGA_GC_INDEX, 6);
	seg = ioport_in(VGA_GC_DATA);
	seg >>= 2;
	seg &= 3;
	switch(seg)
	{
	case 0:
	case 1:
		seg = 0xA000;
		break;
	case 2:
		seg = 0xB000;
		break;
	case 3:
		seg = 0xB800;
		break;
	}
	return seg;
}
static void vmemwr(unsigned dst_off, unsigned char *src, unsigned count)
{
	_vmemwr(get_fb_seg(), dst_off, src, count);
}
static void set_plane(unsigned p)
{
	unsigned char pmask;

	p &= 3;
	pmask = 1 << p;
/* set read plane */
	ioport_out(VGA_GC_INDEX, 4);
	ioport_out(VGA_GC_DATA, p);
/* set write plane */
	ioport_out(VGA_SEQ_INDEX, 2);
	ioport_out(VGA_SEQ_DATA, pmask);
}
static void write_font(unsigned char *buf, unsigned font_height)
{
	unsigned char seq2, seq4, gc4, gc5, gc6;
	unsigned i;

/* save registers
set_plane() modifies GC 4 and SEQ 2, so save them as well */
	ioport_out(VGA_SEQ_INDEX, 2);
	seq2 = ioport_in(VGA_SEQ_DATA);

	ioport_out(VGA_SEQ_INDEX, 4);
	seq4 = ioport_in(VGA_SEQ_DATA);
/* turn off even-odd addressing (set flat addressing)
assume: chain-4 addressing already off */
	ioport_out(VGA_SEQ_DATA, seq4 | 0x04);

	ioport_out(VGA_GC_INDEX, 4);
	gc4 = ioport_in(VGA_GC_DATA);

	ioport_out(VGA_GC_INDEX, 5);
	gc5 = ioport_in(VGA_GC_DATA);
/* turn off even-odd addressing */
	ioport_out(VGA_GC_DATA, gc5 & ~0x10);

	ioport_out(VGA_GC_INDEX, 6);
	gc6 = ioport_in(VGA_GC_DATA);
/* turn off even-odd addressing */
	ioport_out(VGA_GC_DATA, gc6 & ~0x02);
/* write font to plane P4 */
	set_plane(2);
/* write font 0 */
	for(i = 0; i < 256; i++)
	{
		vmemwr(16384u * 0 + i * 32, buf, font_height);
		buf += font_height;
	}
#if 0
/* write font 1 */
	for(i = 0; i < 256; i++)
	{
		vmemwr(16384u * 1 + i * 32, buf, font_height);
		buf += font_height;
	}
#endif
/* restore registers */
	ioport_out(VGA_SEQ_INDEX, 2);
	ioport_out(VGA_SEQ_DATA, seq2);
	ioport_out(VGA_SEQ_INDEX, 4);
	ioport_out(VGA_SEQ_DATA, seq4);
	ioport_out(VGA_GC_INDEX, 4);
	ioport_out(VGA_GC_DATA, gc4);
	ioport_out(VGA_GC_INDEX, 5);
	ioport_out(VGA_GC_DATA, gc5);
	ioport_out(VGA_GC_INDEX, 6);
	ioport_out(VGA_GC_DATA, gc6);
}
// End copied code