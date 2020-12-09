
#include "includes.h"
#include "Instruction.h"
#include "ReservationStation.h"
#include "Tomasulu.h"


/*
g++ -I . main.cpp Instruction.cpp ReservationStation.cpp Tomasulu.cpp Rstat.cpp -o main.exe
After Register Renaming
    Issue:      If there is a free reservation station
    Execute:    When both operands are ready (RaW) & branch outcome known
    Write:      After execution, NO condition       
http://people.ee.duke.edu/~sorin/ece252/lectures/4.2-tomasulo.pdf
*/


int main(){

    //cout << "Enter cycles for : LW SW BEQ JALR/RET ADD/NEG/ADDI DIV:";
    int lc(1), sc(1), bc(1), jc(1), ac(3), dc(1);
    // cin >> lc >>  sc >> bc >> jc >> ac >> dc;
    
    //cout << "Enter reservation stations for : LW SW BEQ JALR/RET ADD/NEG/ADDI DIV:";
    int lr(1), sr(1), br(1), jr(1), ar(3), dr(1);
   // cin >> lr >> sr >> br >> jr >> ar >> dr;

    cout << "Begin\n";
    Tomasulu tomasulu(lr, sr, br, jr, ar, dr, "./instructions.asm", lc, sc, bc, jc, ac, dc);
    cout << "created object\n";
    tomasulu.extract_instructions();
    cout << "extracted\n";
    tomasulu.rename_instructions();
    cout << "renamed\n";
    tomasulu.simulate();


    return 0;
}