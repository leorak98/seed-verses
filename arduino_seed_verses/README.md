# 🤖 SeedVerses Arduino Library

A lightweight, robust, and non-blocking C++ library for ESP32 and ESP8266 to fetch and filter multilingual Bible verses from the **seed-verses** open-source dataset via HTTPS.

Optimized for IoT projects like smart displays, automated ticket dispensers, thermal printers, e-paper dashboards, or daily verse clocks.

---

# ✨ Features

- **Two Modes**
  - Fetch verses directly from the network
  - Or preload the entire dataset into RAM for ultra-fast offline-like access

- **Fast Local Selection**
  - Instant verse retrieval after initialization
  - Perfect for physical buttons, ticket dispensers, or display rotations

- **Tag Filtering**
  - Retrieve verses by category/tags like:
    - `finoana`
    - `fankaherezana`
    - `fanantenana`
    - `vavaka`

- **Memory Safe**
  - Protection against:
    - network failures
    - empty datasets
    - malformed JSON
    - invalid indexes

- **Non-Blocking Friendly**
  - Designed to minimize latency during `loop()`

- **Insecure HTTPS Support**
  - Works without worrying about:
    - GitHub certificate rotation
    - ESP32 time synchronization issues

- **Custom JSON Sources**
  - Easily switch between:
    - official repository
    - GitHub forks
    - local APIs
    - self-hosted endpoints

- **Multilingual**
  - Supports:
    - Malagasy (`mg`)
    - French (`fr`)
    - English (`en`)

---

# 🛠️ Installation

## Via Arduino IDE (Recommended)

1. Open **Arduino IDE**
2. Go to:

```text
Sketch → Include Library → Manage Libraries...
```

3. Search for:

```text
SeedVerses
```

4. Click **Install**

---

## Manual Installation

1. Download this repository as a `.zip`
2. Open Arduino IDE
3. Go to:

```text
Sketch → Include Library → Add .ZIP Library...
```

4. Select the downloaded zip file

---

# ⚠️ Dependency

This library requires:

- **ArduinoJson v7+** by Benoit Blanchon

If you install through the Arduino Library Manager, the dependency is installed automatically.

---

# 🚀 Quick Start (RAM Mode)

This is the recommended mode for production.

The dataset is downloaded once during `setup()` and stored in RAM.  
Verse selection becomes instantaneous inside `loop()` without additional network latency.

```cpp
#include <WiFi.h>
#include <SeedVerses.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

SeedVerses bible;

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi Connected!");

    // Load Malagasy verses into RAM
    if (bible.begin("mg")) {
        Serial.println("Verses loaded successfully!");
    } else {
        Serial.println("Failed to load verses.");
    }
}

void loop() {

    Serial.println("\n--- Random Verse ---");

    // Get instant random verse from RAM
    // Make the parameter empty if you want random element from all verses without specifying tag
    BibleVerse v = bible.getLocalRandomVerse("finoana");

    if (v.valid) {
        Serial.print("ID:   ");
        Serial.println(v.id);

        Serial.print("Text: ");
        Serial.println(v.text);

        Serial.print("Ref:  ");
        Serial.println(v.ref);
    } else {
        Serial.print("Error: ");
        Serial.println(v.text);
    }

    delay(10000);
}
```

---

# 🌐 Network Mode Example

This mode fetches directly from the internet on every request.

Useful when:
- RAM is limited
- You always want fresh remote data

```cpp
#include <WiFi.h>
#include <SeedVerses.h>

SeedVerses bible;

void setup() {
    Serial.begin(115200);
}

void loop() {

    BibleVerse verse = bible.getRandomVerse("fr", "espoir");

    if (verse.valid) {
        Serial.println(verse.text);
        Serial.println(verse.ref);
    } else {
        Serial.println("Failed to fetch verse");
    }

    delay(15000);
}
```

---

# 📖 API Reference

---

## Constructor

### `SeedVerses(const char* customUrl = "...")`

Creates a new SeedVerses instance.s

### Default URL

```cpp
SeedVerses bible;
```

### Custom Source

```cpp
SeedVerses bible(
    "https://raw.githubusercontent.com/username/repo/main/data/"
);
```

Useful for:
- private repositories
- local servers
- custom APIs
- offline LAN deployments

---

## Debug Mode

### `void setDebug(bool enable)`

Enable or disable internal logs.

```cpp
bible.setDebug(false);
```

Default: `true`

---

## Initialize RAM Mode

### `bool begin(String lang)`

Downloads and stores the dataset into RAM.

### Supported Languages

| Code | Language |
|---|---|
| `mg` | Malagasy |
| `fr` | French |
| `en` | English |

### Example

```cpp
bible.begin("mg");
```

Returns:
- `true` on success
- `false` on failure

---

## Local Random Verse

### `BibleVerse getLocalRandomVerse(String targetTag = "")`

Returns a random verse from RAM.

### Example

```cpp
BibleVerse v = bible.getLocalRandomVerse("fankaherezana");
```

If no tag is provided:

```cpp
BibleVerse v = bible.getLocalRandomVerse();
```

Safe against:
- uninitialized RAM
- empty datasets
- invalid selections

---

## Network Random Verse

### `BibleVerse getRandomVerse(String lang, String targetTag = "")`

Fetches a verse directly from the remote server.

### Example

```cpp
BibleVerse v = bible.getRandomVerse("en", "hope");
```

⚠️ This method performs a network request every call.

---

# 📋 BibleVerse Structure

Every method returns a `BibleVerse` structure.

```cpp
BibleVerse v;
```

| Property | Type | Description |
|---|---|---|
| `v.id` | `String` | Unique verse identifier |
| `v.text` | `String` | Verse content |
| `v.ref` | `String` | Bible reference |
| `v.valid` | `bool` | Success state |

---

# 🧠 Example Output

```text
--- Random Verse ---

ID:   152
Text: Fa toy izao no nitiavan’Andriamanitra izao tontolo izao...
Ref:  Jaona 3:16
```

---

# 💡 Recommended Use Cases

- ESP32 thermal printers
- E-paper Bible displays
- Daily verse clocks
- WiFi kiosks
- LED matrix verse boards
- IoT notification systems
- Smart church displays
- Offline devotional devices

---

# 🔒 HTTPS Notes

This library intentionally uses insecure HTTPS mode to improve compatibility on embedded devices.

Advantages:
- No certificate maintenance
- No RTC synchronization requirement
- Fewer SSL connection failures on ESP32/ESP8266

Ideal for lightweight IoT deployments.

---

# 📄 License

This project is open-source software licensed under the **MIT License**.
