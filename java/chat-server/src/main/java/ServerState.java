import java.io.BufferedWriter;
import java.util.Map;
import java.util.HashMap;
import java.util.Collection;

public class ServerState {

    private int factor;
    private Map<String, BufferedWriter> clientMap = new HashMap<String, BufferedWriter>();

    public ServerState(int initialFactor) {
        this.factor = initialFactor;
    }

    public synchronized int getFactor() { 
        return this.factor;
    }

    public synchronized int setFactor(int factor) {
        return this.factor = factor;
    }

    public synchronized Collection<BufferedWriter> getAllClient() {
        return this.clientMap.values();
    }

    public synchronized BufferedWriter getClientById(String id) {
        return this.clientMap.get(id);
    }

    public synchronized void removeClient(String id) {
        this.clientMap.remove(id);
    }

    public synchronized void addClient(String id, BufferedWriter writer) {
        this.clientMap.put(id, writer);
    }

}

