#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <jack/jack.h>


jack_port_t *output_port;
jack_client_t *client;

size_t buffer_position;
size_t buffer_size;
jack_default_audio_sample_t* ringbuffer;

bool *goflag;

void jack_cleanup(){
    if(ringbuffer!=NULL)
        free(ringbuffer);
    if(client!=NULL)
        jack_client_close(client);
}

void append_buffer(jack_default_audio_sample_t f){
    ringbuffer[buffer_position]=f;
    buffer_position++;
    *goflag = buffer_position < buffer_size;
    buffer_position%=buffer_size;
    //printf("%d\n", buffer_position);
}

int process(jack_nframes_t nframes, void *arg) {
	*goflag = true;
    jack_default_audio_sample_t *out;
    out = (jack_default_audio_sample_t*)jack_port_get_buffer(output_port, nframes);
    memcpy (out, ringbuffer+buffer_position,
		sizeof(jack_default_audio_sample_t) * (buffer_size-buffer_position));
    memcpy (out+buffer_size-buffer_position, ringbuffer,
		sizeof(jack_default_audio_sample_t) * buffer_position);
	return 0;      
}

jack_client_t *initialize(bool *go_flag){
    jack_status_t status;
    client = jack_client_open("Tablemin", JackNullOption,
                            &status, NULL);

    if(client==NULL) return NULL;
    jack_set_process_callback(client, process, 0);
    
    output_port = jack_port_register (client, "output",
					 JACK_DEFAULT_AUDIO_TYPE,
					 JackPortIsOutput, 0);
    if(output_port==NULL) return NULL;
    if(jack_activate(client)) return NULL;
    const char **ports = jack_get_ports (client, NULL, NULL,
				JackPortIsPhysical|JackPortIsInput);
    
    if(ports==NULL) return NULL;
    if(jack_connect(client, jack_port_name (output_port), ports[0]))
        return NULL;
    if(jack_connect(client, jack_port_name (output_port), ports[1]))
        return NULL;

    free(ports);
    atexit(jack_cleanup);
    ringbuffer = (float*)malloc(sizeof(float)*jack_get_sample_rate(client));
    buffer_size = jack_get_buffer_size(client);
    
    goflag = go_flag;

    return client;
}
