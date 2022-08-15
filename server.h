/*
 * server.h
 * Copyright Joseph R. Freeston (MIT License)
 * 
 * API Wrapper for CubeServer
 * 
 */


#ifndef CUBESERVER_SERVER_H
#define CUBESERVER_SERVER_H

#include <Arduino.h>

#include <ArduinoJson.h>

#ifdef ARDUINO_ARCH_ESP8266  // ESP8266 version--
# include <ESP8266WiFi.h>
# include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

# include <WiFiClient.h>
#elif ARDUINO_ARCH_ESP32  // ESP32 version--
# error "ESP32 is not *yet* supported by this library"
#else
# error "Unsupported Architecture."
#endif


#include "compile_time.h"


#define VERIFICATION_OK 1
#define VERIFICATION_FAILED -16



extern WiFiClientSecure client;
extern HTTPClient http;
extern uint8_t server_fingerprint[32];

typedef struct CubeServerConfig {
  String AP_SSID;
  String API_HOST;
  int API_PORT;
} CubeServerConfig;


const CubeServerConfig CUBESERVER_DEFAULT_CONFIG = {
  "CubeServer-API",
  "https://192.168.252.1",
  8081
};


typedef struct GameStatus {
  unsigned long int unix_time;
  int score;
  int strikes;
} GameStatus;

class CubeServer {
  private:
    const char * _team_name;
    const char * _team_secret;
    CubeServerConfig _conf;

    int _begin_client(String path);

  public:
    CubeServer(const char * team_name, const char * team_secret, const char * server_fingerprint, long unsigned int timestamp, CubeServerConfig conf);
    CubeServer(const char * team_name, const char * team_secret, const char * server_fingerprint, CubeServerConfig conf) : CubeServer(team_name, team_secret, server_fingerprint, UNIX_TIMESTAMP, CUBESERVER_DEFAULT_CONFIG) {};
    CubeServer(const char * team_name, const char * team_secret, const char * server_fingerprint) : CubeServer(team_name, team_secret, server_fingerprint, CUBESERVER_DEFAULT_CONFIG) {};

    // connect to the wifi access point:
    int connect(bool (*connection_wait_loop)());
    int connect();

    // get status:
    int get_status(GameStatus* stats_var);

};


#endif
