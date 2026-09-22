cplusplus {{
    #include <omnetpp.h>
}}

packet Job
{
    int userClass;     // classe dell'utente (1 o 2)
    simtime_t arrivalTime;  // tempo di ingresso nel sistema
}
