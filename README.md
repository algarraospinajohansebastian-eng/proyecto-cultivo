An IoT-based crop monitoring solution that connects an ESP32 microcontroller with a web interface to track environmental data in real time.

The ESP32 collects telemetry from various sensors (including soil pH, humidity, and temperature) and sends the readings over Wi-Fi to a Node.js backend via HTTP endpoints.
The web frontend, built with HTML and JavaScript, dynamically updates to display real-time agricultural insights accessible from any standard web link.
////
Este proyecto es un sistema de monitoreo de cultivos, conectando una web a un esp32, puede monitorear con sensores de diferentes tipos como ph, humedad, temperatura, etc... y a traves del
codigo de backend en node.js y la esp32 conectada a una red wifi con internet, enviará los datos de los sensores al backend a traves de una ruta http, y los datos se actualizan en el front
de html y javascript para mostrarse desde un link normal y en tiempo real
