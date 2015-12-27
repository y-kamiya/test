-module(tcp_server).
-export([start_link/1]).

start_link(ListenSocket) ->
    io:format("tcp_server~n", []),
    spawn_link(fun() -> accept(ListenSocket) end),
    {ok, self()}.

accept(ListenSocket) ->
    io:format("accept ~p~n", [ListenSocket]),
    {ok, AcceptSocket} = gen_tcp:accept(ListenSocket),
    spawn_link(fun() -> accept(ListenSocket) end),
    handle(AcceptSocket).

handle(AcceptSocket) ->
    io:format("handle ~p~n", [AcceptSocket]),
    inet:setopts(AcceptSocket, [{active, once}]),
    receive
        {tcp, AcceptSocket, <<"quit", _/binary>>} ->
            gen_tcp:close(AcceptSocket);
        {tcp, AcceptSocket, Msg} ->
            gen_tcp:send(AcceptSocket, Msg),
            handle(AcceptSocket)
    end.



