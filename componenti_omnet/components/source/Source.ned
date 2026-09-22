package components.source;

simple Source
{
    parameters:
        int userClass;                 // 1 oppure 2
        double meanInterArrival;       // m_i
        int batchMin;                  // minimo batch
        int batchMax;                  // massimo batch
        @display("i=block/source");
    gates:
        output out;
}
