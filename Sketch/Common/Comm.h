#ifndef COMM_h
#define COMM_h

#include "Types.h"

#define Console Serial

#ifndef IS_NODE
#define Node Serial1
#else
#define Node Serial
#endif

String find(String req, String prefix)
{
    req.trim();
    int start = req.indexOf(prefix);
    int end = req.indexOf(" ", start);
    if (end == -1)
    {
        end = req.length();
    }
    return req.substring(start, end);
}

CMD getCommand(String req)
{
    return cmd(find(req, CMD_PREFIX));
}

STAT getStat(String req)
{
    return stat(find(req, STAT_PREFIX));
}

ERR getErr(String req)
{
    return err(find(req, ERR_PREFIX));
}

void nodeCommand(CMD command)
{
    Node.println(str(command));
}

void nodeStatus(STAT status)
{
    Node.println(str(CMD::SETSTAT) + " " + str(status));
}

void nodeFailure(ERR failure)
{
    Node.println(str(CMD::FAILURE) + " " + str(failure));
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