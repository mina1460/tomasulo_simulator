#ifndef RSRV_H_
#define RSRV_H_

#include "includes.h"

class ReservationStation {
    private:
        string name;
        bool busy;
        string op;
        int Vj, Vk;
        string Qj, Qk;
        int address;
    public:
        ReservationStation (string p_name);

};

#endif