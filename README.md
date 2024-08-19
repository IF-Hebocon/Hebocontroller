# Hebocontroller

## Installation
1. In GitHub Releases auswählen -> [Releases](https://github.com/IF-Hebocon/Hebocontroller/releases)
2. Die Version auswählen
3. Den Anhang hebocontroller.zip herunterladen
4. Zip als Library in der ArduinoIDE hinzufügen: _Sketch -> Include Library -> Add .ZIP Library..._

# Beispiele 
In der Arduino IDE kann das Beispielskript über den Menüpunkt _File -> Examples -> Hebocontroller_ geladen werden

# PlatformIO
```ini
[env:nodemcu-32s]
platform = espressif32
board = nodemcu-32s
framework = arduino
lib_extra_dirs = ~/Documents/Arduino/libraries/hebocontroller
build_flags = -D ARDUINO_NODEMCU_32S=1
```
