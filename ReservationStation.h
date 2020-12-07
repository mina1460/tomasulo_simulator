#ifndef RSRV_H_
#define RSRV_H_

#include "includes.h"

class ReservationStation {
    private:
        string name;
        int id;
        bool busy;
        string op;
        int Vj, Vk;
        int Qj, Qk;
        int address;
    public:
        ReservationStation (string p_name);
        bool get_busy ();

        int get_Vj ();
        int get_Vk ();
        int get_Qj ();
        int get_Qk ();

        void set_Vj (int p_vj);
        void set_Vk (int p_vk);
        void set_Qj (int p_qj);
        void set_Qk (int p_qk);
        

};

#endif