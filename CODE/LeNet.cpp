#include "LeNet.h"

// vvvvv put your code here vvvvv

void LeNet::run()
{

  if(state < 0) {
        dense_valid.write(0);
        rom_rd.write(1);
        rom_addr.write(addr);
        state++;
  }
  
	else if (state == 0) {
        if(addr >= 1){
          data[addr-1] = rom_data_out.read();
        }
        addr++;
        dense_valid.write(0);
        rom_rd.write(1);
        rom_addr.write(addr);

        if (addr == 45211) {
            addr = 0;
            state = 1;
        }
  }
  
	else if (state == 1) {
        rom_rd.write(0);
        dense_valid.write(0);
        
        // Convolution layer - 1
        for (int i = 0; i < 6; i++) {
            m = 44426;
            for (int j = 0; j < 24 * 24; j++) {
                index = m;
                for (int k = 0; k < 25; k++) {
                    Conv1[i][j] += data[index] * data[26*i + k];

                    if (k % 5 == 4)
                        index += 24;
                    else
                        index++;
                }

                Conv1[i][j] += data[26*i + 25];
                if (Conv1[i][j] < 0)
                    Conv1[i][j] = 0;
                if ((m - 44449) % 28 == 0)
                    m += 5;
                else
                    m++;
            }
        }

        // MaxPooling layer - 1
        for (int i = 0; i < 6; i++) {
            m = 0;
            for (int j = 0; j < 12 * 12; j++) {
                MaxP1[i][j] = Conv1[i][m];
                if (MaxP1[i][j] < Conv1[i][m + 1])
                    MaxP1[i][j] = Conv1[i][m + 1];
                if (MaxP1[i][j] < Conv1[i][m + 24])
                    MaxP1[i][j] = Conv1[i][m + 24];
                if (MaxP1[i][j] < Conv1[i][m + 25])
                    MaxP1[i][j] = Conv1[i][m + 25];

                if ((m + 2) % 24 == 0)
                    m += 26;
                else
                    m += 2;
            }
        }

        // Convolution layer - 2
        for (int i = 0; i < 16; i++) {
            m = 0;
            for (int j = 0; j < 8 * 8; j++) {
                index = m;
                for (int k = 0; k < 25; k++) {
                    Conv2[i][j] += MaxP1[0][index] * data[156+151*i+k];
                    Conv2[i][j] += MaxP1[1][index] * data[156+151*i+25+k];
                    Conv2[i][j] += MaxP1[2][index] * data[156+151*i+50+k];
                    Conv2[i][j] += MaxP1[3][index] * data[156+151*i+75+k];
                    Conv2[i][j] += MaxP1[4][index] * data[156+151*i+100+k];
                    Conv2[i][j] += MaxP1[5][index] * data[156+151*i+125+k];

                    if (k % 5 == 4)
                        index += 8;
                    else
                        index++;
                }

                Conv2[i][j] += data[156+151*i+150];
                if (Conv2[i][j] < 0)
                    Conv2[i][j] = 0;

                if ((m - 7) % 12 == 0)
                    m += 5;
                else
                    m++;
            }
        }

        // MaxPooling layer - 2
        for (int i = 0; i < 16; i++) {
            m = 0;
            for (int j = 0; j < 4 * 4; j++) {
                MaxP2[i][j] = Conv2[i][m];
                if (MaxP2[i][j] < Conv2[i][m + 1])
                    MaxP2[i][j] = Conv2[i][m + 1];
                if (MaxP2[i][j] < Conv2[i][m + 8])
                    MaxP2[i][j] = Conv2[i][m + 8];
                if (MaxP2[i][j] < Conv2[i][m + 9])
                    MaxP2[i][j] = Conv2[i][m + 9];
                
                if ((m + 2) % 8 == 0)
                    m += 10;
                else
                    m += 2;
            }
        }


        m = 0;
        index = 0;
        count = 0;
        state++;
        
    }
    
    else {
    
        if (count < 41854) {
            dense_valid.write(1);
            dense_data.write(data[2572+m]);
            m++;
            count++;
            if(m == 41854) m = 0;
        }
        else if(count < 41854 + 16*4*4){
            dense_valid.write(1);
            dense_data.write(MaxP2[m][index]);
            if(index < 15)
                index++;
            else{
                index = 0;
                m++;
            }
            count++;
        }
    }
}
// ^^^^^ put your code here ^^^^^
