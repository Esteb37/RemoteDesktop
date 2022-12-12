enum CMD
{
    START,
    STOP,
    GETSTAT,
    SETSTAT,
    DONE,
    FAVICON,
    LOGON,
    FAILURE,
    UNKNOWN,
};

enum Error
{
    NO_WIFI,
    NO_SERIAL,
    NO_PARSEC,
};

CMD cmd(String command)
{
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
    else if (command == "LOGON")
    {
        return CMD::LOGON;
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

String
str(CMD cmd)
{
    switch (cmd)
    {
    case START:
        return "START";
    case STOP:
        return "STOP";
    case GETSTAT:
        return "GETSTAT";
    case SETSTAT:
        return "SETSTAT";
    case DONE:
        return "DONE";
    case FAVICON:
        return "FAVICON";
    case CMD::FAILURE:
        return "FAILURE";
    case UNKNOWN:
        return "UNKNOWN";
    }
}

enum STAT
{
    IDLE,
    RUNNING,
    LOGON,
    WIFI,
    PARSEC,
    ERROR
};

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
