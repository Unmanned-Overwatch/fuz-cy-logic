@echo off
if exist %1.lis erase %1.lis
bcc -c -ml -Ff=16 %1.cpp > %1.lst
k %1.lst
