# codex tasks

målet: generera färdig firmware för voice pe som kopplar wake word → openai realtime → ha mcp/tools.

## 1. audio io

- implementera i2s init in/out för esp32‑s3  
- samplerate 24 kHz mono pcm16  
- ringbuffer för mic in och speaker out  
- api:  
  - `audio_io_init()`  
  - `size_t audio_read(int16_t* buf, size_t frames)`  
  - `size_t audio_write(const int16_t* buf, size_t frames)`  

## 2. wake word

- enkel vads + keyword spotting  
- api:  
  - `void wakeword_init()`  
  - `bool wakeword_detected(const int16_t* buf, size_t frames)`  

## 3. nätverk

- wifi connect  
- tls websocket klient  
- api:  
  - `void net_init()`  
  - `int ws_connect(const char* url, const char* auth)`  
  - `int ws_send_binary(const uint8_t* data, size_t len)`  
  - `int ws_recv(uint8_t* buf, size_t maxlen, int* out_type)`  

## 4. realtime session

- connect till `wss://api.openai.com/v1/realtime?model=${OPENAI_REALTIME_MODEL}`  
- skicka session init json:  
  - om `MCP_PUBLIC_URL` finns: inkludera mcp remote server och bearer  
  - annars registrera klientverktyg: get_state, call_service  
- strömma pcm in (mic) som binär frames  
- spela upp inkommande pcm från assistant  
- api:  
  - `void rt_start()`  
  - `void rt_stop()`  

## 5. client tools (fallback)

- schema:  
  - `get_state(entity_id)`  
  - `call_service(domain, service, payload)`  
- mapping:  
  - ha websocket/rest enligt `HA_BASE_URL` + `HA_TOKEN`  

## 6. mcp bridge

- om mcp remote används: inget lokalt behövs, bara passera  
- om client tools: parse `function_call`, dispatch till HA  

## 7. robusthet

- reconnect backoff  
- tyst fallback till client tools om mcp svar uteblir  
- watchdog ljudbuffer underflow/overflow  

## 8. test

- loopback audio test  
- wake word trigger test  
- ha ping (get_state på light.kitchen)  
- end‑to‑end: “tänd kökslampan”  

## 9. build artifacts

- `sdkconfig.defaults` optimerad för i2s och wifi  
- release `idf.py build`