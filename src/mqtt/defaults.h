
//#ifndef MQTT_SSL_ENABLE
//#define MQTT_SSL_ENABLE	0
//#endif

//
// Change this to adjust memory consuption of one MQTT connection
// MQTT_BUF_SIZE is the max. size of pending inbound messages for one connection
// QUEUE_BUFFER_SIZE is the max. size of all pending outbound messages for one connection 
//

#ifndef MQTT_BUF_SIZE
#define MQTT_BUF_SIZE   1024
#endif

#ifndef QUEUE_BUFFER_SIZE
#define QUEUE_BUFFER_SIZE 2048
#endif

#ifndef MQTT_KEEPALIVE
#define MQTT_KEEPALIVE    120  /*seconds*/
#endif

#ifndef MQTT_RECONNECT_TIMEOUT
#define MQTT_RECONNECT_TIMEOUT  5 /*seconds*/
#endif

#define PROTOCOL_NAMEv311     /*MQTT version 3.11 compatible with https://eclipse.org/paho/clients/testing/*/

#ifndef MQTT_ID
#define MQTT_ID "ESPBroker"
#endif


