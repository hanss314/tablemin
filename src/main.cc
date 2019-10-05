#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <hidapi/hidapi.h>
#include <jack/jack.h>

#include "profile.h"
#include "jackclient.h"

#define VID 1386
#define PID 884

hid_device *tablet;
Profile *profile;

void cleanup(void){
    if(tablet!=NULL){
       hid_close(tablet);
    }
    if(profile!=NULL){
        delete profile;
    }
    hid_exit();
    printf("Exiting\n");
}   

int main(){
    hid_device *tablet = hid_open(VID, PID, NULL);
    if(tablet==NULL){
        fprintf(stderr, "Device not found\n");
        return -1;
    }
    hid_set_nonblocking(tablet, 1); 
    atexit(cleanup);
    unsigned char data[12];
    bool shouldgo = true;
    jack_client_t *client = initialize(&shouldgo); 
    if(client==NULL){
        fprintf(stderr, "Failed to connect to JACK\n");
        return -2;
    }
    
    int rate = jack_get_sample_rate(client);
    profile = new BasicProfile(rate, 440, 880);
    printf("Success\n");
    while(true){
        if(!shouldgo){
            sleep(1.0/rate);
            continue;
        }
        int status = hid_read(tablet, data, 12);
        if(status==0){
            profile->setState(data);
        }
        float next = profile->getNext();
        append_buffer(next);
        /*
        i++;
        if(i >= 512){
            printf("Reset\n");
            start = Time::now();
            i = 0;
        }
        now = Time::now();
        fsec dt = start-now;
        float sleeptime = dt.count()+((float)i)/rate;
        
        if(sleeptime > 0) sleep(sleeptime);
        */
    }
    return 0;
}
