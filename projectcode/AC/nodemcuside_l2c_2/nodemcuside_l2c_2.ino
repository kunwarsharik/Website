#include <Wire.h>

//int val = 5;

#include <ESP8266WiFi.h>
const char* ssid = "Kervolution";
const char* password = "amitamit";
int flag = 1;
int g=0;
int ledPin = 13; // GPIO13 D7
int value = LOW;
WiFiServer server(80);


void setup() {
 Serial.begin(115200); /* begin serial for debug */
 delay(10);
 pinMode(ledPin, OUTPUT);
 digitalWrite(ledPin, LOW);
 Serial.println("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 Serial.println("WiFi connected");
 server.begin();
 Serial.println("Server started");
 Serial.print("Use this URL to connect: ");
 Serial.print("http://");
 Serial.print(WiFi.localIP());
 Serial.println("/");
 
 Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }    
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();    

  if (request.indexOf("device")!=-1){
    int r1=request.indexOf("device=");
    String tt1=request.substring(r1+7,r1+7+4);
    int r2=request.indexOf("Command=");
    String tt2=request.substring(r2+8,r2+8+2);
    Serial.println(tt1);// show time as control
    Serial.println(tt2);//show battery as control
    g=tt2.toInt();
 // g is val
    Wire.beginTransmission(8);  /* begin with device address 8 */
    Serial.print("if flag 1 val =");
    Serial.println(g);
    Wire.write(g);  /* sends hello string */
    Wire.endTransmission();/*stop transmitting val=Serial.read();if (val != -1){ */ 
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>IR Device Control</title></head>");
  client.println("<body><form method=\"GET\">");
  client.println("<label for=\"device\">Device:</label>");
  client.println("<input type=\"text\" id=\"device\" name=\"device\" value=\"1000\"><br><br>"); 
  client.println("<label for=\"command\">Command:</label>");
  client.println("<input type=\"text\" id=\"Command\" name=\"Command\" value=\"10\"><br><br>");
  client.println("<input type=\"submit\" name=\"submit\"  value=\"Submit\">");
  client.println("</form></body></html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
