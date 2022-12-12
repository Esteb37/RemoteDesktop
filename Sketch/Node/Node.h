#ifdef IS_NODE
#include "../Common/Comm.h"
#include "Handlers.h"
#include "ServerSetup.h"
#include "WifiSetup.h"

namespace NODE
{

  void setup()
  {
    Node.begin(115200);
    WF::setup();
    SERVER::setup();
  }

  void loop()
  {

    SERVER::https.handleClient();
    SERVER::http.handleClient();

    delay(1);

    if (Node.available() > 0)
    {
      String line = Node.readStringUntil('\n');
      CMD command = getCommand(line);
      if (command == CMD::SETSTAT)
      {
        status = getStat(line);
      }
      else if (command == CMD::FAILURE)
      {
        status = STAT::ERROR;
        error = getErr(line);
      }
    }
  }
}

#endif
