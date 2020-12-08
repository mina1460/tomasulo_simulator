
#include "Tomasulu.h"

Tomasulu::Tomasulu(int lrc, int src, int brc, int jrc, int arc, int drc, string file_path,  int lcc, int scc, int bcc, int jcc, int acc, int dcc){
        
        inst_mem.open(file_path, ios::in);
        if(!inst_mem.is_open()){
        cerr << "Failed: Cannot open file " << file_path << "\n";
        exit(1); 
        }
        done = false;
        clock = 0;
        cycles_count = 0; 
        instructions_count = 0; 
        misprediction_count = 0; 
        registers_count = 0;
        inst_to_issue = 0;
        
        for (int i=0; i<6; i++)
                res_counter.push_back(0);
        
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

        vector <ReservationStation*> load_RS;  
        for (int i=0; i<lrc; i++){
                load_RS.push_back(new ReservationStation("Load" + to_string(i)));
        }
        
        vector <ReservationStation*> store_RS;
        for (int i=0; i<src; i++){
                store_RS.push_back(new ReservationStation("Store" + to_string(i)));
        }

        vector <ReservationStation*> beq_RS;
        for (int i=0; i<brc; i++){
                beq_RS.push_back(new ReservationStation("Branch" + to_string(i)));
        }

        vector <ReservationStation*> jal_RS;
        for (int i=0; i<jrc; i++){
                jal_RS.push_back(new ReservationStation("JAL" + to_string(i)));
        }

        vector <ReservationStation*> add_RS;
        for (int i=0; i<arc; i++){
                add_RS.push_back(new ReservationStation("ADD" + to_string(i)));
        }

        vector <ReservationStation*> div_RS;
        for (int i=0; i<drc; i++){
                div_RS.push_back(new ReservationStation("DIV" + to_string(i)));
        }

        

        RS.push_back(load_RS);
        RS.push_back(store_RS);
        RS.push_back(beq_RS);
        RS.push_back(jal_RS);
        RS.push_back(add_RS);
        RS.push_back(div_RS);
       
        for (int i=0; i<100; i++)
                reg_functionalUnit_Map.push_back(NULL);



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
        /* Renaming 
        cout << instructions[i].get_rd() <<" <-- " << instructions[i].get_rs1() << " op " << instructions[i].get_rs2() <<" \n"; 
        if (instructions[i].get_rd() != 0){
                
                instructions[i].set_rs1(reg_map[instructions[i].get_rs1()]);
                instructions[i].set_rs2(reg_map[instructions[i].get_rs2()]);
                
                reg_map[instructions[i].get_rd()] = reg_free_counter;
                instructions[i].set_rd(reg_free_counter); 
                reg_free_counter++;
                
                cout << instructions[i].get_rd() <<" <-- " << instructions[i].get_rs1() << " op " << instructions[i].get_rs2() <<" \n"; 
        }*/
        /************/
        printf("\n");
        }

        
}

void Tomasulu::print_instructions (){
        for (int i=0; i<instructions.size(); i++){
        cout << instructions[i].get_rd() <<" <-- " << instructions[i].get_rs1() << " op " << instructions[i].get_rs2() <<" \n"; 
        }
}


void Tomasulu::simulate(){ 
      
       while (!done) {
                Issue();
                Execute();
                WriteBack();
                clock ++;
                
        }
}

void Tomasulu::Issue(){
                //issue step 
                /*
                1- check operation functional unit type 
                2- check number of remaining reserv stations. if greater than zero, issue and subtract one
                */
                if(res_counter[instructions[inst_to_issue].get_res_id()] < res_count[instructions[inst_to_issue].get_type()]){
                        
                        instructions[inst_to_issue].set_issue_t(clock);
                        
                        int res_id = instructions[inst_to_issue].get_res_id();
                        int size_RS = RS[res_id].size();
                        for (int j=0; j<size_RS; j++)
                                if (!RS[res_id][j]->get_busy()){
                                        instructions[inst_to_issue].set_RS(RS[res_id][j]);
                                        break;
                                }

                        if (reg_functionalUnit_Map[instructions[inst_to_issue].get_rs1()] == NULL){
                                // instructions[inst_to_issue].get_rs1();  
                                // instructions[inst_to_issue].get_RS()->set_Vj(reg_file[map[rs1]]);
                        }
                        else
                        {
                                reg_functionalUnit_Map[instructions[inst_to_issue].get_rs1()] = instructions[inst_to_issue].get_RS();
                                
                        }
                        
                        
                        
                        reg_functionalUnit_Map[instructions[inst_to_issue].get_rd()] = instructions[inst_to_issue].get_RS();


                        
                }
}

void Tomasulu::Execute(){

                //execution
                /*
                1- check if instruction Qj and Qk are empty
                2- check if any precending branch instruction finished execution
                */

}

void Tomasulu::WriteBack(){
//write back
                /*
                1- check all reservation stations (Qj and Qk) if listening for result
                2- write value to register file
                */
}