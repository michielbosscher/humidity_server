This is a quick and dirty humidity sensor and thermistor reading web server. It just takes the humidity sensor and thermistor readings and responds to http requests with them. It also supports json output. If I keep it online you can find it running at http://xorrbit.no-ip.org:1337/

The sensor I'm using is quite old and may not be accurate. I also didn't have proper calibration data for the thermistor so the temps are way off, but you can see it change anyways. Once I get three decent measurements I can create proper coefficients to toss into the steinhart-hart equations I'm using to translate the resistance into a temperature, but until then the values will be off a bit.

It uses the enc28j60 and ethershield libraries from http://trollmaker.com/article11/arduino-1-0-with-enc28j60-ethernet-shield-v1-1
