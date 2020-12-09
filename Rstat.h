#ifndef RSTAT_H_
#define RSTAT_H_

#include "includes.h" 
class Rstat
{
private:
    bool busy;
    int Q; 
    int index; 
public:
    Rstat();
    void setQ(int x, int y);
    void setBusy(bool b);
    bool getBusy();
    int getIndex();
    int getQ ();
    ~Rstat();
};


#endif
