-module(geometry) .
-export([area/1]) .

area({rectangle, Width, Height}) -> Width * Height;
area({circle, R}) -> R * R * 3.14 .
