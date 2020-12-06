#ifndef TOMASULU_H_
#define TOMASULU_H_

#include "Instruction.h"
#include "ReservationStation.h"

class Tomasulu{
    private: 
        int clock; 
        int cycles_count; 
        int instructions_count; 
        int misprediction_count; 
        int registers_count;


        vector <int> res_count;
        vector <int> cyc_count;

        vector <ReservationStation> load_RS;
        vector <ReservationStation> store_RS;
        vector <ReservationStation> beq_RS;
        vector <ReservationStation> jal_RS;
        vector <ReservationStation> add_RS;
        vector <ReservationStation> div_RS;

        int load_res_counter;
        int store_res_counter; 
        int beq_res_counter; 
        int jal_res_counter; 
        int add_res_counter; 
        int div_res_counter;


        int reg_file [REG_FILE_SIZE];           //values of the registers
        int reg_map  [REG_FILE_SIZE];           //mapping of renamed registers
        int reg_free_counter;       

        ifstream inst_mem; 

        vector<Instruction> instructions;
        

    public: 
        Tomasulu(int lrc, int src, int brc, int jrc, int arc, int drc, string file_path,  int lcc, int scc, int bcc, int jcc, int acc, int dcc);
        void extract_instructions();
        void rename_instructions();
        void print_instructions ();
        void check_RaW();
        void check_WaR();
        void check_WAW();

};

#endif
