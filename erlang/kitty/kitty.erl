-module(kitty).
-export([start_link/0, order_cat/4, return_cat/1, close_shop/1]).
-record(cat, {name, color=green, desc}).

start_link() -> spawn_link(fun init/0).

order_cat(Pid, Name, Color, Desc) ->
    Ref = erlang:monitor(process, Pid),
    Pid ! {self(), Ref, {order, Name, Color, Desc}},
    receive
        {Ref, Cat} ->
            erlang:demonitor(Ref, [flush]),
            Cat;
        {'DOWN', Ref, process, Pid, Reason} ->
            erlang:error(Reason)
    after 5000 ->
        erlang:error(timeout)
    end.

return_cat({Pid, Cat = #cat{}}) ->
    Pid ! {return, Cat},
    ok.

close_shop(Pid) ->
    Ref = erlang:monitor(process, Pid),
    Pid ! {self(), Ref, terminate},
    receive
        {Ref, ok} ->
            erlang:demonitor(Ref, [flush]),
            ok;
        {'DOWN', Ref, process, Pid, Reason} ->
            erlang:error(Reason)
    after 5000 ->
        erlang:error(timeout)
    end.

init() -> loop([]).

loop(Cats) ->
    receive
        {Pid, Ref, {order, Name, Color, Desc}} ->
            if Cats =:= [] ->
                 Pid ! {Ref, make_cat(Name, Color, Desc)},
                 loop(Cats);
               Cats =/= [] ->
                 Pid ! {Ref, hd(Cats)},
                 loop(tl(Cats))   
            end;
        {return, Cat = #cat{}} ->
            loop([Cat|Cats]);
        {Pid, Ref, terminate} -> 
            Pid ! {Ref, ok},
            terminate(Cats);
        Unknown ->
            io:format("Unknown message: ~p~n", [Unknown]),
            loop(Cats)
    end.

make_cat(Name, Color, Desc) ->
    #cat{name=Name, color=Color, desc=Desc}.

terminate(Cats) ->
    [io:format("~p was set free.~n", [C#cat.name]) || C <- Cats],
    ok.
              



