#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define SAMPLE_RATE 24000
#define BUFFER_FRAMES 2400

static int16_t mic_buffer[BUFFER_FRAMES];
static size_t mic_head, mic_tail;
static int16_t spk_buffer[BUFFER_FRAMES];
static size_t spk_head, spk_tail;

void audio_io_init() {
    mic_head = mic_tail = 0;
    spk_head = spk_tail = 0;
    memset(mic_buffer, 0, sizeof(mic_buffer));
    memset(spk_buffer, 0, sizeof(spk_buffer));
    // Hardware specific I2S initialisation would go here when
    // building for ESP32. This stub keeps compilation simple.
}

static size_t ring_available(size_t head, size_t tail) {
    if (head >= tail) return head - tail;
    return BUFFER_FRAMES - tail + head;
}

size_t audio_read(int16_t* buf, size_t frames) {
    size_t available = ring_available(mic_head, mic_tail);
    if (frames > available) frames = available;
    for (size_t i = 0; i < frames; ++i) {
        buf[i] = mic_buffer[mic_tail];
        mic_tail = (mic_tail + 1) % BUFFER_FRAMES;
    }
    return frames;
}

size_t audio_write(const int16_t* buf, size_t frames) {
    size_t space = BUFFER_FRAMES - ring_available(spk_head, spk_tail) - 1;
    if (frames > space) frames = space;
    for (size_t i = 0; i < frames; ++i) {
        spk_buffer[spk_head] = buf[i];
        spk_head = (spk_head + 1) % BUFFER_FRAMES;
    }
    return frames;
}
