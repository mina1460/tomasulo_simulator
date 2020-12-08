
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
       
        reg_free_counter = REG_FILE_SIZE;   //8

        //initializes register file, register status
        for (int i=0; i<REG_FILE_SIZE; i++){
                reg_file[i] = 0;
                reg_map[i] = i;
                Rstat r;
                register_status.push_back(r);
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
                
                if(inst_to_issue<instructions.size())
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
                2- check number of remaining reservation stations. if greater than zero, issue and subtract one
                */
                if(res_counter[instructions[inst_to_issue].get_res_id()] < res_count[instructions[inst_to_issue].get_int_type()]){
                        
                        instructions[inst_to_issue].set_issue_t(clock);
                        
                        int res_id = instructions[inst_to_issue].get_res_id();
                        int size_RS = RS[res_id].size();
                        int j;
                        for (j=0; j<size_RS; j++)
                                if (!RS[res_id][j]->busy){
                                        instructions[inst_to_issue].set_RS(RS[res_id][j]);
                                        RS[res_id][j]->instruction_number = inst_to_issue;
                                        RS[res_id][j]->busy = true;
                                        res_counter[instructions[inst_to_issue].get_res_id()]++;
                                        break;
                                }

                        RS[res_id][j]->op = instructions[inst_to_issue].get_type();
                        RS[res_id][j]->id = res_id;
                        
                        //Vj and Qj of Reservation Station
                        if (!register_status[instructions[inst_to_issue].get_rs1()].getBusy()){
                             RS[res_id][j]->Vj = reg_file[instructions[inst_to_issue].get_rs1()];
                             RS[res_id][j]->Qj = -1;
                        } else {
                             RS[res_id][j]->Qj = register_status[instructions[inst_to_issue].get_rs1()].getQ();  
                        }
                        
                        // Vk and Qk of Reservation Station
                        if (!register_status[instructions[inst_to_issue].get_rs2()].getBusy()){
                             RS[res_id][j]->Vk = reg_file[instructions[inst_to_issue].get_rs2()];
                             RS[res_id][j]->Qk = -1;
                        } else {
                             RS[res_id][j]->Qk = register_status[instructions[inst_to_issue].get_rs2()].getQ();  
                        }

                        //set imm of Reservation Station
                        RS[res_id][j]->imm = instructions[inst_to_issue].get_imm();

                        //mark RD register as busy
                        register_status[instructions[inst_to_issue].get_rd()].setQ(res_id, j);

                        
                        inst_to_issue ++; 
                }
}

void Tomasulu::Execute(){

    //execution
    /*
    1- check if instruction Qj and Qk are empty
    2- check if any precending branch instruction finished execution
    */
    for (int i=0; i<RS.size(); i++){
            for (int j=0; j<RS[i].size(); j++){
                    int inst_num = RS[i][j]->instruction_number;
                    if (RS[i][j]->busy 
                        && instructions[inst_num].get_issue_t() > clock 
                        && instructions[inst_num].get_exec_e() <= (cyc_count[instructions[inst_num].get_int_type()])
                        ){

                            if (RS[i][j]->Qj == -1 && RS[i][j]->Qk == -1){          //Qj and Qk are empty
                                    
                                    if (instructions[inst_num].get_exec_s() == 0){
                                            instructions[inst_num].set_exec_s(clock);
                                            int e = instructions[inst_num].get_exec_e();
                                            instructions[inst_num].set_exec_e(e++);
                                    } else {
                                            int e = instructions[inst_num].get_exec_e();
                                            instructions[inst_num].set_exec_e(e++);
                                    }
                                    
                                    if (instructions[inst_num].get_exec_e() == (cyc_count[instructions[inst_num].get_int_type()])){
                                            int s = instructions[inst_num].get_exec_s();
                                            int e = instructions[inst_num].get_exec_e();
                                            instructions[inst_num].set_exec_e(s+e);
                                            int int_type = instructions[inst_num].get_int_type();
                                            switch (int_type)
                                            {
                                            case 0:
                                                    /* LW rd, imm(rs1) */
                                                    
                                                    break;
                                            case 1:
                                                    /* SW rs2, imm(rs1) */
                                                    
                                                    break;
                                            case 2:
                                                    /* BEQ rs1, rs2, imm */
                                                    
                                                    break;
                                            case 3:
                                                    /* JALR rs1 */
                                                    
                                                    break;
                                            case 4:
                                                    /* RET */

                                                    break;
                                            case 5:
                                                    /* ADD rd, rs1, rs2  */ 
                                                    RS[i][j]->result = RS[i][j]->Vj + RS[i][j]->Vk;
                                                    RS[i][j]->ready = true;
                                                    break;
                                            case 6:
                                                    /* NEG rd, rs1 */
                                                    RS[i][j]->result = 0-RS[i][j]->Vj;
                                                    RS[i][j]->ready = true;
                                                    break;
                                            case 7:
                                                    /* ADDI rd, rs1, imm */
                                                    RS[i][j]->result = RS[i][j]->Vj + RS[i][j]->imm;
                                                    RS[i][j]->ready = true;
                                                    break;
                                            case 8:
                                                    /* DIV rd, rs1, rs2 */
                                                    RS[i][j]->result = RS[i][j]->Vj / RS[i][j]->Vk;
                                                    RS[i][j]->ready = true;
                                                    break;
                                            default:
                                                    RS[i][j]->ready = false;
                                                    break;
                                        }

                                    }

                                    
                            } else continue;

                            
                            



                    }
            }
    }
    
            





}



void Tomasulu::WriteBack(){
//write back
                /*
                1- check all reservation stations (Qj and Qk) if listening for result
                2- write value to register file
                */
}