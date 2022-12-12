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
