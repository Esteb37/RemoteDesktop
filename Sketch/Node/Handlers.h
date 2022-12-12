#ifdef IS_NODE

#ifndef HANDLERS_H
#define HANDLERS_H

#include "../Common/Comm.h"
#include "../Common/Types.h"
#include "Responses.h"

using namespace SERVER;

namespace NODE
{

    STAT status = STAT::IDLE;
    ERR error = ERR::NONE;

    void onStart(bool https = false)
    {
        if (status == STAT::IDLE)
        {
            status = STAT::RUNNING;
            sendOK(https);
            nodeCommand(CMD::START);
        }
        else
        {
            sendError("Already Running", https);
        }
    }

    void onStop(bool https = false)
    {
        if (status == STAT::RUNNING)
        {
            status = STAT::IDLE;
            sendOK(https);
            nodeCommand(CMD::STOP);
        }
        else
        {
            sendError("Already Stopped", https);
        }
    }

    void onGetStat(bool https = false)
    {
        if (status != STAT::ERROR)
        {
            sendOK(str(status), https);
        }
        else
        {
            sendError(str(error), https);
        }
    }
}

#endif

#endif