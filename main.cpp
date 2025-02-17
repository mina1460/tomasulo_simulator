
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
    - Does not take 1 clock cycle execution time
    ✔︎ - JALR does not reissue instructions after jumping backwards
    ✔︎ - LW rs1 dependancy stalls execution
    ✔︎ - SW rs2 dependancy stalls execution
    ✔︎ - Try RET, NEG, DIV   
    ✔︎ - Add another stopping condition
    ✔︎ - Try BEQ 
    ✔︎ - First instruction takes 1 extra cycle in execution
    ✔︎ - User enters starting program's address 

*/


int main(){

    int lc(2), sc(2), bc(1), jc(2), ac(3), dc(6);
    int address;
    int num, val;
    
    cout << "Usage: place instructions in a file called \"instructions.txt\" \n";
    cout << "Enter first instruction address: ";
    cin >> address;

    cout << "Enter cycles for executing: \n";
    cout << "\tLW : \t" ;
    cin >> lc;
    cout << "\tSW : \t";
    cin >> sc;
    cout << "\tBEQ : \t";
    cin >> bc;
    cout << "\tJALR/RET : \t";
    cin >> jc;
    cout << "\tADD/NEG/ADDI : \t";
    cin >> ac;
    cout << "\tDIV : \t";
    cin >> dc;
    
 
    int lr(1), sr(1), br(1), jr(1), ar(3), dr(1);
    cout << "Enter reservation station numbers for : \n";
    cout <<  "\tLW : \t" ;
    cin >> lr;
    cout << "\tSW : \t";
    cin >> sr;
    cout << "\tBEQ : \t";
    cin >> br;
    cout << "\tJALR/RET : \t";
    cin >> jr;
    cout << "\tADD/NEG/ADDI : \t";
    cin >> ar;
    cout << "\tDIV : \t";
    cin >> dr;

    
    Tomasulu tomasulu(lr, sr, br, jr, ar, dr, "./instructions.txt", lc, sc, bc, jc, ac, dc, address);
    tomasulu.extract_instructions();
    
    cout << "Enter amount of data to add to memory: ";
    cin >> num;
    for (int i=0; i<num; i++){
        cout << "Data " << i+1 << "\n";
        cout << "\tEnter address: ";
        int address;
        cin >> address;
        cout << "\tEnter data: ";
        cin >> val;
        tomasulu.addToMem (val, address);
    }


    tomasulu.simulate();


    return 0;
}