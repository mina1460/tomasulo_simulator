
#include "includes.h"
#include "Instruction.h"
#include "ReservationStation.h"
#include "Tomasulu.h"


/*
g++ -I . main.cpp Instruction.cpp ReservationStation.cpp Tomasulu.cpp Rstat.cpp -o main.exe
g++ -g -I . main.cpp Instruction.cpp ReservationStation.cpp Tomasulu.cpp Rstat.cpp -o newmain
break Tomasulu::extract_instructions()
After Register Renaming
    Issue:      If there is a free reservation station
    Execute:    When both operands are ready (RaW) & branch outcome known
    Write:      After execution, NO condition       
http://people.ee.duke.edu/~sorin/ece252/lectures/4.2-tomasulo.pdf


To Do:
    - JALR does not reissue instructions after jumping backwards
    - LW rs1 dependancy stalls execution
    - SW rs2 dependancy stalls execution
    - Try BEQ, RET, NEG, DIV   
    - Add another stopping condition
    - First instruction takes 1 extra cycle in execution
    - User enters starting program's address 

*/


int main(){

    //cout << "Enter cycles for : LW SW BEQ JALR/RET ADD/NEG/ADDI DIV:";
    int lc(2), sc(2), bc(1), jc(2), ac(3), dc(1);
    // cin >> lc >>  sc >> bc >> jc >> ac >> dc;
    
    //cout << "Enter reservation stations for : LW SW BEQ JALR/RET ADD/NEG/ADDI DIV:";
    int lr(2), sr(2), br(1), jr(1), ar(3), dr(1);
   // cin >> lr >> sr >> br >> jr >> ar >> dr;

    Tomasulu tomasulu(lr, sr, br, jr, ar, dr, "./instructions.txt", lc, sc, bc, jc, ac, dc);
    tomasulu.extract_instructions();
    tomasulu.rename_instructions();
    tomasulu.simulate();


    return 0;
}