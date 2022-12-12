#ifndef COMM_h
#define COMM_h

#include "Types.h"

#define Console Serial

#ifndef IS_NODE
#define Node Serial1
#else
#define Node Serial
#endif

CMD getCommand(String req)
{
    int start = req.indexOf("/");
    int end = req.indexOf(" ", start);
    return cmd(req.substring(start + 1, end));
}

STAT getStat(String req)
{
    int start = req.indexOf("+");
    int end = req.indexOf(" ", start);
    return stat(req.substring(start + 1, end));
}

ERR getErr(String req)
{
    int start = req.indexOf("+");
    int end = req.indexOf(" ", start);
    return err(req.substring(start + 1, end));
}

void nodeCommand(CMD command)
{
    Node.println(str(command));
}

void nodeStatus(STAT status)
{
    Node.println(str(CMD::SETSTAT) + "+" + str(status));
}

void nodeFailure(ERR failure)
{
    Node.println(str(CMD::FAILURE) + "+" + str(failure));
}

CMD readConsole()
{
    if (Console.available() > 0)
    {
        String line = Console.readStringUntil('\n');
        line.trim();
        if (line.length() > 0)
        {
            return getCommand(line);
        }
    }

    return CMD::UNKNOWN;
}

CMD readNode()
{
    if (Node.available() > 0)
    {
        String line = Node.readStringUntil('\n');
        line.trim();
        if (line.length() > 0)
        {
            return getCommand(line);
        }
    }

    return CMD::UNKNOWN;
}

#endif