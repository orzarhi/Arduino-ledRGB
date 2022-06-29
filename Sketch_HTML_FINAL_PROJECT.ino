/*
 Name:		Sketch_HTML_FINAL_PROJECT.ino
 Created:	1/14/2022 9:23:40 AM
 Author:	Or
*/

void setup() {
	wifi_setup();
	rgb_setup();
	RGB_color(0, 0, 0);
}


void loop() {
	wifi_loop();	
}
