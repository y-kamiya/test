-module(ppool_supersup).
-behaviour(supervisor).
-export([start_link/0, start_pool/3, stop_pool/1]).
-export([init/1]).

start_link() ->
    supervisor:start_link({local, ppool}, ?MODULE, []).

init([]) ->
    {ok, {{one_for_one, 3, 3600}, []}}.
% why one_for_one?
%[{ppool_sup, ppool_sup:start_link, permanent, brutal_kill, supervisor, ppool_sup}]}}.

start_pool(Name, Limit, MFA) ->
    ChildSpec = {Name,
                 {ppool_sup, start_link, [Name, Limit, MFA]},
                 permanent, 10500, supervisor, [ppool_sup]},
    supervisor:start_child(ppool, ChildSpec).

stop_pool(Name) ->
    supervisor:terminate_child(ppool, Name),
    supervisor:delete_child(ppool, Name).

