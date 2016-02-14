import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class ServerState {

    private Map<String, ClientState> clientMap = new ConcurrentHashMap<String, ClientState>();

    public synchronized void addClient(String name, ClientState clientState) {
    	clientMap.put(name, clientState);
    }

    public boolean isNameDuplicate(String name) {
    	return clientMap.containsKey(name);
    }
}

