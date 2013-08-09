//
// obj_demo.c
// testing various sprite related things
//
// (20031003 - 20060924, Cearn)

#include <string.h>
#include "toolbox.h"
#include "metr.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;
OBJ_ATTR *metr= &obj_buffer[0]; //graphics variables, need to be global so both setup() and main can see them



void setup()
{
	u32 tid= 0, pb= 0;		// tile id, pal-bank
	// Places the glyphs of a 4bpp boxed metroid sprite 
	//   into LOW obj memory (cbb == 4)
	memcpy(&tile_mem[4][0], metr_boxTiles, 64);
	memcpy(pal_obj_mem, metrPal, metrPalLen);

	oam_init(obj_buffer, 128);
	REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D;
	obj_set_attr(metr, 
		ATTR0_SQUARE,				// Square, regular sprite
		ATTR1_SIZE_8,					// 8x8p, 
		ATTR2_PALBANK(pb) | tid);		// palbank 0, tile 0

}
int main()
{

	int vy=0;
	int x= 96, y= 32; //variables local to main
	
	setup();


	while(1)
	{
		vid_vsync();
		key_poll();

		// move left/right
		x += 2*key_tri_horz();
		
		vy=vy-1;//gravity
		y -= vy;//vertical speed (velocity)
		
		if(y>148){ //bouncing off the planet 
			vy=vy*-1;
			vy=vy-1;
			y=148;
		}


		// Rockets
		if(KEY_DOWN_NOW(KEY_A))
			vy=vy+2;


		obj_set_pos(metr, x, y);

		oam_copy(oam_mem, obj_buffer, 1);	// only need to update one
	}

	return 0;
}
