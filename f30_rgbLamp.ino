#define LED_R D1
#define LED_G D2
#define LED_B D3

void rgb_setup()
{
	pinMode(LED_R, OUTPUT);
	pinMode(LED_G, OUTPUT);
	pinMode(LED_B, OUTPUT);
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
	analogWrite(LED_R, red_light_value);
	analogWrite(LED_G, green_light_value);
	analogWrite(LED_B, blue_light_value);
}
