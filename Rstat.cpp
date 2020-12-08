#include "Rstat.h"


Rstat::Rstat()
{
    busy = false;
    Q = 0;
    index = 0;
}
void Rstat::setQ(int x, int y){
        busy = true;
        index = x;
        Q = y;
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