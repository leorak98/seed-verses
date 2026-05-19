#include "SeedVerses.h"

SeedVerses::SeedVerses(const char* customUrl) {
    _baseUrl = customUrl;
}

void SeedVerses::setDebug(bool enable) {
    _debugEnabled = enable;
}

void SeedVerses::log(String message) {
    if (_debugEnabled) {
        Serial.println("[SeedVerses] " + message);
    }
}

// =========================================================================
// MÉTHODE OPTIMISÉE (Setup -> RAM)
// =========================================================================

bool SeedVerses::begin(String lang) {
    WiFiClientSecure client;
    client.setInsecure(); // HTTPS flexible sans maintenance de certificat
    
    HTTPClient http;
    String url = String(_baseUrl) + lang + "/verses.json?nocache=" + String(random(1000, 9999));
    
    log("Téléchargement initial : " + url);

    if (http.begin(client, url)) {
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            
            _localDoc.clear(); 
            DeserializationError error = deserializeJson(_localDoc, payload);
            
            http.end();
            if (!error) {
                log("Données JSON chargées en RAM avec succès !");
                return true;
            } else {
                log("Erreur de décodage JSON initial : " + String(error.c_str()));
                return false;
            }
        }
        http.end();
        log("Échec HTTP. Code : " + String(httpCode));
    } else {
        log("Impossible d'initialiser la connexion HTTP.");
    }
    return false;
}

BibleVerse SeedVerses::getLocalRandomVerse(String targetTag) {
    // Par défaut valid = false, et les chaînes sont vides
    BibleVerse selectedVerse = {"", "", "", false};
    
    // SÉCURITÉ : Si le document est vide ou n'est pas un tableau
    if (_localDoc.isNull() || !_localDoc.is<JsonArray>()) {
        log("Erreur : RAM vide. Appelez begin() d'abord.");
        return selectedVerse;
    }

    JsonArray array = _localDoc.as<JsonArray>();
    
    if (array.size() == 0) {
        log("Erreur : Le fichier JSON en mémoire est vide.");
        return selectedVerse;
    }

    std::vector<size_t> validIndexes;
    
    for (size_t i = 0; i < array.size(); i++) {
        JsonObject v = array[i].as<JsonObject>();
        if (targetTag == "") {
            validIndexes.push_back(i);
        } else if (v["tags"].is<JsonArray>()) { 
            JsonArray tags = v["tags"].as<JsonArray>();
            for (JsonVariant t : tags) {
                if (t.as<String>() == targetTag) {
                    validIndexes.push_back(i);
                    break;
                }
            }
        }
    }
    
    if (validIndexes.size() > 0) {
        int randomIndex = random(0, validIndexes.size());
        JsonObject finalVerse = array[validIndexes[randomIndex]].as<JsonObject>();
        
        selectedVerse.id = finalVerse["id"].as<String>();
        selectedVerse.text = finalVerse["text"].as<String>();
        selectedVerse.ref = finalVerse["ref"].as<String>();
        selectedVerse.valid = true;
    } else {
        log("Aucun verset ne correspond au tag demandé : " + targetTag);
    }
    
    return selectedVerse;
}

BibleVerse SeedVerses::getRandomVerse(String lang, String targetTag) {
    // Par défaut valid = false, les chaînes de caractères restent vides
    BibleVerse selectedVerse = {"", "", "", false};
    
    WiFiClientSecure client;
    client.setInsecure();
    
    HTTPClient http;
    String url = String(_baseUrl) + lang + "/verses.json?nocache=" + String(random(1000, 9999));
    
    if (http.begin(client, url)) {
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            JsonDocument tempDoc; 
            DeserializationError error = deserializeJson(tempDoc, payload);
            
            if (!error && tempDoc.is<JsonArray>()) {
                JsonArray array = tempDoc.as<JsonArray>();
                std::vector<size_t> validIndexes;
                
                for (size_t i = 0; i < array.size(); i++) {
                    JsonObject v = array[i].as<JsonObject>();
                    if (targetTag == "") {
                        validIndexes.push_back(i);
                    } else if (v["tags"].is<JsonArray>()) { 
                        JsonArray tags = v["tags"].as<JsonArray>();
                        for (JsonVariant t : tags) {
                            if (t.as<String>() == targetTag) {
                                validIndexes.push_back(i);
                                break;
                            }
                        }
                    }
                }
                
                if (validIndexes.size() > 0) {
                    int randomIndex = random(0, validIndexes.size());
                    JsonObject finalVerse = array[validIndexes[randomIndex]].as<JsonObject>();
                    
                    selectedVerse.id = finalVerse["id"].as<String>();
                    selectedVerse.text = finalVerse["text"].as<String>();
                    selectedVerse.ref = finalVerse["ref"].as<String>();
                    selectedVerse.valid = true;
                } else {
                    log("Aucun verset trouvé via l'API pour le tag : " + targetTag);
                }
            } else {
                log("Erreur de décodage JSON via l'API réseau.");
            }
        } else {
            log("Échec HTTP lors de l'appel API direct. Code : " + String(httpCode));
        }
        http.end();
    } else {
        log("Impossible de se connecter à l'API distante.");
    }
    return selectedVerse;
}