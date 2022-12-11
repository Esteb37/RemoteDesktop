enum CMD
{
    START,
    STOP,
    STATUS,
    DONE,
    UNKNOWN,
};

CMD cmd(String command)
{
    if (command == "START")
    {
        return CMD::START;
    }
    else if (command == "STOP")
    {
        return CMD::STOP;
    }
    else if (command == "STATUS")
    {
        return CMD::STATUS;
    }
    else if (command == "DONE")
    {
        return CMD::DONE;
    }
    else
    {
        return CMD::UNKNOWN;
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
    case STATUS:
        return "STATUS";
    case DONE:
        return "DONE";
    case UNKNOWN:
        return "UNKNOWN";
    }
}

enum STAT
{
    IDLE,
    RUNNING,
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
