#ifndef TYPES_H
#define TYPES_H

const String CMD_PREFIX = "/";
const String STAT_PREFIX = "+";
const String ERR_PREFIX = "-";

enum CMD
{
    START,
    STOP,
    GETSTAT,
    SETSTAT,
    DONE,
    FAVICON,
    FAILURE,
    AK,
    SHUTOFF,
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
    HOSTING,
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
    command.trim();
    command.replace(CMD_PREFIX, "");
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
    else if (command == "AK")
    {
        return CMD::AK;
    }
    else if (command == "SHUTOFF")
    {
        return CMD::SHUTOFF;
    }
    else
    {
        return CMD::UNKNOWN;
    }
}

STAT stat(String stat)
{
    stat.trim();
    stat.replace(STAT_PREFIX, "");
    stat.toUpperCase();

    if (stat == "IDLE")
    {
        return STAT::IDLE;
    }
    else if (stat == "RUNNING")
    {
        return STAT::RUNNING;
    }
    else if (stat == "POWERED")
    {
        return STAT::POWERED;
    }
    else if (stat == "LOGGED")
    {
        return STAT::LOGGED;
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
    else if (stat == "HOSTING")
    {
        return STAT::HOSTING;
    }
    else
    {
        return STAT::ERROR;
    }
}

ERR err(String err)
{
    err.trim();
    err.replace(ERR_PREFIX, "");
    err.toUpperCase();

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
        return CMD_PREFIX + "START";
    case STOP:
        return CMD_PREFIX + "STOP";
    case GETSTAT:
        return CMD_PREFIX + "GETSTAT";
    case SETSTAT:
        return CMD_PREFIX + "SETSTAT";
    case DONE:
        return CMD_PREFIX + "DONE";
    case FAVICON:
        return CMD_PREFIX + "FAVICON.ICO";
    case CMD::FAILURE:
        return CMD_PREFIX + "FAILURE";
    case AK:
        return CMD_PREFIX + "AK";
    case SHUTOFF:
        return CMD_PREFIX + "SHUTOFF";
    default:
        return CMD_PREFIX + "UNKNOWN";
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
        return STAT_PREFIX + "IDLE";
    case RUNNING:
        return STAT_PREFIX + "RUNNING";
    case POWERED:
        return STAT_PREFIX + "POWERED";
    case LOGGED:
        return STAT_PREFIX + "LOGGED";
    case LOGON:
        return STAT_PREFIX + "LOGON";
    case WIFI:
        return STAT_PREFIX + "WIFI";
    case PARSEC:
        return STAT_PREFIX + "PARSEC";
    case HOSTING:
        return STAT_PREFIX + "HOSTING";
    case STAT::ERROR:
        return STAT_PREFIX + "ERROR";
    }
}

String str(ERR err)
{
    switch (err)
    {
    case NO_WIFI:
        return ERR_PREFIX + "NO_WIFI";
    case NO_SERIAL:
        return ERR_PREFIX + "NO_SERIAL";
    case NO_PARSEC:
        return ERR_PREFIX + "NO_PARSEC";
    case NONE:
        return ERR_PREFIX + "NONE";
    }
}

#endif