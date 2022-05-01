#include "vga.h"
#include "../kernel/kernel.h"
#include "../screen/screen.h"

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
// End copied code