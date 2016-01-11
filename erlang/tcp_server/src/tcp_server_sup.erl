-module(tcp_server_sup).
-behaviour(supervisor).
-export([start_server/1, start_child/0]).
-export([init/1]).

start_server(Port) ->
    supervisor:start_link({local, ?MODULE}, ?MODULE, [Port]).

init([Port]) ->
    io:format("~p~n", [erl_syntax:abstract(Port)]),
    {ok, ListenSocket} = gen_tcp:listen(Port, [binary, {active, false}, {packet, line}]),
    spawn_link(fun() -> start_acceptors() end),
    Spec = {tcp_server
            ,{tcp_server, start_link, [ListenSocket]}
            ,temporary
            ,3600
            ,worker
            ,[tcp_server]},
    {ok, {{simple_one_for_one, 60, 3600}, [Spec]}}.

start_child() ->
    io:format("bbbbbb~n", []),
    supervisor:start_child(self(), []).

start_acceptors() ->
    io:format("aaaaaaa~n", []),
    [start_child() || _ <- lists:seq(1,20)],
    ok.
