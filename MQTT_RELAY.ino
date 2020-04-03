#include <WiFi.h>
#include <PubSubClient.h>

char bulbstate[5];
int b=90;
 
const char* ssid = "sky";
const char* password =  "akash123";
const char* mqttServer = "tailor.cloudmqtt.com";
const int mqttPort =  13689;
const char* mqttUser = "bvuxmfyf";
const char* mqttPassword = "TEEHOMrPi7eP";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
  
  pinMode(D7,OUTPUT);
  digitalWrite(D7,HIGH);
  Serial.begin(115200);
 
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
      client.subscribe("lightstatus");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }

  String a= "distance : ";
  a+=b;
  char buf[20];
  a.toCharArray(buf,20);
  //Serial.println(buf);
  //client.publish("python/test",buf);
  //client.subscribe("lightstatus");
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) 
  {
    bulbstate[i]=(char)payload[i];
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() 
{
  client.loop();
  if(bulbstate[0] == '1')
  {
    digitalWrite(D7,HIGH);
  }
  else if(bulbstate[0] == '0')
  {
    digitalWrite(D7,LOW);
  }//client.publish("esp/test", "Hello from ESP8266");

}
