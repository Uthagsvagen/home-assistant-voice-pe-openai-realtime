#include "config.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void net_init();
void audio_io_init();
void wakeword_init();
bool wakeword_detected(const int16_t* buf, size_t frames);
void rt_start();

size_t audio_read(int16_t* buf, size_t frames);

void app_main() {
    net_init();
    audio_io_init();
    wakeword_init();
    int16_t buf[2400];
    while (1) {
        size_t n = audio_read(buf, 2400);
        if (wakeword_detected(buf, n)) {
            rt_start();
        }
    }
}
