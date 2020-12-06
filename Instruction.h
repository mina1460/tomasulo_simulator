#ifndef INST_H_
#define INST_H_

#include "includes.h"


class Instruction{
    private:
        int issue_t; 
        int exec_s, exec_e; 
        int write_t; 
        int rd, rs1, rs2; 
        int imm; 
        int execution_time; 
        string instruction_asm;
        int int_type;       //add, load, store, div,  branches, jal_Ret; 
        int reservation_station;
    public: 
        Instruction(string assembly);
        void extract_type();
        void extract_operands();
        int get_rd ();
        void set_rd (int p_rd);
        int get_rs1 ();
        void set_rs1 (int p_rs1);
        int get_rs2 ();
        void set_rs2 (int p_rs2);

};

#endif