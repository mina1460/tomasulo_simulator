
#include "Tomasulu.h"

Tomasulu::Tomasulu(int lrc, int src, int brc, int jrc, int arc, int drc, string file_path,  int lcc, int scc, int bcc, int jcc, int acc, int dcc){
        
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

        reg_free_counter = REG_FILE_SIZE;   //8

        for (int i=0; i<REG_FILE_SIZE; i++){
        reg_file[i] = 0;
        reg_map[i] = i;
        }
}

void Tomasulu::extract_instructions(){
        string line; 
        while(getline(inst_mem,line)){
        Instruction temp_inst(line);
        instructions.push_back(temp_inst);                
        }
}
void Tomasulu::rename_instructions(){
        printf("\n");
        for (int i=0; i<instructions.size(); i++){
        instructions[i].extract_type();
        /* Renaming */
        cout << instructions[i].get_rd() <<" <-- " << instructions[i].get_rs1() << " op " << instructions[i].get_rs2() <<" \n"; 
        if (instructions[i].get_rd() != 0){
                
                instructions[i].set_rs1(reg_map[instructions[i].get_rs1()]);
                instructions[i].set_rs2(reg_map[instructions[i].get_rs2()]);
                
                reg_map[instructions[i].get_rd()] = reg_free_counter;
                instructions[i].set_rd(reg_free_counter); 
                reg_free_counter++;
                
                cout << instructions[i].get_rd() <<" <-- " << instructions[i].get_rs1() << " op " << instructions[i].get_rs2() <<" \n"; 
        }
        /************/
        printf("\n");
        }

        
}

void Tomasulu::print_instructions (){
        for (int i=0; i<instructions.size(); i++){
        cout << instructions[i].get_rd() <<" <-- " << instructions[i].get_rs1() << " op " << instructions[i].get_rs2() <<" \n"; 
        }
}

void Tomasulu::check_RaW(){}
void Tomasulu::check_WaR(){}
void Tomasulu::check_WAW(){}
