SetComm.exe COM6
avrdude.exe -p m8 -c avr910 -P COM6 -b 115200 -U flash:w:"..\Debug\Exe\PIRDVR.a90":a
pause