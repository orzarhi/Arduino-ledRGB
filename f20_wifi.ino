#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

IPAddress    apIP(55, 55, 55, 55);
const char* ssid = "orZWiFi"; // שם הרשת שיוצג
const char* password = "88888888";// הסיסמה לרשת אם נרצה להשתמש בה 
ESP8266WebServer server(80);


void wifi_setup()
{
	WiFi.mode(WIFI_AP_STA);
	WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00   
	WiFi.softAP(ssid);
	//WiFi.softAP(ssid,password); // עם סיסמא
	server.on("/", handleRoot);
	server.onNotFound(handleNotFound);
	server.begin();
}

void handleRoot()
{
   	int R,G,B;	
	if (server.arg("dirOn") == "O")
	{
    	String r = server.arg("RL");
	 	R = r.toInt();

		String g = server.arg("GL");
		G = g.toInt();	

		String b = server.arg("BL");
		B = b.toInt();		

		RGB_color(R, G, B);				
	}
	if (server.arg("dirOf") == "Of")
	{		
		RGB_color(0, 0,0);
	}

	char html[2000] = "";

	strcat(html, "<!DOCTYPE html>");
	strcat(html, "<html>");
	strcat(html, "<head>");
	strcat(html, "<meta charset=\"utf-8\" />");
	strcat(html, "<title>Final project</title>");
	strcat(html, "<style>");
	strcat(html, "body{");
	strcat(html, "background-image: linear-gradient(120deg,#f6d365,#fda085);");
	strcat(html, "margin: 0;");
	strcat(html, "padding: 0;");
	strcat(html, "box-sizing: border-box;");
	strcat(html, "display: grid;");
	strcat(html, "place-items: center;");
	strcat(html, "height: 100vh;}");
	strcat(html, ".main{");
	strcat(html, "height: 430px;");
	strcat(html, "width: 280px;");
	strcat(html, "background: #333;");
	strcat(html, "border-radius: 10px;");
	strcat(html, "display: grid;");
	strcat(html, "place-items: center;");
	strcat(html, "color: #fff;");
	strcat(html, "font-family: Verdana;}");
	strcat(html, ".ON{");
	strcat(html, "background-color: forestgreen;");
	strcat(html, "width: 55%;");
	strcat(html, "margin: 5%;}");
	strcat(html, ".OFF{");
	strcat(html, "background-color: darkred;");
	strcat(html, "width: 55%;");
	strcat(html, "margin: 5%;}");
	strcat(html, ".box{");
	strcat(html, "text-align: center;}");
	strcat(html, "</style>");
	strcat(html, "</head>");
	strcat(html, "<body>");
	strcat(html, "<form class=\"main\">");
	strcat(html, "<h1>Select Color:</h1>");
	strcat(html, "<input type=\"color\" id=\"myColor\"/>");
	strcat(html, "<p>R:<input name=\"RL\" type=\"text\"   id=\"boxR\" class=\"box\" /> </p>");
	strcat(html, "<p>G:<input name=\"GL\" type=\"text\"   id=\"boxG\" class=\"box\" /></p>");
	strcat(html, "<p>B:<input name=\"BL\" type=\"text\"   id=\"boxB\" class=\"box\" /> </p>");
	strcat(html, "<button name=\"dirOn\" value=\"O\"  onclick=\"myFunction()\" class=\"ON\">On</button>");
	strcat(html, "<button name=\"dirOf\" value=\"Of\" onclick=\"clearAll()\"   class=\"OFF\">Off</button>");
	strcat(html, "</form>");
	strcat(html, "<script>");
	strcat(html, "function myFunction(){");
	strcat(html, "var x = document.getElementById(\"myColor\").value;");
	strcat(html, "var r = parseInt(x.slice(1, 3), 16),");
	strcat(html, "g = parseInt(x.slice(3, 5), 16),");
	strcat(html, "b = parseInt(x.slice(5, 7), 16);");
	strcat(html, "document.getElementById(\"boxR\").value = r;");
	strcat(html, "document.getElementById(\"boxG\").value = g;");
	strcat(html, "document.getElementById(\"boxB\").value = b;}");
	strcat(html, "function clearAll(){");
	strcat(html, "document.getElementById(\"boxR\").value = \"Off. Try again\";");
	strcat(html, "document.getElementById(\"boxG\").value = \"Off. Try again\";");
	strcat(html, "document.getElementById(\"boxB\").value = \"Off. Try again\";}");
	strcat(html, "</script>");
	strcat(html, "</body>");
	strcat(html, "</html>");

	server.send(200, "text/html", html);
}

void wifi_loop()
{
	server.handleClient();// server is defined at this tab
	delay(10);
}
void handleNotFound()
{
	String message = "File Not Foundnn";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";

	for (uint8_t i = 0; i < server.args(); i++)
	{
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
}