cmake_minimum_required(VERSION 3.0.0)
project(blackjack VERSION 0.1.0)
include_directories("./include")
add_executable(blackjack "src/BlackJack.cpp" "src/Karte.cpp" "src/Spieler.cpp")

