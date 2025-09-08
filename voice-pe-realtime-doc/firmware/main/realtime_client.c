#include "config.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

int ws_connect(const char* url, const char* auth);
int ws_send_binary(const uint8_t* data, size_t len);
int ws_recv(uint8_t* buf, size_t maxlen, int* out_type);
size_t audio_read(int16_t* buf, size_t frames);
size_t audio_write(const int16_t* buf, size_t frames);

void rt_start() {
    const char* url = "wss://api.openai.com/v1/realtime?model=" OPENAI_REALTIME_MODEL;
    char auth[256];
    // build auth header
    int ok = ws_connect(url, auth);
    if (ok != 0) return;
    uint8_t rx[4096];
    int16_t inbuf[4800];
    for (;;) {
        size_t n = audio_read(inbuf, 2400);
        if (n > 0) ws_send_binary((uint8_t*)inbuf, n * sizeof(int16_t));
        int t = 0;
        int r = ws_recv(rx, sizeof(rx), &t);
        if (r > 0 && t == 2) audio_write((int16_t*)rx, r / 2);
    }
}