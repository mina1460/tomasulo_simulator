#include "Instruction.h"

Instruction::Instruction(string assembly)
{
    instruction_asm = assembly;
}

void Instruction::extract_type(){
    stringstream ss(instruction_asm); 
    string type; 
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
        // cout << temp_inst << "\n";
        getline(ss, rd_str, ',');
        getline(ss, imm_str, '(');
        getline(ss, rs1_str, ')');
        // cout << junk << " " << rd_str << " " << imm_str << " " << rs1_str << "\n";
        rd_str = rd_str.substr(1, rd_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        // cout << junk << " " << rd_str << " " << imm_str << " " << rs1_str << "\n";
        rd = stoi(rd_str);
        // cout << "LW rd = " << rd << "\n";
        rs1 = stoi(rs1_str);
        rs2 = 0; 
        imm = stoi(imm_str);
        break;
    case 1:
        /* SW rs2, imm(rs1) */
        //cout << temp_inst << "\n";
        getline(ss, rs2_str, ',');
        getline(ss, imm_str, '(');
        getline(ss, rs1_str, ')');
        rs2_str = rs2_str.substr(1, rs2_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        // cout << junk << " " << rs2_str << " " << imm_str << " " << rs1_str << "\n";
        rs2 = stoi(rs2_str);
        rs1 = stoi(rs1_str);
        rd = 0; 
        imm = stoi(imm_str);
        break;
    case 2:
        /* BEQ rs1, rs2, imm */
        // cout << temp_inst << "\n";
        getline(ss, rs1_str, ',');
        getline(ss, rs2_str, ',');
        getline(ss, imm_str, '\n');
        rs2_str = rs2_str.substr(1, rs2_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        // cout << junk << " " << rs1_str << " " << rs2_str << " " << imm_str << "\n";
        rs2 = stoi(rs2_str);
        rs1 = stoi(rs1_str);
        imm = stoi(imm_str);
        rd = 0; 
        break;
    case 3:
        /* JALR rs1 */
        // cout << temp_inst << "\n";
        getline(ss, rs1_str, '\n');
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        // cout << junk << " " << rs1_str << " " << rs2_str << " " << imm_str << "\n";
        rs2 = 0;
        rs1 = stoi(rs1_str);
        imm = 0;
        rd = 1; 
        break;
    case 4:
        /* RET */
        // cout << temp_inst << "\n";
        rs1 = 1;
        rs2 = 0;
        imm = 0;
        rd = 0; 
        break;
    case 5: 
    case 8:
        /* ADD rd, rs1, rs2  ||  DIV rd, rs1, rs2 */
        // cout << temp_inst << "\n";
        getline(ss, rd_str, ',');
        getline(ss, rs1_str, ',');
        getline(ss, rs2_str, '\n');
        rd_str = rd_str.substr(1, rd_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        rs2_str = rs2_str.substr(1, rs2_str.length()-1);
        // cout << junk << " " << rd_str << " " << rs1_str << " " << rs2_str << "\n";
        rs2 = stoi(rs2_str);
        rs1 = stoi(rs1_str);
        imm = 0;
        rd = stoi(rd_str); 
        break;
    case 6:
        /* NEG rd, rs1 */
        // cout << temp_inst << "\n";
        getline(ss, rd_str, ',');
        getline(ss, rs1_str, ',');
        rd_str = rd_str.substr(1, rd_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
        // cout << junk << " " << rd_str << " " << rs1_str << "\n";
        rs2 = 0;
        rs1 = stoi(rs1_str);
        imm = 0;
        rd = stoi(rd_str); 
        break;
    case 7:
        /* ADDI rd, rs1, imm */
        // cout << temp_inst << "\n";
        getline(ss, rd_str, ',');
        getline(ss, rs1_str, ',');
        getline(ss, imm_str, '\n');
        rd_str = rd_str.substr(1, rd_str.length()-1);
        rs1_str = rs1_str.substr(1, rs1_str.length()-1);
    //    cout << junk << " " << rd_str << " " << rs1_str << " " << imm_str << "\n";
        rs2 = 0;
        rs1 = stoi(rs1_str);
        imm = stoi(imm_str);
        rd = stoi(rd_str); 
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

