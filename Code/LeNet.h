#include "systemc.h"
#include "define.h"
#include <iostream>

using namespace std;

// vvvvv put your code here vvvvv
SC_MODULE( LeNet ) {	
	sc_in_clk clk;
	sc_in < bool > rst;
	
	sc_out < bool > rom_rd;
	sc_out < sc_uint<16> > rom_addr;
	sc_in < DATA_TYPE > rom_data_out;
	
	sc_out < bool > ram_wr;
	sc_out < sc_uint<16> > ram_addr;
	sc_in < DATA_TYPE > ram_data_out;
	sc_out < DATA_TYPE > ram_data_in;
	
	sc_out < DATA_TYPE > result;
	sc_out < bool > output_valid;
  
	void run();
  
	// vvvvv my code vvvvv 
  int state = -2;
  sc_uint<16> addr = 0;
  float data[45210];
  
  int kernel[6] = {0, 26, 52, 78, 104, 130};
  int kernel2[16] = {156, 182, 208, 234, 260, 286, 312, 338, 364, 390, 416, 442, 468, 494, 520, 546};
  int m, index;
  DATA_TYPE Conv1[6][24*24];
  DATA_TYPE MaxP1[6][12*12];
  DATA_TYPE Conv2[16][8*8];
  DATA_TYPE MaxP2[16][4*4];
  DATA_TYPE Flatten[16*4*4];
  DATA_TYPE Dense1[120];
  DATA_TYPE Dense2[84];
  DATA_TYPE Dense3[10];
  // ^^^^^ my code ^^^^^
  
  
	SC_CTOR( LeNet )
	{
	  // vvvvv my code vvvvv
    SC_METHOD( run );
		sensitive << rst.pos() << clk.pos();
    // ^^^^^ my code ^^^^^		  
	}
 
};
// ^^^^^ put your code here ^^^^^
