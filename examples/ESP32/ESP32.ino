#include <hebocontroller.h>

Hebobot hebobot("hebobot #1", 115200);
Hebocontroller controller(hebobot);

void setup() {
  hebobot.init();
  controller.init();
}

void loop() {
  controller.poll();
}
