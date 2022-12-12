#ifndef TYPES_H
#define TYPES_H

enum CMD
{
    START,
    STOP,
    GETSTAT,
    SETSTAT,
    DONE,
    FAVICON,
    FAILURE,
    UNKNOWN,
};

enum STAT
{
    IDLE,
    RUNNING,
    POWERED,
    LOGGED,
    LOGON,
    WIFI,
    PARSEC,
    ERROR
};

enum ERR
{
    NO_WIFI,
    NO_SERIAL,
    NO_PARSEC,
    NONE,
};

CMD cmd(String command)
{
    command = "/" + command;

    command.toUpperCase();

    if (command == "START" || command == "RUN")
    {
        return CMD::START;
    }
    else if (command == "STOP" || command == "PAUSE")
    {
        return CMD::STOP;
    }
    else if (command == "GETSTAT" || command == "STATUS")
    {
        return CMD::GETSTAT;
    }
    else if (command == "SETSTAT" || command == "SETSTATUS")
    {
        return CMD::SETSTAT;
    }
    else if (command == "DONE")
    {
        return CMD::DONE;
    }
    else if (command == "FAVICON" || command == "FAVICON.ICO")
    {
        return CMD::FAVICON;
    }
    else if (command == "FAILURE")
    {
        return CMD::FAILURE;
    }
    else
    {
        return CMD::UNKNOWN;
    }
}

STAT stat(String stat)
{
    if (stat == "IDLE")
    {
        return STAT::IDLE;
    }
    else if (stat == "RUNNING")
    {
        return STAT::RUNNING;
    }
    else if (stat == "LOGON")
    {
        return STAT::LOGON;
    }
    else if (stat == "WIFI")
    {
        return STAT::WIFI;
    }
    else if (stat == "PARSEC")
    {
        return STAT::PARSEC;
    }
    else
    {
        return STAT::ERROR;
    }
}

ERR err(String err)
{
    if (err == "NO_WIFI")
    {
        return ERR::NO_WIFI;
    }
    else if (err == "NO_SERIAL")
    {
        return ERR::NO_SERIAL;
    }
    else if (err == "NO_PARSEC")
    {
        return ERR::NO_PARSEC;
    }
    else
    {
        return ERR::NONE;
    }
}

String str(CMD cmd)
{
    String command = "/";
    switch (cmd)
    {
    case START:
        return command + "START";
    case STOP:
        return command + "STOP";
    case GETSTAT:
        return command + "GETSTAT";
    case SETSTAT:
        return command + "SETSTAT";
    case DONE:
        return command + "DONE";
    case FAVICON:
        return command + "FAVICON.ICO";
    case CMD::FAILURE:
        return command + "FAILURE";
    default:
        return command + "UNKNOWN";
    }
}

String str_low(CMD cmd)
{
    String command = str(cmd);
    command.toLowerCase();
    return command;
}

String str(STAT stat)
{
    switch (stat)
    {
    case IDLE:
        return "IDLE";
    case RUNNING:
        return "RUNNING";
    case ERROR:
        return "ERROR";
    }
}

String str(ERR err)
{
    switch (err)
    {
    case NO_WIFI:
        return "NO_WIFI";
    case NO_SERIAL:
        return "NO_SERIAL";
    case NO_PARSEC:
        return "NO_PARSEC";
    case NONE:
        return "NONE";
    }
}

#endif