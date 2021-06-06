@echo off
@echo Test %2
@echo Test %2 >> result.txt
copy %2 cicle.in > nul
timer %1 2000 65536 >> result.txt
check %2 %2.a cicle.out >> result.txt
if exist cicle.in del cicle.in
if exist cicle.out del cicle.out