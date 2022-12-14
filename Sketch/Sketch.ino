#define IS_NODE

#include "Ino/Ino.h"
#include "Node/Node.h"

void setup()
{

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
