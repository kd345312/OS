#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdlib.h>
#include <cstring>
using namespace std;

#define SIZE 500

void fsAlg(int width, int height, int **input, int **output){
     for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            if(input[i][j] < 128)
                output[i][j] = 0;
            else
                output[i][j] = 1;
            int err = input[i][j] - 255*output[i][j];
            input[i][j+1] += err * 7/16;
            input[i+1][j-1] += err * 3/16;
            input[i+1][j] += err * 5/16;
            input[i+1][j+1] += err * 1/16;
        }
    }
}

void *buff(void *nothing){
    int w, h;
    int **imagein;
    int **imageout;
    fsAlg(w, h, imagein, imageout);
}

int main(int argc, char *argv[]){
    ifstream in;
    string filename;
    int **imagein;
    int **imageout;
    int tmax;
    int num;
    int rc;
    int h, w;
    pthread_t p[tmax];

    if(argc == 3){
       filename = argv[1];
       tmax = atoi(argv[2]);
    }
    else if(argc > 3)
        cerr << "Too many arguements\n";
    else
        cerr << "Too few arguements\n";
    
    in.open(filename.c_str());
    while(in >> num){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                imagein[i][j] = num;
                h = i;
                w = j;
            }
        }
    }
    for(int i = 0; i < tmax; i++){
        rc = pthread_create(&p[tmax], NULL, buff, (void *)i);
        cout << rc << endl;
    }
    pthread_exit(NULL);
    return 0;
}









