#include <WiFi.h>
#include <SeedVerses.h>

const char* ssid = "VOTRE_WIFI_SSID";
const char* password = "VOTRE_WIFI_PASSWORD";

SeedVerses bible;

void setup() {
    Serial.begin(115200);
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { delay(500); }
    Serial.println("\nWiFi Connecté !");

    bool success = bible.begin("mg");
    if (success) {
        Serial.println("Pré-chargement réussi.");
    } else {
        Serial.println("Échec du pré-chargement.");
    }
}

void loop() {
    Serial.println("\n--- Nouveau tirage depuis la RAM (Chaque 5 secondes) ---");
    
    // C'est instantané, pas de requête HTTP ici !
    // Mettre le parametre vide pour tous les versets sans spéficier le tag
    BibleVerse v = bible.getLocalRandomVerse("finoana");
    
    if (v.valid) {
        Serial.println(v.text + " (" + v.ref + ")");
    } else {
        Serial.println("Erreur RAM : " + v.text);
        
        // REPLI (FALLBACK) : Si la RAM est vide ou a échoué au setup, 
        // on peut utiliser l'ancienne méthode réseau en secours !
        Serial.println("Tentative de secours via le réseau...");
        BibleVerse secours = bible.getRandomVerse("mg", "finoana");
        if (secours.valid) {
            Serial.println(secours.text + " (" + secours.ref + ")");
        }
    }

    delay(5000); 
}