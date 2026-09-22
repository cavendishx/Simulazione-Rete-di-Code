import org.omnetpp.queueing.Clone;
import components.server.Server;
import components.source.Source;
import components.queue.Queue;
import components.sink.Sink;


network Net
{
    @display("bgb=369,326");
    submodules:

        source1: Source {
            @display("p=32,82");
        }

        source2: Source {
            @display("p=32,190");
        }

        queue: Queue {
            @display("p=126,136");
        }

        server: Server {
            @display("p=228,136");
        }

        sink: Sink {
            @display("p=313,136");
        }

    connections:
        source1.out --> queue.inSource[0];
        source2.out --> queue.inSource[1];
        queue.out --> server.in;
        server.outSink --> sink.in;
        server.outQueue --> queue.inServer;
}
