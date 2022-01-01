#include "Dense.h"

// vvvvv put your code here vvvvv

void Dense::run()
{
  
  if (rst) {
  } else if (dense_valid) {
  
        output_valid.write(0);
  
        if(count < 41854){
            data[count] = dense_data.read();
            count++;
        }
        else if(state == 1){
        
              if (m < 10) {
                  output_valid.write(1);
                  result.write(Dense3[m]);
                  m++;
              }
        
        }
        else{
            MaxP2[m][index] = dense_data.read();
            if(index < 15)
                index++;
            else{
                index = 0;
                m++;
            }
            count++;
            
            if(count == 41854 + 4*4*16){
            
                  // Flatten
                  m = 0;
                  for (int i = 0; i < 4 * 4; i++) {
                      for (int j = 0; j < 16; j++) {
                          Flatten[m] = MaxP2[j][i];
                          m++;
                      }
                  }
          
                  // Dense layer - 1
                  for (int i = 0; i < 120; i++) {
                      for (int j = 0; j < 4 * 4 * 16; j++) {
                          Dense1[i] += Flatten[j] * data[257*i + j];
                      }
                      Dense1[i] += data[257*i + 256];
                      if (Dense1[i] < 0)
                          Dense1[i] = 0;
                  }
          
                  // Dense layer - 2
                  for (int i = 0; i < 84; i++) {
                      for (int j = 0; j < 120; j++) {
                          Dense2[i] += Dense1[j] * data[30840+ 121*i + j];
                      }
                      Dense2[i] += data[30840 + 121*i + 120];
                      if (Dense2[i] < 0)
                          Dense2[i] = 0;
                  }
          
                  // Dense layer - 3
                  for (int i = 0; i < 10; i++) {
                      for (int j = 0; j < 84; j++) {
                          Dense3[i] += Dense2[j] * data[41004 + 85*i + j];
                      }
                      Dense3[i] += data[41004 + 85*i + 84];
                      if (Dense3[i] < 0)
                          Dense3[i] = 0;
                  }
          
                  m = 0;
                  state = 1;
              }
            
            }
        }
  }
  
// ^^^^^ put your code here ^^^^^
