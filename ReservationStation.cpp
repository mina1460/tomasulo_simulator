#include "ReservationStation.h"

ReservationStation::ReservationStation (string p_name){
        name = p_name;
}
void ReservationStation::resetRS (){
        id = -1;
        busy = false;
        op.clear();
        Vj = 0;
        Vk = 0;
        imm = 0;
        Qj = -1;
        Qk = -1;
        address = 0;
        instruction_number = - 1; 
        ready = false; 
        result = 0;
}
// bool ReservationStation::get_busy (){
//         return busy;
// }
// int ReservationStation::get_Vj (){
//         return Vj;
// }
// int ReservationStation::get_Vk (){
//         return Vk;
// }
// int ReservationStation::get_Qj (){
//         return Qj; 
// }
// int ReservationStation::get_Qk (){
//         return Qk;
// }
// void ReservationStation::set_Vj (int p_vj){
//         Vj = p_vj;
// }
// void ReservationStation::set_Vk (int p_vk){
//         Vk = p_vk;
// }
// void ReservationStation::set_Qj (int p_qj){
//         Qj = p_qj;
// }
// void ReservationStation::set_Qk (int p_qk){
//         Qk = p_qk;
// }
