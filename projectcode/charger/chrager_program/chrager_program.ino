#include <ESP8266WiFi.h>
const char* ssid = "Kervolution";
const char* password = "amitamit";
int flag = 1;
int g=0;
int ledPin = 13; // GPIO13 D7
int value = LOW;
WiFiServer server(80);
//long lCnt = 0;
//unsigned long lStart;

void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  

  if (request.indexOf("timeval")!=-1){
  int r1=request.indexOf("timeval=");
  String tt1=request.substring(r1+8,r1+8+4);
  int r2=request.indexOf("Battery=");
  String tt2=request.substring(r2+8,r2+8+2);
  Serial.println(tt1);// show time as control
  Serial.println(tt2);//show battery as control
  g=tt2.toInt();
  
  if (g<40){
    value=LOW;
  }
  if ((g>=40) && (g<=70)){
    value=LOW;
    Serial.println("in if");
    }
  if (g>70){
    value = HIGH;
  }
  Serial.println(value);
 digitalWrite(ledPin, value);// connect on low
 delay(1000);
//  r1 is time to start and battery is percentage we want to start
//upower -d | grep -i "percentage" //to get charging in ubuntu
  }
  else{
    value = LOW;
  }
  
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>Automatic Charger</title></head>");
  client.println("<body><form method=\"GET\">");
  client.println("<label for=\"timeval\">timeval:</label>");
  client.println("<input type=\"text\" id=\"timeval\" name=\"timeval\" value=\"1000\"><br><br>"); 
  client.println("<label for=\"lname\">Battery:</label>");
  client.println("<input type=\"text\" id=\"Battery\" name=\"Battery\" value=\"10\"><br><br>");
  client.println("<input type=\"submit\" name=\"submit\"  value=\"Submit\">");
  client.println("</form></body></html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println(""); 
}
