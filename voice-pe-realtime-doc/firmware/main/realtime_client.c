#include "config.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

int ws_connect(const char* url, const char* auth);
int ws_send_binary(const uint8_t* data, size_t len);
int ws_recv(uint8_t* buf, size_t maxlen, int* out_type);
int ws_close();
size_t audio_read(int16_t* buf, size_t frames);
size_t audio_write(const int16_t* buf, size_t frames);
bool stopword_detected(const int16_t* buf, size_t frames);

static bool running = false;

void rt_start() {
    const char* url = "wss://api.openai.com/v1/realtime?model=" OPENAI_REALTIME_MODEL;
    char auth[256];
    // build auth header (Bearer + API key)
    int ok = ws_connect(url, auth);
    if (ok != 0) return;
    running = true;
    uint8_t rx[4096];
    int16_t inbuf[4800];
    while (running) {
        size_t n = audio_read(inbuf, 2400);
        if (n > 0) {
            if (stopword_detected(inbuf, n)) break;
            ws_send_binary((uint8_t*)inbuf, n * sizeof(int16_t));
        }
        int t = 0;
        int r = ws_recv(rx, sizeof(rx) - 1, &t);
        if (r > 0) {
            if (t == 2) {
                audio_write((int16_t*)rx, r / 2);
            } else if (t == 1) {
                rx[r] = 0;
                if (strstr((char*)rx, "Avsluta konversations") != NULL) {
                    break;
                }
            }
        }
    }
    rt_stop();
}

void rt_stop() {
    running = false;
    ws_close();
}
