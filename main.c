#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const int trigPin = 12;
const int echoPin = 14;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
const char* ssid = "S10";                   // wifi ssid
const char* password =  "12345678";         // wifi password
const char* mqttServer = "192.168.102.100";    // IP adress Raspberry Pi
const int mqttPort = 1883;
const char* mqttUser = "msherbinii";      // if you don't have MQTT Username, no need input
const char* mqttPassword = "ProjectNetworks2002";  // if you don't have MQTT Password, no need input

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {

    Serial.begin(9600); // Starts the serial communication
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");

    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);

    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");

        if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

            Serial.println("connected");

        } else {

            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);

        }
        // MQTT
    const char* mqtt_server = "192.168.0.8";  // IP of the MQTT broker
    const char* ultrasonic_1 = "room/sensors/ultrasonic1";
    const char* ultrasonic_2 = "room/sensors/ultrasonic2";
    const char* mqtt_username = "msherbini"; // MQTT username
    const char* mqtt_password = "msherbini"; // MQTT password
    const char* clientID = "client_room"; // MQTT client ID
    }

//  client.publish("esp8266", "Hello Raspberry Pi");
//  client.subscribe("esp8266");

}

void callback(char* topic, byte* payload, unsigned int length) {

    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }

    Serial.println();
    Serial.println("-----------------------");

}

void loop() {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distanceCm = duration * SOUND_VELOCITY/2;
    String x= String('distanceCm');



    // Prints the distance on the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);

    delay(1000);
    client.publish("esp8266", "x");
    client.subscribe("esp8266");
    delay(300);
    client.loop();