#include <cmath>

float *list_to_freqmap(int *keys, float start, float step){
    float *map = (float*)malloc(sizeof(float)*256);
    for(int i=0; i<256; i++){
        map[i] = 0.0;
    }
    int i=0;
    int key;
    while((key=keys[i++]) != 0){
        map[key] = start;
        start *= step;
    }
    return map;
    
}
