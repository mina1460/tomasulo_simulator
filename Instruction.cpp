#include "Instruction.h"

Instruction::Instruction(string assembly)
{
    instruction_asm = assembly;
    exec_e = 0;
    exec_s = 0;
}

void Instruction::extract_type(){
    stringstream ss(instruction_asm); 
    
    ss >> type;
        if (type == "LW")
    {
        int_type = 0;
    } else if (type == "SW")
    {
        int_type = 1;
    } else if (type =="BEQ")
    {
        int_type = 2;
    } else if (type == "JALR")
    {
        int_type = 3;
    } else if (type == "RET")
    {
        int_type = 4;
    } else if (type == "ADD")
    {
        int_type = 5;
    } else if (type == "NEG")
    {
        int_type = 6;
    } else if (type == "ADDI")
    {
        int_type = 7;
    } else if (type == "DIV")
    {
        int_type = 8;
    }
    extract_operands();
    
}
void Instruction::extract_operands(){

    stringstream iss(instruction_asm);
    string junk, temp, temp_inst; 
    iss >> junk;
    string rd_str, imm_str, rs1_str, rs2_str; 
    while (getline(iss, temp, ' ')){
            temp_inst += temp;
    }
        stringstream ss(temp_inst);
    switch (int_type)
    {
    case 0:
        /* LW rd, imm(rs1) */
        getline(ss, rd_str, ',');
        getline(ss, imm_str, '(');
        getline(ss, rs1_str, ')');
        rd_str = rd_str.substr(1, rd_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        rd = stoi(rd_str);
        rs1 = stoi(rs1_str);
        rs2 = 0; 
        imm = stoi(imm_str);
        res_id = 0;
        break;
    case 1:
        /* SW rs2, imm(rs1) */
        getline(ss, rs2_str, ',');
        getline(ss, imm_str, '(');
        getline(ss, rs1_str, ')');
        rs2_str = rs2_str.substr(1, rs2_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        rs2 = stoi(rs2_str);
        rs1 = stoi(rs1_str);
        rd = 0; 
        imm = stoi(imm_str);
        res_id = 1;
        break;
    case 2:
        /* BEQ rs1, rs2, imm */
        getline(ss, rs1_str, ',');
        getline(ss, rs2_str, ',');
        getline(ss, imm_str, '\n');
        rs2_str = rs2_str.substr(1, rs2_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        rs2 = stoi(rs2_str);
        rs1 = stoi(rs1_str);
        imm = stoi(imm_str);
        rd = 0; 
        res_id = 2;
        break;
    case 3:
        /* JALR rs1 */
        getline(ss, rs1_str, '\n');
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        rs2 = 0;
        rs1 = stoi(rs1_str);
        imm = 0;
        rd = 1; 
        res_id = 3;
        break;
    case 4:
        /* RET */
        rs1 = 1;
        rs2 = 0;
        imm = 0;
        rd = 0; 
        res_id = 3;
        break;
    case 5: 
    case 8:
        /* ADD rd, rs1, rs2  ||  DIV rd, rs1, rs2 */
        getline(ss, rd_str, ',');
        getline(ss, rs1_str, ',');
        getline(ss, rs2_str, '\n');
        rd_str = rd_str.substr(1, rd_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        rs2_str = rs2_str.substr(1, rs2_str.length()-1);
        rs2 = stoi(rs2_str);
        rs1 = stoi(rs1_str);
        imm = 0;
        rd = stoi(rd_str); 
        res_id = (int_type) == 8 ? 5 : 4;
        break;
    case 6:
        /* NEG rd, rs1 */
        getline(ss, rd_str, ',');
        getline(ss, rs1_str, ',');
        rd_str = rd_str.substr(1, rd_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        rs2 = 0;
        rs1 = stoi(rs1_str);
        imm = 0;
        rd = stoi(rd_str); 
        res_id = 4;
        break;
    case 7:
        /* ADDI rd, rs1, imm */
        getline(ss, rd_str, ',');
        getline(ss, rs1_str, ',');
        getline(ss, imm_str, '\n');
        rd_str = rd_str.substr(1, rd_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        rs2 = 0;
        rs1 = stoi(rs1_str);
        imm = stoi(imm_str);
        rd = stoi(rd_str); 
        res_id = 4;
        break;
    default:
        break;
    }
}
int Instruction::get_rd (){  
    return rd;  
}
void Instruction::set_rd (int p_rd){     
    rd = p_rd;
}
int Instruction::get_rs1 (){
    return rs1;
}
void Instruction::set_rs1 (int p_rs1){
    rs1 = p_rs1;
}
int Instruction::get_rs2 (){
    return rs2;
}
void Instruction::set_rs2 (int p_rs2){
    rs2 = p_rs2;
}
int Instruction::get_int_type (){
    return int_type;
}
int Instruction::get_imm (){
    return imm;
}
int Instruction::get_res_id (){
    return res_id;
}
void Instruction::set_issue_t (int p_t){
    issue_t = p_t;
}
void Instruction::set_exec_s (int p_t){
    exec_s = p_t;
}
void Instruction::set_exec_e (int p_t){
    exec_e = p_t;
}

int Instruction::get_issue_t(){
    return issue_t;
}
int Instruction::get_exec_s(){
    return exec_s;
}
int Instruction::get_exec_e(){
    return exec_e;
}

void Instruction::set_RS (ReservationStation * p_RS){
    RS = p_RS;
}
string Instruction::get_type(){
return type;
}
ReservationStation * Instruction::get_RS(){
    return RS;
}
Instruction::~Instruction()
{
    if (RS != NULL){
        delete RS;
    }
}
