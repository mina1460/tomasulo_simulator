#ifndef INST_H_
#define INST_H_

#include "includes.h"
#include "ReservationStation.h"


class Instruction{
    private:
        int issue_t; 
        int exec_s, exec_e; 
        int write_t; 
        int rd, rs1, rs2; 
        int imm; 
        string type; 
        int execution_time; 
        string instruction_asm;
        int int_type, res_id;       //add, load, store, div,  branches, jal_Ret; 
        ReservationStation * RS;
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
        int get_int_type ();
        int get_res_id();
        void set_issue_t (int p_t);
        void set_RS (ReservationStation * p_RS);
        string get_type ();
        ReservationStation * get_RS();
        int get_imm ();
        int get_issue_t();
        int get_exec_s();
        int get_exec_e();
        void set_exec_s(int x);
        void set_exec_e(int x);
        
        ~Instruction();
};

#endif

/*
Types:
    0   Load
    1   Store
    2   Branch
    3   JALR
    4   RET
    5   ADD
    6   NEG
    7   ADDI
    8   DIV

RES_id:
    0   Load
    1   Store
    2   Branch
    3   JALR/RET
    4   ADD/NEG/ADDI
    5   DIV
*/