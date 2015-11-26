-module(dog).
-compile(export_all).
-behaviour(gen_fsm).

start() ->
    gen_fsm:start(?MODULE, [], []).

init(_Args) ->
    {ok, sitting, []}.

sitting(squirrel, _StateData) ->
    io:format("dog find squirrel~n"),
    {next_state, bark, []};
sitting(dogfood, _StateData) ->
    io:format("dog find dogfood~n"),
    {next_state, eating, []};
sitting(Event, _StateData) ->
    io:format("unknown event ~p received when sitting~n", [Event]),
    {next_state, sitting, []}.

bark(dogfood, _StateData) ->
    io:format("dog find dogfood, so stop to bark~n"),
    {next_state, eating, []};
bark(Event, _StateData) ->
    io:format("unknown event ~p received when bark~n", [Event]),
    {next_state, bark, []}.

eating(wait, _StateData) ->
    io:format("dog is said to wait to eat~n"),
    {next_state, sitting, []};
eating(Event, _StateData) ->
    io:format("unknown event ~p received when eating~n", [Event]),
    {next_state, eating, []}.


code_change(_OldVersion, _StateName, _Data, _Extra) ->
    {ok, sitting, []}.
handle_event(lion, StateName, []) ->
    io:format("dog find lion, so dog stop to ~p and start to bark~n", [StateName]),
    {next_state, bark, []}.
handle_info(_A, _B, _C) ->
    io:format("unknown things occurred~n"),
    {stop, "dog is confused~n"}. 
handle_sync_event(lion, From, _StateName, []) ->
    gen_fsm:reply("dog start to bark", From),
    {next_state, bark, []}.
terminate(Reason, StateName, _Data) ->
    io:format("terminated because ~p when ~p~n", [Reason, StateName]).


squirrel(Pid) ->
    gen_fsm:send_event(Pid, squirrel).

dogfood(Pid) ->
    gen_fsm:send_event(Pid, dogfood).

wait(Pid) ->
    gen_fsm:send_event(Pid, wait).

lion(Pid) ->
    gen_fsm:send_event(Pid, lion).

