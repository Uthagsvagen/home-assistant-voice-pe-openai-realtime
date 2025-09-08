#include "config.h"

void net_init();
void audio_io_init();
void wakeword_init();
void rt_start();

void app_main() {
    net_init();
    audio_io_init();
    wakeword_init();
    rt_start();
    while (1) {
        // idle loop
    }
}