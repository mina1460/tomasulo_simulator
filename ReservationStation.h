#ifndef RSRV_H_
#define RSRV_H_

#include "includes.h"

class ReservationStation {
    private:
        
    public:
        ReservationStation (string p_name);
        ~ReservationStation ();
        // bool get_busy ();

        // int get_Vj ();
        // int get_Vk ();
        // int get_Qj ();
        // int get_Qk ();

        // void set_Vj (int p_vj);
        // void set_Vk (int p_vk);
        // void set_Qj (int p_qj);
        // void set_Qk (int p_qk);
        void resetRS();

        string name;
        int IDj, IDk;
        bool busy;
        string op;
        int Vj, Vk;
        int imm;
        int Qj, Qk;
        int address;
        int instruction_number; 
        bool ready; 
        int result;
};

#endif