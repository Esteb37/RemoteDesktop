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

    // end is any non-alphanumeric character after the prefix
    int end = start + prefix.length();
    while (end < req.length() && isalnum(req[end]))
    {
        end++;
    }

    if (start == -1 || end == -1)
    {
        return "";
    }

    start += prefix.length();
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

void consoleCommand(CMD command)
{
    Console.println(str(command));
}

void consoleStatus(STAT status)
{
    Console.println(str(CMD::SETSTAT) + " " + str(status));
}

void consoleFailure(ERR failure)
{
    Console.println(str(CMD::FAILURE) + " " + str(failure));
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