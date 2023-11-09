#include <DFRobotHCHOSensor.h>
#include <SoftwareSerial.h>
#include <SPI.h> // OLED display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SensorSerialPin 10 // Sensor
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
SoftwareSerial sensorSerial(SensorSerialPin,SensorSerialPin); // Sensor
DFRobotHCHOSensor hchoSensor(&sensorSerial);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
void setup() {
sensorSerial.begin(9600); // Sensor
sensorSerial.listen();
Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // OLED display initialize with the I2C addr0x3C
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print("Bereit zum Messen");
display.display();
}

void loop() {
if(hchoSensor.available()>0)
{
Serial.print(hchoSensor.uartReadPPM()); // Output measured values via serial monitor on the screen
Serial.println("ppm");
delay(4000); // Output measured values via OLED display
display.clearDisplay();
display.setTextSize(3);
display.setTextColor(WHITE);
display.setCursor(0,10);
display.print(hchoSensor.uartReadPPM());
display.println("ppm");
display.display();
delay(1000);
display.clearDisplay();
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
}
