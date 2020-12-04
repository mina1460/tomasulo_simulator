#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
// #include <boost/algorithm/string.hpp>
using namespace std; 

/*
After Register Renaming
    Issue:      If there is a free reservation station
    Execute:    Both operands are ready (RaW)
    Write:         

*/

class ReservationStation {
    private:
        string name;
        bool busy;
        string op;
        int Vj, Vk;
        string Qj, Qk;
        int address;
    public:
        ReservationStation (string p_name){
            name = p_name;
        }

};


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
        Instruction(string asma)
        {
            instruction_asm = asma;
        }
        
        void extract_type(){
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

        void extract_operands(){

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
                cout << temp_inst << "\n";
                getline(ss, rd_str, ',');
                getline(ss, imm_str, '(');
                getline(ss, rs1_str, ')');
                cout << junk << " " << rd_str << " " << imm_str << " " << rs1_str << "\n";
                rd_str = rd_str.substr(1, rd_str.length()-1);
                rs1_str = rs1_str.substr(1, rs1_str.length()-1);
                cout << junk << " " << rd_str << " " << imm_str << " " << rs1_str << "\n";
                rd = stoi(rd_str);
                rs1 = stoi(rs1_str);
                rs2 = 0; 
                imm = stoi(imm_str);
                break;
            case 1:
                /* SW rs2, imm(rs1) */
                cout << temp_inst << "\n";
                getline(ss, rs2_str, ',');
                getline(ss, imm_str, '(');
                getline(ss, rs1_str, ')');
                rs2_str = rs2_str.substr(1, rs2_str.length()-1);
                rs1_str = rs1_str.substr(1, rs1_str.length()-1);
                cout << junk << " " << rs2_str << " " << imm_str << " " << rs1_str << "\n";
                rs2 = stoi(rs2_str);
                rs1 = stoi(rs1_str);
                rd = 0; 
                imm = stoi(imm_str);
                break;
            case 2:
                /* BEQ rs1, rs2, imm */
                cout << temp_inst << "\n";
                getline(ss, rs1_str, ',');
                getline(ss, rs2_str, ',');
                getline(ss, imm_str, '\n');
                rs2_str = rs2_str.substr(1, rs2_str.length()-1);
                rs1_str = rs1_str.substr(1, rs1_str.length()-1);
                cout << junk << " " << rs1_str << " " << rs2_str << " " << imm_str << "\n";
                rs2 = stoi(rs2_str);
                rs1 = stoi(rs1_str);
                imm = stoi(imm_str);
                rd = 0; 
                break;
            case 3:
                /* JALR rs1 */
                cout << temp_inst << "\n";
                getline(ss, rs1_str, '\n');
                rs1_str = rs1_str.substr(1, rs1_str.length()-1);
                cout << junk << " " << rs1_str << " " << rs2_str << " " << imm_str << "\n";
                rs2 = 0;
                rs1 = stoi(rs1_str);
                imm = 0;
                rd = 1; 
                break;
            case 4:
                /* RET */
                cout << temp_inst << "\n";
                rs1 = 1;
                rs2 = 0;
                imm = 0;
                rd = 0; 
                break;
            case 5: 
            case 8:
                /* ADD rd, rs1, rs2  ||  DIV rd, rs1, rs2 */
                cout << temp_inst << "\n";
                getline(ss, rd_str, ',');
                getline(ss, rs1_str, ',');
                getline(ss, rs2_str, '\n');
                rd_str = rd_str.substr(1, rd_str.length()-1);
                rs1_str = rs1_str.substr(1, rs1_str.length()-1);
                rs2_str = rs2_str.substr(1, rs2_str.length()-1);
                cout << junk << " " << rd_str << " " << rs1_str << " " << rs2_str << "\n";
                rs2 = stoi(rs2_str);
                rs1 = stoi(rs1_str);
                imm = 0;
                rd = stoi(rd_str); 
                break;
            case 6:
                /* NEG rd, rs1 */
                cout << temp_inst << "\n";
                getline(ss, rd_str, ',');
                getline(ss, rs1_str, ',');
                rd_str = rd_str.substr(1, rd_str.length()-1);
                rs1_str = rs1_str.substr(1, rs1_str.length()-1);
                cout << junk << " " << rd_str << " " << rs1_str << "\n";
                rs2 = 0;
                rs1 = stoi(rs1_str);
                imm = 0;
                rd = stoi(rd_str); 
                break;
            case 7:
                /* ADDI rd, rs1, imm */
                cout << temp_inst << "\n";
                getline(ss, rd_str, ',');
                getline(ss, rs1_str, ',');
                getline(ss, imm_str, '\n');
                rd_str = rd_str.substr(1, rd_str.length()-1);
                rs1_str = rs1_str.substr(1, rs1_str.length()-1);
                cout << junk << " " << rd_str << " " << rs1_str << " " << imm_str << "\n";
                rs2 = 0;
                rs1 = stoi(rs1_str);
                imm = stoi(imm_str);
                rd = stoi(rd_str); 
                break;
            default:
                break;
            }
        }

};




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


        int reg_file[8];

        ifstream inst_mem; 

        vector<Instruction> instructions;

    public: 
        Tomasulu(int lrc, int src, int brc, int jrc, int arc, int drc, string file_path,  int lcc, int scc, int bcc, int jcc, int acc, int dcc){
            
            inst_mem.open(file_path, ios::in);
            if(!inst_mem.is_open()){
                cerr << "Failed: Cannot open file " << file_path << "\n";
                exit(1); 
            }
            load_res_counter  = 0;
            store_res_counter = 0;
            beq_res_counter   = 0;
            jal_res_counter   = 0;
            add_res_counter   = 0;
            div_res_counter   = 0;
            
            res_count.push_back(lrc);
            res_count.push_back(src); 
            res_count.push_back(brc); 
            res_count.push_back(jrc);
            res_count.push_back(jrc); 
            res_count.push_back(arc); 
            res_count.push_back(arc);
            res_count.push_back(arc);
            res_count.push_back(drc);

            cyc_count.push_back(lcc);
            cyc_count.push_back(scc); 
            cyc_count.push_back(bcc); 
            cyc_count.push_back(jcc);
            cyc_count.push_back(jcc); 
            cyc_count.push_back(acc); 
            cyc_count.push_back(acc);
            cyc_count.push_back(acc);
            cyc_count.push_back(dcc);

        }

        void extract_instructions(){
            string line; 
            while(getline(inst_mem,line)){
                Instruction temp_inst(line);
                instructions.push_back(temp_inst);
                
            }
        }
        void print_instructions(){
            for (auto i : instructions)
            {
                i.extract_type();
            }
            
        }
        void check_RaW();
        void check_WaR();
        void check_WAW();

};


int main(){

    cout << "Enter cycles for : LW SW BEQ JALR/RET ADD/NEG/ADDI DIV:";
    int lc, sc, bc, jc, ac, dc;
    cin >> lc >>  sc >> bc >> jc >> ac >> dc;
    
    cout << "Enter reservation stations for : LW SW BEQ JALR/RET ADD/NEG/ADDI DIV:";
    int lr, sr, br, jr, ar, dr;
    cin >> lr >> sr >> br >> jr >> ar >> dr;

    Tomasulu tomasulu(lr, sr, br, jr, ar, dr, "./instructions.asm", lc, sc, bc, jc, ac, dc);
    tomasulu.extract_instructions();
    tomasulu.print_instructions();


    return 0;
}