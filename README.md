# 🌱 seed-verses

A collaborative, multilingual dataset of short and popular Bible verses in JSON format. Perfect for APIs, IoT, and applications.

---

- 🇲🇬 Tahirin-kevitra misy andinin-tsoratra masina fohy sy malaza amin'ny teny maro (JSON). Natao ho an'ny API, IoT ary rindrambaiko.
- 🇫🇷 Une collection collaborative et multilingue de versets bibliques courts au format JSON. Idéal pour les APIs, l'IoT et les applications.
- 🇺🇸 A collaborative, multilingual dataset of short and popular Bible verses in JSON format. Perfect for APIs, IoT, and apps.

---

## 🚀 Raw API Usage
You can fetch the raw JSON files directly via GitHub Raw links for your web developments or ESP32/ESP8266 boards:
- **Malagasy:** `https://raw.githubusercontent.com/leorak98/seed-verses/main/data/mg/verses.json`
- **French:** `https://raw.githubusercontent.com/leorak98/seed-verses/main/data/fr/verses.json`
- **English:** `https://raw.githubusercontent.com/leorak98/seed-verses/main/data/en/verses.json`

---

## 🛠️ Official Integrations

### 🤖 1. Embedded / Arduino / ESP... (`arduino_seed_verses`)
Perfect for IoT hardware projects such as thermal ticket printer dispensers.
*   **Features:** Initial payload preloading into RAM for zero-latency lookups, tag filtering, and automatic network failure fallback handlers to keep your device responsive.
*   👉 [View Arduino Documentation and Examples](./arduino_seed_verses/README.md)

### 📱 2. Mobile / Flutter (`flutter_seed_verses`)
Designed to seamlessly embed these verses into your Android and iOS mobile applications.

> ⏳ **Under Consideration / Call for Contributors**
> The Flutter package is not available yet. If you are a Dart/Flutter developer and want to design the architecture of this library (Offline-First local caching, asynchronous background sync, etc.), your help is highly welcome!
> 
> 👉 Feel free to open an **Issue** or a **Pull Request** to kickstart this module.

---

## 🤝 How to contribute?
We gladly accept contributions to enrich the dataset, fix typos, or add entirely new languages!

1. Navigate to your language folder inside the `data/` directory.
2. Add a short verse into the `verses.json` file while strictly respecting the existing structural schema.
3. If your language does not exist yet, simply spin up a new directory named after its standard ISO code (e.g., `es/` for Spanish).

### 🏷️ Supported Themes & Keywords (Tags):
To keep verses indexed and easily searchable, we use simple keywords. Feel free to use them or suggest new ones in your PRs:
`finoana` (faith), `fanantenana` (hope), `fitiavana` (love), `fiadanana` (peace), `fankaherezana` (encouragement), `fahasalamana` (health).

---

## 📄 License
This entire project (both datasets and integration source codes) is open-source and distributed under the **MIT License**.