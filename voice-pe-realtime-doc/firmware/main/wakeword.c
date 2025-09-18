#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#define ENERGY_THRESHOLD 2000
#define ENERGY_HITS      400
#define STOP_HITS        800

static int energy_count = 0;
static int stop_count = 0;

void wakeword_init() {
    energy_count = 0;
    stop_count = 0;
}

bool wakeword_detected(const int16_t* buf, size_t frames) {
    for (size_t i = 0; i < frames; ++i) {
        if (abs(buf[i]) > ENERGY_THRESHOLD) {
            if (++energy_count > ENERGY_HITS) {
                energy_count = 0;
                return true;
            }
        } else {
            energy_count = 0;
        }
    }
    return false;
}

bool stopword_detected(const int16_t* buf, size_t frames) {
    for (size_t i = 0; i < frames; ++i) {
        if (abs(buf[i]) > ENERGY_THRESHOLD) {
            if (++stop_count > STOP_HITS) {
                stop_count = 0;
                return true;
            }
        } else {
            stop_count = 0;
        }
    }
    return false;
}
