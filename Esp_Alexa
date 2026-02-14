
#include <WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "Trunet_teknomindz 2.4"    
#define WIFI_PASS         "India@2026"
#define APP_KEY           "21f9338b-6e8c-477d-aa0d-b5233f9ea842"     
#define APP_SECRET        "578fbb46-0770-4c8d-ae62-5ed75833182d-26aa470f-57cd-4281-a060-f1afd92998ef"   
#define SWITCH_ID         "697dc2ab2c0599192aea4759"   
#define BAUD_RATE         9600                

#define RELAY_PIN         2                  
bool onPowerState(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN, state);             
  return true;                               
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);             
  WiFi.begin(WIFI_SSID, WIFI_PASS);           

  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];   
  mySwitch.onPowerState(onPowerState);                
  SinricPro.begin(APP_KEY, APP_SECRET);               
}

void loop() {
  SinricPro.handle();                        
}
