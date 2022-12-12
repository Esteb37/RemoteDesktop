#define IS_NODE

#include "Ino.h"
#include "Node.h"

void setup()
{
    Node.begin(115200);
    Console.begin(9600);

#ifdef IS_NODE
    NODE::setup();
#else
    INO::setup();
#endif
}

void loop()
{
#ifdef IS_NODE
    NODE::loop();
#else
    INO::loop();
#endif
}
