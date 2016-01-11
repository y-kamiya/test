-module(naive_tcp).
-compile(export_all).

start_server(Port) ->
    Pid = spawn_link(fun() ->
        {ok, ListenSocket} = gen_tcp:listen(Port, [binary, {active, false}]),
        spawn(fun() -> acceptor(ListenSocket) end),
        timer:sleep(infinity)
    end),
    {ok, Pid}.
    
acceptor(ListenSocket) ->
    {ok, AcceptSocket} = gen_tcp:accept(ListenSocket),
    spawn(fun() -> acceptor(ListenSocket) end),
    handle(AcceptSocket).

handle(AcceptSocket) ->
    inet:setopts(AcceptSocket, [{active, once}]),
    receive
        {tcp, AcceptSocket, <<"quit", _/binary>>} ->
            gen_tcp:close(AcceptSocket);
        {tcp, AcceptSocket, Msg} ->
            gen_tcp:send(AcceptSocket, Msg),
            handle(AcceptSocket)
    end.

