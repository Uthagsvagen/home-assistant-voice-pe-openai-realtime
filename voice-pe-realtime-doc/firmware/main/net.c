#include "config.h"
#include <stdint.h>
#include <stddef.h>

int ws_connect(const char* url, const char* auth);
int ws_send_binary(const uint8_t* data, size_t len);
int ws_recv(uint8_t* buf, size_t maxlen, int* out_type);
int ws_close();

void net_init() {
    // initialize wifi and tls
}

int ws_connect(const char* url, const char* auth) {
    (void)url; (void)auth;
    return 0;
}

int ws_send_binary(const uint8_t* data, size_t len) {
    (void)data; (void)len;
    return 0;
}

int ws_recv(uint8_t* buf, size_t maxlen, int* out_type) {
    (void)buf; (void)maxlen; (void)out_type;
    return 0;
}

int ws_close() {
    return 0;
}
