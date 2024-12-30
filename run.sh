#!/bin/zsh

# Compile
g++ -std=c++11 \
-I/opt/homebrew/Cellar/crow/1.2.0/include \
-I/opt/homebrew/opt/asio/include \
-I/opt/homebrew/Cellar/mysql-connector-c++/9.1.0/include \
-L/opt/homebrew/Cellar/mysql-connector-c++/9.1.0/lib \
-lmysqlcppconnx \
-o server server.cpp
# Running
./server

# Alias is compilerest
