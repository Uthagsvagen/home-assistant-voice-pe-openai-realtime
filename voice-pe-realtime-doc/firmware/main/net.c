#include "config.h"
#include <stdint.h>

int ws_connect(const char* url, const char* auth);
int ws_send_binary(const uint8_t* data, size_t len);
int ws_recv(uint8_t* buf, size_t maxlen, int* out_type);

void net_init() {
    // initialize wifi and tls
}

int ws_connect(const char* url, const char* auth) {
    return 0;
}

int ws_send_binary(const uint8_t* data, size_t len) {
    return 0;
}

int ws_recv(uint8_t* buf, size_t maxlen, int* out_type) {
    return 0;
}