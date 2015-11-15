-module(kitty2).
-export([start_link/0, order_cat/4, return_cat/1, close_shop/1]).
-export([init/1, handle_call/3, handle_cast/2]).

-record(cat, {name, color=green, desc}).

start_link() -> my_server:start_link(?MODULE, []).

order_cat(Pid, Name, Color, Desc) ->
    my_server:call(Pid, {order, Name, Color, Desc}).

return_cat({Pid, Cat = #cat{}}) ->
    my_server:cast(Pid, {return, Cat}).

close_shop(Pid) ->
    my_server:call(Pid, terminate).


init([]) -> [].

handle_call({order, Name, Color, Desc}, From, Cats) ->
    if Cats =:= [] ->
         my_server:reply(From, make_cat(Name, Color, Desc)),
         Cats;
       Cats =/= [] ->
         my_server:reply(From, hd(Cats)),
         tl(Cats)
    end;

handle_call(terminate, From, Cats) ->
    my_server:reply(From, ok),
    terminate(Cats).

handle_cast({return, Cat = #cat{}}, Cats) -> [Cat|Cats].

make_cat(Name, Color, Desc) ->
    #cat{name=Name, color=Color, desc=Desc}.

terminate(Cats) ->
    [io:format("~p was set free.~n", [C#cat.name]) || C <- Cats],
    ok.
              



