/*
 * uMQTTBroker demo for Arduino
 * 
 * The program starts a broker, subscribes to anything and publishs a topic every second.
 * Try to connect from a remote client and publish something - the console will show this as well.
 */

#include <ESP8266WiFi.h>

#include "uMQTTBroker.h"
#include "espconn.h"

/*
 * Your WiFi config here
 */
char ssid[] = "ssid";  	// your network SSID (name)
char pass[] = "password";	// your network password


unsigned int mqttPort = 1883;       // the standard MQTT broker port
unsigned int max_subscriptions = 30;
unsigned int max_retained_topics = 30;

/*
 * Data callback: called on any locally subscribed topic
 */

void data_callback(uint32_t *client /* we can ignore this */, const char* topic, uint32_t topic_len, const char *data, uint32_t lengh) {
  char topic_str[topic_len+1];
  os_memcpy(topic_str, topic, topic_len);
  topic_str[topic_len] = '\0';

  char data_str[lengh+1];
  os_memcpy(data_str, data, lengh);
  data_str[lengh] = '\0';

  Serial.println("received topic '"+(String)topic_str+"' with data '"+(String)data_str+"'");
}

/*
 * Authentication callback: called on any valid connction request
 * Returns true, if authorized
 */
 
bool auth_data_callback(const char* username, const char *password, struct espconn *pesp_conn){
  Serial.print("Connect from: ");
  Serial.print((String)pesp_conn->proto.tcp->remote_ip[0]+".");
  Serial.print((String)pesp_conn->proto.tcp->remote_ip[1]+".");
  Serial.print((String)pesp_conn->proto.tcp->remote_ip[2]+".");
  Serial.println((String)pesp_conn->proto.tcp->remote_ip[3]);

  Serial.println("Username/Pasword: "+(String)username+"/"+(String)password);

/*
 * Implement this,if you want to have username/password authentication
 */
//  if ((String)username == "root" &&  (String)password == "admin" ) {
//    return true;
//  }else{
//    return false;
//  }
  return true;
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // We start by connecting to a WiFi network
  Serial.println("Connecting to "+(String)ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: "+WiFi.localIP().toString());

/*
 * Register the callbacks
 */
  MQTT_server_onData(data_callback);
  MQTT_server_onAuth(auth_data_callback);

/*
 * Start the broker
 */
  Serial.println("Starting MQTT broker");
  MQTT_server_start(mqttPort, max_subscriptions, max_retained_topics);

/*
 * Subscribe to anything
 */
  MQTT_local_subscribe((unsigned char *)"#", 0);
}

int counter = 0;

void loop()
{
  String myData(counter++);

/*
 * Publish the counter value as String
 */
  MQTT_local_publish((unsigned char *)"/MyBroker/count", (unsigned char *)myData.c_str(), myData.length(), 0, 0);
  
  // wait a second
  delay(1000);
}
