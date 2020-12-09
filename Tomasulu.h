#ifndef TOMASULU_H_
#define TOMASULU_H_

#include "Instruction.h"
#include "ReservationStation.h"
#include "Rstat.h"

#define MEM_SIZE    320

class Tomasulu{
    private: 
        int clock; 
        int cycles_count; 
        int instructions_count; 
        int misprediction_count; 
        int registers_count;
        bool done;

        int no_of_branches;
        int branch_pc;
        bool branch_met;
        bool can_issue;

        int DataMem [MEM_SIZE] = {0};
        vector <int> res_count;             //reservation stations count
        vector <int> cyc_count;             //cycles taken to execute instruction
        vector <int> res_counter;           //currently used reservation stations

        vector < vector<ReservationStation*>> RS;
        vector <ReservationStation*> RS_flush;          //RS to flush (reset) if branch taken

        int reg_file [REG_FILE_SIZE];           //values of the registers
        int reg_map  [REG_FILE_SIZE];           //mapping of renamed registers
        int reg_free_counter;       
        vector <ReservationStation*> reg_functionalUnit_Map;    //register mapping to reservation station
        ifstream inst_mem;  
        vector <Rstat> register_status;
        vector<Instruction> instructions;
        int inst_to_issue;                      //current instruction to issue (issue in order)
        

    public: 
        Tomasulu(int lrc, int src, int brc, int jrc, int arc, int drc, string file_path,  int lcc, int scc, int bcc, int jcc, int acc, int dcc);
        void addToMem (int val, int address);
        void extract_instructions();
        void rename_instructions();
        void print_instructions ();
        void simulate ();
        void Issue ();
        void Execute ();
        void WriteBack ();
        void print_stats();
};

#endif
