#include "Rstat.h"


Rstat::Rstat()
{
    busy = false;
    Q = -1;
    index = -1;
}
void Rstat::setQ(int x, int y){
        busy = true;
        index = x;
        Q = y;
}
void Rstat::setNOTBusy (){
        busy = false;
}
void Rstat::setBusy(bool b){
        busy = b;
}  
bool Rstat::getBusy(){
        return busy;
}

int Rstat::getQ (){
        return Q;
}
int Rstat::getIndex(){
    return index; 
}

Rstat::~Rstat()
{
}