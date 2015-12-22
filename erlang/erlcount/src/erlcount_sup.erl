-module(erlcount_sup).
-behaviour(supervisor).
-export([start_link/0, init/1]).

start_link() ->
    supervisor:start_link(?MODULE, []).

init([]) ->
    {ok, {{one_for_one, 5, 100},
     [{dispatch,
       {erlcount_dispatch, start_link, []},
       transient,
       60000,
       worker,
       [erlcount_dispatch]}]}}.
