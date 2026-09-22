package components.server;

simple Server
{
    @display("i=block/server");
    gates:
        input in;   // dalla Queue
        output outSink; // verso Sink
        output outQueue; // verso Queue
}

