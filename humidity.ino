/* humidity sensor and thermistor web server */

#include "etherShield.h"
#include "ETHER_28J60.h"
#include "math.h"

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};
static uint8_t ip[4] = {192, 168, 1, 15};
static uint16_t port = 80;

ETHER_28J60 e;

void setup()
{
  e.setup(mac, ip, port);
}

float vcc = 5.00; // measured vcc
float pad = 120000; // pad resistor value
float thermr = 100000; // thermistor nominal resistance

float thermistor(int rawADC) {
  long resistance;
  float temp;
  
  resistance = ((1024 * pad / rawADC) - pad);
  temp = resistance;
  temp = log(resistance);
  
  // calibration coefficients here are not 100% accurate as they are from the internets
  temp = 1 / (0.0006106983648 + (0.0002291898583 * temp) + (0.00000006859220227 * temp * temp * temp));
  temp = temp - 273.15;            

  return temp;
}

void loop()
{
  int reading;
  int i;
  float humidity;
  float temperature;
  int decimals;
  char *param;
  
  if (param = e.serviceRequest())
  {
    
    if (strcmp(param, "json") == 0) {
      // json
      e.print("{\n    \"humidity\": ");
      
      reading = 0;
      for (i = 0; i < 50 ; i++) {
        reading += analogRead(A0);
      }
      humidity = reading / 50.0;
      
      humidity = (humidity / 1024.0) * 5.00;
      humidity = (humidity * 35.220) - 27.577;
      e.print(humidity, 1);
      e.print(",\n    \"temperature\": ");
    
      reading = 0;
      for (i = 0; i < 50 ; i++) {
        reading += analogRead(A1);
      }
      temperature = reading / 50.0;
     
      temperature = thermistor((int)temperature);
      e.print(temperature, 1);
      e.print("\n}\n");
    } else {
      e.print("<html><body><font face=\"Verdana\"><center><h1>Andrew's Awesome Humidity Sensor</h1><hr/>");
      e.print("<table>");
    
      e.print("<tr><td align=\"right\">");
      reading = 0;
      for (i = 0; i < 50 ; i++) {
        reading += analogRead(A0);
      }
      humidity = reading / 50.0;
      
      e.print("Humidity:</td><td>");
      humidity = (humidity / 1024.0) * 5.00;
      humidity = (humidity * 35.220) - 27.577;
      e.print(humidity, 1);
      e.print("%</td></tr>");
    
      e.print("<tr><td align=\"right\">");
      reading = 0;
      for (i = 0; i < 50 ; i++) {
        reading += analogRead(A1);
      }
      temperature = reading / 50.0;

      e.print("Temperature:</td><td>");
      temperature = thermistor((int)temperature);
      e.print(temperature, 1);
      e.print("&deg;C</td></tr>");
    
      e.print("</table></center></font></body></html>");
    }
    
    e.respond();
  }
  delay(100);
}

