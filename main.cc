#include "defn.h"

int main()
{
    float ***dataSet;

    dataSet = new float**[YEARS * WEEKS];

    for (int i = 0; i < YEARS*WEEKS; i++)
    {
        dataSet[i] = new float*[ROWS];
        for(int j = 0; j < ROWS; j++)
        {
            dataSet[i][j] = new float[COLS];
        }
    }

    float **averages;
    averages = new float*[ROWS];

    for (int i = 0; i < ROWS; i++)
    {
        averages[i] = new float[COLS];
        for (int h = 0; h < COLS; h++)
        {
            averages[i][h] = 0.0;
        }
    }

    struct point ***graph;
    graph = new point**[ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        graph[i] = new struct point*[COLS];
        for(int h = 0; h < COLS; h++)
        {
            graph[i][h] = new struct point[ROWS*COLS];
        }
    }

    for (int i = START_YEAR; i <= END_YEAR; i++)
    {
        for(int j = 1; j <= WEEKS; j++){
            char fileName [100];
            sprintf(fileName, "CS310_project_subregion/%d/Beaufort_Sea_diffw%02dy%d+landmask",i,j,i);
            ifstream file(fileName, ios::binary);
            if(file.is_open())
            {
                for(int h = 0; h < ROWS; h++)
                {
                    for(int k = 0; k < COLS; k++)
                    {
                        file.read((char*)&dataSet[(((i - START_YEAR)*WEEKS) + j) - 1][h][k], sizeof(float));
                        averages[h][k] += dataSet[(((i - START_YEAR)*WEEKS) + j) - 1][h][k];
                    }
                }
            }
            file.close();
        }
    }

    for (int i = 0; i < ROWS; i++)
    {
        for(int h = 0; h < COLS; h++)
        {
            averages[i][h] = averages[i][h]/(YEARS*WEEKS);
        }
    }

    for(int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if(dataSet[i][j][0] != 168 &&
                    dataSet[i][j][0] != 157)
            {
                for (int p = i; p < ROWS; p++)
                {
                    for (int q = j+1; q < COLS; q++)
                    {
                        if(dataSet[p][q][0] != 168 &&
                            dataSet[p][q][0] != 157)
                        {
                            int Sxx = 0;
                            int Syy = 0;
                            int Sxy = 0;
                            for (int k = 0; k <= END_YEAR - START_YEAR; k++)
                            {
                                Sxx += pow((dataSet[i][j][k] - averages[i][j]), 2.0);
                                Syy += pow((dataSet[p][q][k] - averages[p][q]), 2.0);
                                Sxy += (dataSet[i][j][k] - averages[i][j])*(dataSet[p][q][k] - averages[p][q]);
                            }
                            if(Sxy / sqrt(Sxx*Syy) > thresh)
                            {
                                printf("Edge found! %d %d and %d %d\n", i, j, p, q);
                                int e = 0;
                                while(graph[i][j][e].row != -1)
                                {
                                    e++;
                                }
                                graph[i][j][e].row = p;
                                graph[i][j][e].col = q;
                                e = 0;
                                while(graph[i][j][e].row != -1)
                                {
                                    e++;
                                }
                                graph[p][q][e].row = i;
                                graph[p][q][e].col = j;
                            }
                        }
                    }
                }
            } 
        }
    }


    for (int i = 0; i < ROWS; i++)
    {
        for(int h = 0; h < COLS; h++)
        {
            delete [] graph[i][h];
        }
        delete [] graph[i];
    }
    delete [] graph;

    for (int i = 0; i < ROWS; i++)
    {
        delete [] averages[i];
    }
    delete [] averages;
    
    for (int i = 0; i < YEARS*WEEKS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            delete [] dataSet[i][j];
        }
        delete [] dataSet[i];
    } 
    delete [] dataSet;
}


