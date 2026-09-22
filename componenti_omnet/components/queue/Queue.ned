package components.queue;

simple Queue
{
    parameters:
        @display("i=block/queue");

        // Service Rule parameters
        int a1;            // minimo batch classe1
        int b1;            // massimo batch classe1
        int a2;            // minimo batch classe2
        int b2;            // massimo batch classe2

        // Service time parameters
        double sp1;        // deterministico classe1
        double l1;         // limite inferiore uniforme classe1
        double u1;         // limite superiore uniforme classe1
        double sp2;        // deterministico classe2
        double l2;         // limite inferiore uniforme classe2
        double u2;         // limite superiore uniforme classe2

        // Vacation / Setup parameters
        double sv;         // vacation scaling
        double z;          // limite inferiore uniforme vacation
        double w;          // limite superiore uniforme vacation
        double h;          // media esponenziale setup
        int N;             // soglia utenti classe1 per setup

	gates:
        input inSource[2];        // da Source
        input inServer;	 // da Server
        output out;      // verso Server
}