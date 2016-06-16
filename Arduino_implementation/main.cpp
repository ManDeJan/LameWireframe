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
	screen.clear();

	int i = 0, j = 0;
	float scale = 1.02;
	while (true) {
		screen.clear();
		
		pyramid.translate(-1, 0, 0);
		pyramid.rotateX(3);
		if(pyramid.posx < -100){pyramid.posx=100;}
		pyramid.draw();

		cube.rotateZ(3);
		cube.rotateY(4);
		cube.rotateX(5);
		cube.scale(scale);
		cube.draw();

		if(j == 5) {	//here you can specify the amount of calculated frames per flush
			scale = 0.98;
		}
		if (j >= 10){
			scale = 1.02;
			j = 0;
		} else {
			j++;
		}

		if(i == 0) {	//here you can specify the amount of calculated frames per flush
			screen.flush();
			i=0;
		} else {
			i++;
		}
	}
}
