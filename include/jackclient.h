#include <jack/jack.h>

jack_client_t *initialize(bool*);
void append_buffer(jack_default_audio_sample_t f);
