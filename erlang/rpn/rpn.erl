-module(rpn).
-export([rpn/1, rpn_test/0]).

rpn(Input) when is_list(Input) ->
    Tokens = string:tokens(Input, " "),
    [Res] = lists:foldl(fun rpn/2, [], Tokens),
    Res.

rpn("+", [V1, V2 | S]) -> [V1 + V2 | S];
rpn("sum", S) -> [lists:sum(S)];
rpn(Token, S) -> [read(Token)|S].

read(C) -> list_to_integer(C).

rpn_test() ->
    3 = rpn("1 2 +"),
    6 = rpn("1 2 3 sum"),
    ok = try
             rpn("1 2 3 +")
         catch
             error:{badmatch, [_|_]} -> ok
         end,
    ok.

