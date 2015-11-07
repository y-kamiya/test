-module(message).
-compile(export_all).

message() ->
    receive
        hello ->
            io:format("hi.~n");
        color ->
            io:format("red.~n");
        _ ->
            io:format("i dont know this word.~n")
    end.

message2() ->
    receive
        {From, hello} ->
            From ! "hi.~n",
            message2();
        {From, color} ->
            From ! "red.~n";
        _ ->
            io:format("i dont know this word.~n"),
            message2()
    end.

