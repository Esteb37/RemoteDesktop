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

    void onStart(bool using_https = false)
    {
        if (status == STAT::IDLE)
        {
            status = STAT::RUNNING;
            sendOK(using_https);
            nodeCommand(CMD::START);
        }
        else
        {
            sendError("Already Running", using_https);
        }
    }

    void onStop(bool using_https = false)
    {
        if (status != STAT::IDLE)
        {
            status = STAT::IDLE;
            sendOK(using_https);
            nodeCommand(CMD::STOP);
        }
        else
        {
            sendError("Already Stopped", using_https);
        }
    }

    void onGetStat(bool using_https = false)
    {
        if (status != STAT::ERROR)
        {
            sendOK(str(status), using_https);
        }
        else
        {
            sendError(str(error), using_https);
        }
    }
}

#endif

#endif