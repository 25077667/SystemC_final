#include "LeNet.h"

// vvvvv put your code here vvvvv

void LeNet::run() {

    if(state < 0)
    {
         output_valid.write(0);
         rom_rd.write(1);
         rom_addr.write(addr);
         state++;
    }
    else if (state == 0)
    {
         data[addr] = rom_data_out.read();
         addr++;
         
         output_valid.write(0);
         rom_rd.write(1);
         rom_addr.write(addr);
         
         if(addr == 45209){
             addr = 0;
             state = 1;
         }
    }
    else if (state == 1)
    {
         rom_rd.write(0);
         output_valid.write(0);
         //Convolution layer - 1
         for(int i = 0; i < 6; i++)
         {
            m = 44426;
            for(int j = 0; j < 24*24; j++)
            {
                index = m;
                for(int k = 0; k < 25; k++)
                {
                     Conv1[i][j] += data[index]*data[kernel[i]+k];
                     
                     if(k%5 == 0) index += 24;
                     else index++;
                }
                
                Conv1[i][j] += data[kernel[i]+25];
                if(Conv1[i][j] < 0) Conv1[i][j] = 0;
                if((m-44449)%28 == 0) m += 5;
                else m++;
            }
    		 }
         
        //MaxPooling layer - 1
        for(int i = 0; i < 6; i++)
        {
             m = 0;
             for(int j = 0; j < 12*12; j++)
             {
                 MaxP1[i][j] = Conv1[i][m];
                 if(MaxP1[i][j] < Conv1[i][m+1]) MaxP1[i][j] = Conv1[i][m+1];
                 if(MaxP1[i][j] <  Conv1[i][m+24]) MaxP1[i][j] =  Conv1[i][m+24];
                 if(MaxP1[i][j] <  Conv1[i][m+25]) MaxP1[i][j] =  Conv1[i][m+25];
                 
                 if((m+2)%24 == 0) m += 26;
                 else m += 2;
             }
        }
        
        //Convolution layer - 2
         for(int i = 0; i < 16; i++)
         {
            m = 0;
            for(int j = 0; j < 8*8; j++)
            {
                index = m;
                for(int k = 0; k < 25; k++)
                {
                     Conv2[i][j] += MaxP1[0][index]*data[kernel2[i]+k];
                     Conv2[i][j] += MaxP1[1][index]*data[kernel2[i]+k];
                     Conv2[i][j] += MaxP1[2][index]*data[kernel2[i]+k];
                     Conv2[i][j] += MaxP1[3][index]*data[kernel2[i]+k];
                     Conv2[i][j] += MaxP1[4][index]*data[kernel2[i]+k];
                     Conv2[i][j] += MaxP1[5][index]*data[kernel2[i]+k];
                     
                     if(k%5 == 0) index += 20;
                     else index++;
                }
                
                Conv2[i][j] += data[kernel[i]+25];
                if(Conv2[i][j] < 0) Conv2[i][j] = 0;
                
                if((m-7)%12 == 0) m += 5;
                else m++;
            }
    		 }
        
        //MaxPooling layer - 2
        for(int i = 0; i < 16; i++)
        {
             m = 0;
             for(int j = 0; j < 4*4; j++)
             {
                 MaxP2[i][j] = Conv2[i][m];
                 if(MaxP2[i][j] < Conv2[i][m+1]) MaxP2[i][j] = Conv2[i][m+1];
                 if(MaxP2[i][j] < Conv2[i][m+7]) MaxP2[i][j] =  Conv2[i][m+7];
                 if(MaxP2[i][j] < Conv2[i][m+8]) MaxP2[i][j] =  Conv2[i][m+8];
                 
                 if((m+2)%8 == 0) m += 10;
                 else m += 2;
             }
        }
        
        //Flatten
        m = 0;
        for(int i = 0; i < 4*4; i++)
        {
              for(int j = 0; j < 16; j++)
              {
                  Flatten[m] =  MaxP2[j][i];
                  m++;
              }
        }
        
        //Dense layer - 1
        for(int i = 0; i < 120; i++)
        {
            for(int j = 0; j < 4*4*6; j++)
            {
                Dense1[i] += Flatten[j]*data[2572+(257)*i+j];
            } 
            Dense1[i] += data[2572+(257)*(i+1)-1];
            if(Dense1[i] < 0) Dense1[i] = 0;
        }
        
        //Dense layer - 2
        for(int i = 0; i < 84; i++)
        {
            for(int j = 0; j < 120; j++)
            {
                Dense2[i] += Dense1[j]*data[33412+(121)*i+j];
            } 
            Dense2[i] += data[33412+(121)*(i+1)-1];
            if(Dense2[i] < 0) Dense2[i] = 0;
        }
        
        //Dense layer - 3
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 84; j++)
            {
                Dense3[i] += Dense2[j]*data[43576+(85)*i+j];
            } 
            Dense3[i] += data[43576+(85)*(i+1)-1];
            if(Dense3[i] < 0) Dense3[i] = 0;
            cout << "Dense3[" << i << "] = " << Dense3[i] << endl;
        }
        
        m = 0;
        state++;
    }
    else
    {
        if(m < 10)
        {
            output_valid.write(1);
            result.write(Dense3[m]);
            m++;
        }
    }

}
// ^^^^^ put your code here ^^^^^
