-module(ppool_sup).
-behaviour(supervisor).
-export([start_link/3, init/1]).

start_link(Name, Limit, MFA) ->
    supervisor:start_link(?MODULE, {Name, Limit, MFA}).

init({Name, Limit, MFA}) ->
    ChildSpec = {serv,
                 {ppool_serv, start_link, [Name, Limit, self(), MFA]},
                 permanent,
                 5000,
                 worker,
                 [ppool_serv]},
    {ok, {{one_for_all, 1, 3600}, [ChildSpec]}}.

