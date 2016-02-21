import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class ServerState {

    private Map<String, ClientState> clientMap = new ConcurrentHashMap<String, ClientState>();

    public synchronized void addClient(String name, ClientState clientState) {
        clientMap.put(name, clientState);
    }

    public synchronized void removeClient(String name) {
        clientMap.remove(name);
    }

    public boolean isNameDuplicate(String name) {
        return clientMap.containsKey(name);
    }

    public void broadcast(Message message) {
        clientMap.forEach((name, clientState) -> {
            clientState.sendMessage(message);
        });
    }

    public void tell(String name, Message message) {
        ClientState clientState = clientMap.get(name);
        if (clientState == null) {
            return;
        }
        clientState.sendMessage(message);
    }
}

