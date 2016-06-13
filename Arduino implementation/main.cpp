#include "due_sam3x.init.h"
#include "hwlib.hpp"
#include "ddd.hpp"

int main( void )
{
	WDT->WDT_MR = WDT_MR_WDDIS; // MURDERER DE WAAKHOND!!!!!!!!!!!!
    
    auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );  
    auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto i2c = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    auto slavescreen = hwlib::glcd_oled(i2c);
    auto screen = hwlib::bufferwindow(slavescreen);

	unsigned char verticeslength = 8;
	unsigned char edgelength = 12;
	const unsigned char width = 128;
	const unsigned char height = 64;

	Vertex vertices[] = {
		{ 16,  16,  16},
		{ 16,  16, -16},
		{ 16, -16,  16},
		{-16,  16,  16},
		{ 16, -16, -16},
		{-16,  16, -16},
		{-16, -16,  16},
		{-16, -16, -16},
	};

	Edge edges[] = {
		{0, 1},
		{0, 2},
		{0, 3},
		{1, 4},
		{1, 5},
		{2, 4},
		{2, 6},
		{3, 5},
		{3, 6},
		{4, 7},
		{5, 7},
		{6, 7},
	};

	Vertex pyrverts[] = {
		{ 10,  0,  10},
		{-10,  0,  10},
		{ 10,  0, -10},
		{-10,  0, -10},
		{  0, 25,   0},
	};

	Edge pyredge[] = {
		{0, 1},
		{0, 2},
		{1, 3},
		{2, 3},
		{0, 4},
		{1, 4},
		{2, 4},
		{3, 4},
	};


	driedobj cube(screen, vertices, edges, verticeslength, edgelength, width, height);
	driedobj pyramid(screen, pyrverts, pyredge, 5, 8, width, height);

	pyramid.rotateZ(90);
	pyramid.translate(64, 0, 0);
	cube.rotateZ(1);
	cube.rotateY(1);

	int i = 0;
	while (true) {

		i++;
		pyramid.translate(-1, 0, 0);
		cube.rotateZ(1);
		cube.rotateY(2);
		cube.rotateX(3);
		pyramid.rotateX(3);
		if(pyramid.posx < -100){pyramid.posx=100;}
		if (i == 100) {
		screen.clear();
		pyramid.draw();
		cube.draw();
		i = 0;
		}

	}
}
