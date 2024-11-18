#!/bin/zsh

# Compile
g++ -std=c++11 -I/opt/homebrew/Cellar/crow/1.2.0/include -I/opt/homebrew/opt/asio/include -o server server.cpp

# Running
./server

# Alias is compilerest
