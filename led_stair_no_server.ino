#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "MQTT.h"
#include "Range.h"

double val;
bool go_backwards = false;
int led = -1;
int prev_led = -1;

int light_it_up(double dist, bool backwards, int number_of_leds, double max_dist) {
  int n = round(dist/(max_dist/(number_of_leds+1)));
  if (backwards) return number_of_leds-n+1;
  return n;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  range_init();
  WIFI_init(MODE_AP);
  MQTT_init();

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  mqtt_client.loop();
  val = get_range();
  led = light_it_up(val, go_backwards, 6, 210.0);
  String my_topic = String("buda/leds/")+String(led);
  mqtt_client.publish(my_topic.c_str(), String("100255100").c_str());
  if (led != prev_led) {
    String my_prev_topic = String("buda/leds/")+String(prev_led);
    mqtt_client.publish(my_prev_topic.c_str(), String("000000000").c_str());
  }
  prev_led = led;
  delay(1000);
}
