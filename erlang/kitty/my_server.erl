-module(my_server).
-compile(export_all).

call(Pid, Msg) ->
    Ref = erlang:monitor(process, Pid),
    Pid ! {sync, self(), Ref, Msg},
    receive
        {Ref, Reply} ->
            erlang:demonitor(Ref, [flush]),
            Reply;
        {'DOWN', Ref, process, Pid, Reason} ->
            erlang:error(Reason)
    after 5000 ->
        erlang:error(timeout)
    end.

cast(Pid, Msg) ->
    Pid ! {async, Msg},
    ok.

loop(Module, State) ->
    receive
        {sync, Pid, Ref, Msg} -> 
            loop(Module, Module:handle_call(Msg, {Pid, Ref}, State));
        {async, Msg} -> 
            loop(Module, Module:handle_cast(Msg, State))
    end.

reply({Pid, Ref}, Msg) ->
    Pid ! {Ref, Msg}.

start(Module, InitialState) ->
    spawn(fun() -> init(Module, InitialState) end).

start_link(Module, InitialState) ->
    spawn_link(fun() -> init(Module, InitialState) end).

init(Module, InitialState) ->
    loop(Module, Module:init(InitialState)).
