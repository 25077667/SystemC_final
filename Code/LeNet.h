#include <iostream>
#include "define.h"
#include "systemc.h"

using namespace std;

// vvvvv put your code here vvvvv
SC_MODULE(LeNet)
{
    sc_in_clk clk;
    sc_in<bool> rst;

    sc_out<bool> rom_rd;
    sc_out<sc_uint<16>> rom_addr;
    sc_in<DATA_TYPE> rom_data_out;

    sc_out<bool> ram_wr;
    sc_out<sc_uint<16>> ram_addr;
    sc_in<DATA_TYPE> ram_data_out;
    sc_out<DATA_TYPE> ram_data_in;

    sc_out<DATA_TYPE> result;
    sc_out<bool> output_valid;

    void run();

    // vvvvv my code vvvvv
    int state = -2;
    sc_uint<16> addr = 0;
    DATA_TYPE data[45210];

    int m, index;
    MUL_DATA_TYPE Conv1[6][24 * 24];
    MUL_DATA_TYPE MaxP1[6][12 * 12];
    MUL_DATA_TYPE Conv2[16][8 * 8];
    MUL_DATA_TYPE MaxP2[16][4 * 4];
    MUL_DATA_TYPE Flatten[16 * 4 * 4];
    MUL_DATA_TYPE Dense1[120];
    MUL_DATA_TYPE Dense2[84];
    MUL_DATA_TYPE Dense3[10];
    // ^^^^^ my code ^^^^^

    SC_CTOR(LeNet)
    {
        // vvvvv my code vvvvv
        SC_METHOD(run);
        sensitive << rst.pos() << clk.pos();
        // ^^^^^ my code ^^^^^
    }
};
// ^^^^^ put your code here ^^^^^
