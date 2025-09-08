#include <stdint.h>
#include <stddef.h>

void audio_io_init() {
    // init I2S or audio hardware
}

size_t audio_read(int16_t* buf, size_t frames) {
    return 0;
}

size_t audio_write(const int16_t* buf, size_t frames) {
    return 0;
}