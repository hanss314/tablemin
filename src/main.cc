#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#include <hidapi/hidapi.h>
#include <jack/jack.h>

#include "profile.h"
#include "jackclient.h"
#include "input.h"
#include "util.h"
#include "funcs.h"

#define VID 1386
#define PID 884

#define THRESHOLD(x) x>1?1.0:(x<-1?-1.0:x)

hid_device *tablet = NULL;
InputState *input = NULL;
Profile *profile = NULL;

void cleanup(void){
    if(tablet!=NULL) hid_close(tablet);
    if(input!=NULL) delete input;
    if(profile!=NULL) delete profile;
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
    /*profile = new ExtratoneProfile(
        new DiscreteProfile(440, 880),
        //new NoiseProfile(),
        1, 100
    );*/
    input = new InputState();
    /*profile = new EnablerProfile(
        new BasicProfile(220, 880), 65
    );*/
    /*int keys[] = {52,39,53,40,54,55,42,56,43,57,58,45,59,46,60,0};
    profile = new MixerProfile(
        new KeyboardProfile(list_to_freqmap(keys, 440, pow(2.0, 1.0/12.0))),
        new BasicProfile(220, 880)
    );*/
    //profile = new KeyboardProfile(list_to_freqmap(keys, 440, pow(2.0, 1.0/12.0)));

    //profile = new DiscreteProfile(440, 880);
    //profile = new NoiseProfile();
    profile = new WaveProfile(220, 880,
        new WaveformFunc(&simplesin, 2*M_PI),
        new AttackFunc(simpleinit, 1.2/1000.0),
        new ReleaseFunc(simpledecay,  1.0/10.0)
    );

    profile->setInput(input);
    profile->setRate(rate);
    while(true){
        if(!shouldgo){
            sleep(1.0/rate);
            continue;
        }
        int status = hid_read(tablet, data, 12);
        if(status==0){
            input->setState(data);
            profile->onStateUpdate();
            //profile->sendEvent(data);
        }
        for(int i=0; i<input->changecount; i++){
            profile->onKbEvent(
                input->changed[i], 
                input->pressedkeys[input->changed[i]]
            );
            input->changecount = 0;
        }
        float next = profile->getNext();
        append_buffer(THRESHOLD(next));
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
