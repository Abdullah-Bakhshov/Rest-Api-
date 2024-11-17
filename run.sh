#!/bin/zsh

g++ -std=c++11 -I/opt/homebrew/Cellar/crow/1.2.0/include -I/opt/homebrew/opt/asio/include -o my_program main.cpp
# Add any necessary linking flags if needed, like -L/some/library/path -lsomeLibrary
./my_program

# Alias is compilerest
