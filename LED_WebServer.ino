#include<ESP8266WiFi.h>

const char* ssid = "anthanh";
const char* password = "25041999";
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(10);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(16, OUTPUT);
  digitalWrite(16, 0);
  digitalWrite(5, 0);
  digitalWrite(4, 0);
  digitalWrite(0, 0);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connectting to");
  Serial.println(ssid);

  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  //START the server
  server.begin();
  Serial.println("Server started");
  //Print the IP address
  Serial.print("Use the URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.print("/");
}

void loop()
{
  //Check if a client has connected
  WiFiClient client = server.available();
  if(!client)
  {
    return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  //Match the request
  if(request.indexOf("/light1on") > 0)
  {
    digitalWrite(5, 1);
  }
  if(request.indexOf("/light1off") > 0)
  {
    digitalWrite(5, 0);
  }
  //
    if(request.indexOf("/light2on") > 0)
  {
    digitalWrite(4, 1);
  }
  if(request.indexOf("/light2off") > 0)
  {
    digitalWrite(4, 0);
  }
  //
    if(request.indexOf("/light3on") > 0)
  {
    digitalWrite(0, 1);
  }
  if(request.indexOf("/light3off") > 0)
  {
    digitalWrite(0, 0);
  }
  //
    if(request.indexOf("/light4on") > 0)
  {
    digitalWrite(16, 1);
  }
  if(request.indexOf("/light4off") > 0)
  {
    digitalWrite(16, 0);
  }

  //Set ledPin according tho request
  //ditalWrite(ledPin,vaule);

  //Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // do not forhet this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes'/>");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent'/>");
  client.println("</head>");
  client.println("<body bgcolor = \"#f7e6ec\">");
  client.println("<hr/><hr>");
  client.println("<h4><center> CONTROL ELECTRONICS FOR ESP8266 </center></h4>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><hr>");
  client.println("<center>");
  client.println("Devive 1");
  client.println("<a href=\"/light1on\"\"><button>Turn On</button></a>");
  client.println("<a href=\"/light1off\"\"><button>Turn Off</button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  //
  client.println("Devive 2");
  client.println("<a href=\"/light2on\"\"><button>Turn On</button></a>");
  client.println("<a href=\"/light2off\"\"><button>Turn Off</button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  //
  client.println("Devive 3");
  client.println("<a href=\"/light3on\"\"><button>Turn On</button></a>");
  client.println("<a href=\"/light3off\"\"><button>Turn Off</button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  //
   client.println("Devive 4");
  client.println("<a href=\"/light4on\"\"><button>Turn On</button></a>");
  client.println("<a href=\"/light4off\"\"><button>Turn Off</button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  //
  client.println("<table border=\"5\">");
  client.println("<tr>");
  //
  if(digitalRead(5))
  {
    client.print("<td>Light 1 is ON</td>");
  }
  else
  {
    client.print("<td>Light 1 is OFF</td>");
  }
  client.println("<br />");
  //
  if(digitalRead(4))
  {
    client.print("<td>Light 2 is ON</td>");
  }
  else
  {
    client.print("<td>Light 2 is OFF</td>");
  }
  client.println("</tr>");
  client.println("<tr>");
  //
  if(digitalRead(0))
  {
    client.print("<td>Light 3 is ON</td>");
  }
  else
  {
    client.print("<td>Light 3 is OFF</td>");
  }
  //
  if(digitalRead(16))
  {
    client.print("<td>Light 4 is ON</td>");
  }
  else
  {
    client.print("<td>Light 4 is OFF</td>");
  }
  client.println("</tr>");
  client.println("</table>");
  client.println("</center>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");

}
