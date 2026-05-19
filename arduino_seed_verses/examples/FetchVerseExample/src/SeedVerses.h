#ifndef SeedVerses_h
#define SeedVerses_h

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <vector> // Ajouté par sécurité pour la gestion des index dynamiques

struct BibleVerse {
    String id;
    String text;
    String ref;
    bool valid;
};

class SeedVerses {
  public:
    // Le constructeur pointe par défaut sur le dépôt GitHub officiel open-source
    SeedVerses(const char* customUrl = "https://raw.githubusercontent.com/leorak98/seed-verses/main/data/");
    
    // Active ou désactive les logs automatiques dans le moniteur série (par défaut activé)
    void setDebug(bool enable);

    // --- MÉTHODE RAM ---
    bool begin(String lang);
    BibleVerse getLocalRandomVerse(String targetTag = "");

    // --- MÉTHODE RÉSEAU DIRECT ---
    // Ajout de la valeur par défaut "" pour targetTag pour uniformiser l'utilisation
    BibleVerse getRandomVerse(String lang, String targetTag = "");

  private:
    const char* _baseUrl;
    JsonDocument _localDoc;
    bool _debugEnabled = true;
    
    void log(String message);
};

#endif