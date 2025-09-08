import express from "express";
import fetch from "node-fetch";
const app = express();
app.use(express.json());
app.post("/tool/get_state", async (req, res) => {
  const { entity_id, baseUrl, token } = req.body;
  const r = await fetch(`${baseUrl}/api/states/${entity_id}`, {
    headers: { Authorization: `Bearer ${token}` }
  });
  const j = await r.json();
  res.json(j);
});
app.post("/tool/call_service", async (req, res) => {
  const { domain, service, payload, baseUrl, token } = req.body;
  const r = await fetch(`${baseUrl}/api/services/${domain}/${service}`, {
    method: "POST",
    headers: {
      Authorization: `Bearer ${token}`,
      "Content-Type": "application/json"
    },
    body: JSON.stringify(payload || {})
  });
  const j = await r.json();
  res.json(j);
});
app.listen(8787);