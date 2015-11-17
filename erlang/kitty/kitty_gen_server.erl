-module(kitty_gen_server).
-behaviour(gen_server).
-compile(export_all).

-record(cat, {name, color=green, desc}).

start() -> gen_server:start(?MODULE, [], []).
start_link() -> gen_server:start_link(?MODULE, [], []).

order_cat(Pid, Name, Color, Desc) ->
    gen_server:call(Pid, {order, Name, Color, Desc}).

return_cat(Pid, Cat = #cat{}) ->
    gen_server:cast(Pid, {return, Cat}).

close_shop(Pid) ->
    gen_server:call(Pid, terminate).


init([]) -> {ok, []}.

handle_call({order, Name, Color, Desc}, _From, Cats) ->
    if Cats =:= [] ->
         {reply, make_cat(Name, Color, Desc), Cats};
       Cats =/= [] ->
         {reply, hd(Cats), tl(Cats)}
    end;

handle_call(terminate, _From, Cats) ->
    {stop, normal, ok, Cats}.

handle_cast({return, Cat = #cat{}}, Cats) -> 
    {noreply, [Cat|Cats]}.

handle_info(Msg, Cats) ->
    io:format("Unexpected message: ~p~n",[Msg]),
    {noreply, Cats}.

code_change(_OldVsn, State, _Extra) ->
    {ok, State}.

% private
make_cat(Name, Color, Desc) ->
    #cat{name=Name, color=Color, desc=Desc}.

terminate(normal, Cats) ->
    [io:format("~p was set free.~n", [C#cat.name]) || C <- Cats],
    ok.
              





