#include "defn.h"


int connectedComponent(struct graphPoint *point, struct graphPoint **graph, int count)
{
    if(point->time == -1)
    {
        point->time = count;
        for(int k = 0; point->dest[k].row != -1; k++)
        {
            count++;
            count = connectedComponent(&(graph[point->dest[k].row][point->dest[k].col]), graph, count);
        }
    }
    return count;
}

int clusterCoefficient(struct graphPoint *point, struct graphPoint **graph)
{  
    int edge = 0;
    int count = 0;
    float coeff;
    
    for(int i = 0; point->dest[i].row != -1; i++)
    {
        for(int j = 0; point->dest[j].row != -1; j++)
        {
            bool add = false;
            for(int k = i; point->dest[i]->dest[k] != null; k++)
            {
                if(point->dest[i]->dest[j].row == point->dest[k].row && point->dest[i]=>dest[j].col == point->dest[k].col)
                {
                    add = true;
                }
                if(add)
                {
                    edge += 1;
                }
            }
        }
        count++;
    }
    
    coeff = (edge * 2) / (count * (count - 1));
    return coeff;

}



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

    struct graphPoint **graph;
    graph = new graphPoint*[ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        graph[i] = new struct graphPoint[COLS];
        for(int h = 0; h < COLS; h++)
        {
            graph[i][h].dest = new struct destPoint[ROWS*COLS];
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
                                //printf("Edge found! %d %d and %d %d time of first\n", i, j, p, q);
                                int e = 0;
                                while(graph[i][j].dest[e].row != -1)
                                {
                                    e++;
                                }
                                graph[i][j].dest[e].row = p;
                                graph[i][j].dest[e].col = q;
                                e = 0;
                                while(graph[i][j].dest[e].row != -1)
                                {
                                    e++;
                                }
                                graph[p][q].dest[e].row = i;
                                graph[p][q].dest[e].col = j;
                            }
                        }
                    }
                }
            } 
        }
    }
    
    int count[ROWS*COLS] = [0];

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int connected = connectedComponent(&(graph[i][j]), graph, 0);
            if (connected > 0)
            {
                printf("Graph of size %d\n", connected+1);
                //printf("connected %d for %d, %d: ", temp, i, j);
                //for(int k = 0; graph[i][j].dest[k].row != -1; k++)
                //    printf("point %d, %d,  ", graph[i][j].dest[k].row, graph[i][j].dest[k].col);
                //printf("\n");
            }
        }
    }

    for(int i = 0; i < ROWS*COLS; i++)
    {
        if(count[i] > 0)
        {
            printf("%d graphs of size %d", count[i], i);
        }
    }

    for (int i = 0; i < ROWS; i++)
    {
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


