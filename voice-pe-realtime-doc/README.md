# voice-pe-realtime

från wake word till gpt‑realtime med mcp‑åtkomst till home assistant. firmware för voice assistant pe som kör:

* lokal wake word  
* vid aktivering: full duplex till openai realtime api  
* verktygsanrop via mcp till home assistant, eller lokala klientverktyg som fallback  

## krav

* esp‑idf v5+  
* voice pe‑hårdvara (esp32‑s3 + xmos/codec)  
* home assistant ≥ 2025.2 med mcp server  
* openai api‑nyckel  
* wi‑fi  

## två lägen för verktyg

1. **remote mcp** – exponera ha mcp server över https med token. realtime‑sessionen får mcp‑url + auth.  
2. **client tools** – firmware översätter tool calls och anropar ha lokalt (rest/websocket). använd när mcp inte är publikt.  

## bygg

```bash
idf.py set‑target esp32s3
idf.py build
idf.py ‑p /dev/tty.usbmodemX flash monitor
```

## konfiguration

miljövariabler eller `config.h`:

* `OPENAI_API_KEY`  
* `OPENAI_REALTIME_MODEL` (t.ex. gpt‑realtime‑preview)  
* `HA_BASE_URL` (https://ha.example.com)  
* `HA_TOKEN`  
* `MCP_PUBLIC_URL` (lämna tomt för client tools)  
* `DEVICE_NAME`  

## flöde

* `wakeword.c` lyssnar  
* `realtime_client.c` upprättar websocket till openai och strömmar pcm in/ut  
* om mcp är satt: session init med mcp; annars registreras klientverktyg  
* `mcp_bridge.c` kör verktyg mot ha  
* `audio_io.c` fångar/uppspelar ljud  
* `net.c` wifi + tls  

## proxy (valfritt)

om du vill köra lokalt utan att exponera ha: `tools/ws_proxy/server.js` som tar emot verktygsanrop och vidarebefordrar till ha.

## licens

mit