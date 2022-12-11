#include <Ino.h>
#include <Node.h>

#define NODE

void setup()
{
#ifdef NODE
    NODE::setup();
#else
    INO::setup();
#endif
}

void loop()
{
#ifdef NODE
    NODE::loop();
#else
    INO::loop();
#endif
}