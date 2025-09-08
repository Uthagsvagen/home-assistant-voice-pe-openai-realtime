#include "config.h"
#include <stdbool.h>

bool mcp_available() {
    return MCP_PUBLIC_URL[0] != 0;
}

int ha_get_state(const char* entity_id, char* out_json, int maxlen) {
    return 0;
}

int ha_call_service(const char* domain, const char* service, const char* payload_json) {
    return 0;
}