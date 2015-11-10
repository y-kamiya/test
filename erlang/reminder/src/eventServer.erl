-module(eventServer).
-compile(export_all).

-record(state, {events,
                clients}).

-record(event, {name="",
                description="",
                pid,
                timeout=0}).

loop(S = #state{}) ->
    receive
        {Pid, MsgRef, {subscribe, Client}} ->
            Ref = erlang:monitor(process, Client),
            NewClients = orddict:store(Ref, Client, S#state.clients),
            Pid ! {MsgRef, ok},
            loop(S#state{clients=NewClients});
        {Pid, MsgRef, {add, Name, Desc, Timeout}} ->
            EventPid = event:start_link(Name, Timeout),
            Event = #event{name=Name,
                           description=Desc,
                           pid=EventPid,
                           timeout=Timeout},
            Events = orddict:store(Name, Event, S#state.events),
            Pid ! {MsgRef, ok},
            loop(S#state{events=Events});
        {Pid, MsgRef, {cancel, Name}} ->
            Events = case orddict:find(Name, S#state.events) of
                         {ok, E} -> 
                             event:cancel(E#event.pid),
                             orddict:erase(Name, S#state.events);
                         error ->
                             S#state.events
                     end,
            Pid ! {MsgRef, ok},
            loop(S#state{events=Events});
        {done, Name} ->
            Event = orddict:fetch(Name, S#state.events),
            orddict:map(fun (_Ref, Client) -> Client ! {done, Name, Event#event.description} end, S#state.clients),
            Events = orddict:erase(Name, S#state.events),
            loop(S#state{events=Events});
        shutdown ->
            exit(shutdown);
        {'DOWN', Ref, process, _Pid, _Reason} ->
            orddict:erase(Ref, S#state.clients);
        code_change ->
            ?MODULE:loop(S);
        Unknown ->
            io:format("Unkonw message: ~p~n", [Unknown]),
            loop(S)
    end.

init() ->
    loop(#state{events=orddict:new(),
                clients=orddict:new()}).    

start() ->
    register(?MODULE, Pid=spawn(?MODULE, init, [])),
    Pid.

start_link() ->
    register(?MODULE, Pid=spawn_link(?MODULE, init, [])),
    Pid.

terminate() ->
    ?MODULE ! shutdown.

subscribe(Pid) ->
    Ref = erlang:monitor(process, whereis(?MODULE)),
    ?MODULE ! {self(), Ref, {subscribe, Pid}},
    receive
        {Ref, ok} ->
            {ok, Ref};
        {'DOWN', Ref, process, _Pid, Reason} ->
            {error, Reason}
    after 5000 ->
        {error, timeout}
    end.

add_event(Name, Description, Timeout) ->
    Ref = make_ref(),
    ?MODULE ! {self(), Ref, {add, Name, Description, Timeout}},
    receive
        {Ref, Msg} -> Msg
    after 5000 ->
        {error, timeout}
    end.

cancel(Name) ->
    Ref = make_ref(),
    ?MODULE ! {self(), Ref, {cancel, Name}},
    receive
        {Ref, ok} -> ok
    after 5000 ->
        {error, timeout}
    end.

listen(Delay) ->
    receive
        M = {done, _Name, _Description} ->
            [M | listen(0)]
    after Delay * 1000 ->
            []
    end.
