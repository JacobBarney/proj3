include "defn.h"

int main()
{
    float ***dataSet;

    dataSet = new float***[YEARS * WEEKS];
    
    for (int i = 0; i < YEARS*WEEKS; i++){
        dataSet[i] = new float*[ROWS];
        for(int j = 0; j < ROWS; j++){
            dataSet[i][j] = new float[COLS];
        }
    }

    for (int i = 0; i < YEARS*WEEKS; i++){
        
        for(int j = 0; j < ROWS; j++){
            delete [] dataSet[i][j];
        }
        delete [] dataSet[i][j];
    }
    delete [] dataSet;

   











