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
        bool done;

        vector <int> res_count;             //reservation stations count
        vector <int> cyc_count;             //cycles taken to execute instruction
        vector <int> res_counter;           //currently used reservation stations

        vector < vector<ReservationStation*>> RS;

        int reg_file [REG_FILE_SIZE];           //values of the registers
        int reg_map  [REG_FILE_SIZE];           //mapping of renamed registers
        int reg_free_counter;       
        vector <ReservationStation*> reg_functionalUnit_Map;    //register mapping to reservation station
        ifstream inst_mem;  

        vector<Instruction> instructions;
        int inst_to_issue;                      //current instruction to issue (issue in order)
        

    public: 
        Tomasulu(int lrc, int src, int brc, int jrc, int arc, int drc, string file_path,  int lcc, int scc, int bcc, int jcc, int acc, int dcc);
        void extract_instructions();
        void rename_instructions();
        void print_instructions ();
        void simulate ();
        void Issue ();
        void Execute ();
        void WriteBack ();
};

#endif
