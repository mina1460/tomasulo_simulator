
#include "Tomasulu.h"
#include <iomanip>
Tomasulu::Tomasulu(int lrc, int src, int brc, int jrc, int arc, int drc, string file_path,  int lcc, int scc, int bcc, int jcc, int acc, int dcc){
        
        inst_mem.open(file_path, ios::in);
        if(!inst_mem.is_open()){
                cerr << "Failed: Cannot open file " << file_path << "\n";
                exit(1); 
        }
        done = false;
        can_issue = true;
        branch_met = false;
        branch_pc = INT_MAX;
        clock = 0;
        cycles_count = 0; 
        instructions_count = 0; 
        misprediction_count = 0; 
        registers_count = 0;
        inst_to_issue = 0;
        no_of_branches = 0;
        
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

        for (int o = 0; o < MEM_SIZE; o++)
        {
                DataMem[o] = o;
        }
        
        DataMem [0] = 17;
        DataMem [110] = 9;
        DataMem [1] = 25;
        DataMem [124] = 9;
        DataMem [300] = 7;

}
void Tomasulu::addToMem (int val, int address){
        DataMem [address] = val;
        return;
}
void Tomasulu::extract_instructions(){
        string line; 
        while(getline(inst_mem,line)){
                Instruction temp_inst(line);
                instructions.push_back(temp_inst);                 
        }
        return;
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
        // printf("\n");
        }  
  

        
}

void Tomasulu::print_instructions (){
        for (int i=0; i<instructions.size(); i++){
        cout << instructions[i].get_rd() <<" <-- " << instructions[i].get_rs1() << " op " << instructions[i].get_rs2() <<" \n"; 
        }
}


void Tomasulu::simulate(){ 

       while (!done) {
                cout << clock << " ";
                if(inst_to_issue<instructions.size() && can_issue)
                        Issue();
                
                Execute();
                WriteBack();


                for (int i=0; i<RS.size(); i++){
                        for (int j=0; j<RS[i].size(); j++){
                               if (RS[i][j]->busy || clock < 100){
                                        done = false;
                                        goto cont;
                                }
                                else {
                                        done = true;
                                } 
                        }
                }
                cont:

                clock ++;
              
                int o; 
                cin >> o;
                if (o == -1) break;
                
                print_stats();
        }
        print_stats();
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
                        

                        if (RS[res_id][j]->op == "JALR" || RS[res_id][j]->op == "RET"){
                                can_issue = false;
                        }

                        if (branch_met){
                                RS_flush.push_back(RS[res_id][j]);
                                
                        }
                        
                        if(RS[res_id][j]->op == "BEQ" && !branch_met) {
                                branch_pc = inst_to_issue;
                                branch_met = true;
                        }
                        
                        
                        //Vj and Qj of Reservation Station
                        if (!register_status[instructions[inst_to_issue].get_rs1()].getBusy() || instructions[inst_to_issue].get_rs1() == 0){
                             RS[res_id][j]->Vj = reg_file[instructions[inst_to_issue].get_rs1()];
                             RS[res_id][j]->Qj = -1;
                             RS[res_id][j]->IDj = -1;
                        } else {
                             RS[res_id][j]->Qj = register_status[instructions[inst_to_issue].get_rs1()].getQ();  
                             RS[res_id][j]->IDj = register_status[instructions[inst_to_issue].get_rs1()].getIndex();
                        }
                        
                        // Vk and Qk of Reservation Station
                        if (!register_status[instructions[inst_to_issue].get_rs2()].getBusy() || instructions[inst_to_issue].get_rs2() == 0){
                             RS[res_id][j]->Vk = reg_file[instructions[inst_to_issue].get_rs2()];
                             RS[res_id][j]->Qk = -1;
                             RS[res_id][j]->IDk = -1;
                        } else {
                             RS[res_id][j]->Qk = register_status[instructions[inst_to_issue].get_rs2()].getQ(); 
                             RS[res_id][j]->IDk = register_status[instructions[inst_to_issue].get_rs2()].getIndex();
                        }

                        //set imm of Reservation Station
                        RS[res_id][j]->imm = instructions[inst_to_issue].get_imm();

                        //mark RD register as busy
                        if (instructions[inst_to_issue].get_rd() != 0)
                                register_status[instructions[inst_to_issue].get_rd()].setQ(res_id, j);

                        
                        inst_to_issue ++; 
                }
}

void Tomasulu::Execute(){

    //execution
    /*
    Loop on every Reservation Station and check:
        1- If Busy
        2- If instruction issue time is less than clock (so as not to issue and execute at same clock cycle)
        3- If execution counter less or equal to max cycles for exectuion
        4- If branch hasnt been met or branch is met and instruction is before branch
    */
                        // cout << "In execute\n";
    for (int i=0; i<RS.size(); i++){
            for (int j=0; j<RS[i].size(); j++){
                    int inst_num = RS[i][j]->instruction_number;

                        // cout << inst_num << " ";
                        // cout << "\t" << instructions[inst_num].get_issue_t() << " " << clock << "\n";

                    if (RS[i][j]->busy 
                        && instructions[inst_num].get_issue_t() < clock 
                        && instructions[inst_num].get_exec_e() <= (cyc_count[instructions[inst_num].get_int_type()])
                        && (!branch_met || (branch_met && (inst_num <= branch_pc)))
                        ){
                        //     cout << "\n" << inst_num << ": Qj " << RS[i][j]->Qj << " " << "Qk " << RS[i][j]->Qk << " ";
                        //     cout << "\t end: " << instructions[inst_num].get_exec_e() << "\t start: " << instructions[inst_num].get_exec_s()<< "\n";
                            if (RS[i][j]->Qj == -1 && RS[i][j]->Qk == -1){          //Qj and Qk are empty
                                    
                                    if (instructions[inst_num].get_exec_s() == 0){
                                            instructions[inst_num].set_exec_s(clock);
                                            int e = instructions[inst_num].get_exec_e();
                                            instructions[inst_num].set_exec_e(++e);
                                    } else {
                                            int e = instructions[inst_num].get_exec_e();
                                            instructions[inst_num].set_exec_e(++e);
                                    }
                                    
                                    if (instructions[inst_num].get_exec_e()+1 == (cyc_count[instructions[inst_num].get_int_type()])){
                                            int s = instructions[inst_num].get_exec_s();
                                            int e = instructions[inst_num].get_exec_e();
                                            instructions[inst_num].set_exec_e(s+e);
                                            int int_type = instructions[inst_num].get_int_type();
                                            switch (int_type)
                                            {
                                            case 0:
                                                    /* LW rd, imm(rs1) */
                                                    RS[i][j]->address = RS[i][j]->Vj + RS[i][j]->imm;
                                                    RS[i][j]->result = DataMem[RS[i][j]->address % MEM_SIZE];
                                                    RS[i][j]->ready = true;
                                                    break;
                                            case 1:
                                                    /* SW rs2, imm(rs1) */
                                                    RS[i][j]->address = RS[i][j]->Vj + RS[i][j]->imm;
                                                    RS[i][j]->ready = true;
                                                    break;
                                            case 2:
                                                    /* BEQ rs1, rs2, imm */
                                                    if (RS[i][j]->Vj == RS[i][j]->Vk){
                                                        inst_to_issue += RS[i][j]->imm;
                                                        for (int k = 0; k < RS_flush.size(); k++)
                                                                RS_flush[k]->resetRS();
                                                        misprediction_count++;
                                                    }
                                                    branch_met = false;
                                                    RS_flush.clear();
                                                    no_of_branches++;
                                                    RS[i][j]->ready = true;
                                                    break;
                                            case 3:
                                                    /* JALR rs1 */
                                                    RS[i][j]->result = inst_to_issue;
                                                    RS[i][j]->ready = true;
                                                    inst_to_issue = RS[i][j]->Vj;
                                                    can_issue = true;
                                                    break;
                                            case 4:
                                                    /* RET */
                                                    inst_to_issue = RS[i][j]->Vj;
                                                    can_issue = true;
                                                    RS[i][j]->ready = true;
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
                                                    cout << "DEFAULT EXEC\n";
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

        for (int i=0; i<RS.size(); i++){
                for (int j=0; j<RS[i].size(); j++){
                        int inst_num = RS[i][j]->instruction_number;
                        if (RS[i][j]->busy 
                            && RS[i][j]->ready
                            && instructions[inst_num].get_exec_e() < clock
                        ){
                        int int_type = instructions[inst_num].get_int_type();
                        instructions[inst_num].setWriteT(clock);
                        res_counter[instructions[inst_num].get_res_id()]--;
                                switch (int_type)
                                            {
                                            case 0:     /* LW rd, imm(rs1) */
                                            case 3:     /* JALR rs1 */
                                            case 5:     /* ADD rd, rs1, rs2  */ 
                                            case 6:     /* NEG rd, rs1 */
                                            case 7:     /* ADDI rd, rs1, imm */
                                            case 8:     /* DIV rd, rs1, rs2 */
                                                    
                                                    for (int k = 0; k<register_status.size(); k++){
                                                        if (register_status[k].getIndex() == i && register_status[k].getQ() == j){
                                                                reg_file[k] = RS[i][j]->result;
                                                                reg_file[0] = 0;
                                                                register_status[k].setQ(-1,-1);
                                                                register_status[k].setNOTBusy();
                                                                
                                                        }
                                                    }

                                                    for (int x=0; x<RS.size(); x++){
                                                        for (int y=0; y<RS[x].size(); y++){
                                                                if (RS[x][y]->IDj == i && RS[x][y]->Qj == j){
                                                                        RS[x][y]->Vj = RS[i][j]->result;
                                                                        RS[x][y]->Qj = -1;
                                                                }
                                                                if (RS[x][y]->IDk == i && RS[x][y]->Qk == j){
                                                                        RS[x][y]->Vk = RS[i][j]->result;
                                                                        RS[x][y]->Qk = -1;
                                                                }
                                                        }
                                                    }

                                                    RS[i][j]->resetRS();
                                                    break;
                                            
                                            case 1:     /* SW rs2, imm(rs1) */

                                                    DataMem[RS[i][j]->address % MEM_SIZE] = RS[i][j]->Vk;
                                                    RS[i][j]->resetRS();
                                                    break;

                                            case 2:     /* BEQ rs1, rs2, imm */
                                                    
                                                    RS[i][j]->resetRS();
                                                    break;
                                            
                                            case 4:     /* RET */
                                                    
                                                    RS[i][j]->resetRS();   
                                                    break;
                                            
                                            default:
                                                    cout << "DEFAULT WB\n";
                                                    break;
                                        }
                                       


                        }
                }
        }
}

void Tomasulu::print_stats(){
        // ofstream stats;
        // stats.open("stats.html", ios::out);
        
        cout <<"Instructions\t\t"  <<"Issue\t" << "Execute\t\t" << "Write Back\t" << endl;
                int i;
        for (i = 0; i < instructions.size(); i++)
        {
                cout << instructions[i].get_inst() 
                        << "\t\t\t" << instructions[i].get_issue_t() 
                        << "\t" << instructions[i].get_exec_s() <<" - " << instructions[i].get_exec_e() 
                        << "\t\t" <<instructions[i].get_write_t() << endl;
        }
        cout << "\nREG Status\n";
        for(int j=0; j<REG_FILE_SIZE; j++){
                cout <<"X" <<j <<": " << register_status[j].getIndex() << " " << register_status[j].getQ() << "\t";
        }

        cout << "\nREG file\n";
        for(int j=0; j<REG_FILE_SIZE; j++){
                cout <<"X" <<j <<": " <<reg_file[j] << "\t";
        }
        printf("\n");
        cout << "Number of Clock cycles = " << instructions[i-1].get_write_t() << "\n";
        cout << "Instruction per Cycle (IPC) = " << (float)i / (float)instructions[i-1].get_write_t() << "\n";
        cout << "Branch Misprediction Percentage = " << ((float)misprediction_count / (float)no_of_branches) * 100 << "\n";
        
}