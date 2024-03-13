SetComm.exe COM8
avrdude.exe -p m8 -c avr910 -P COM8 -b 115200 -U flash:w:"..\Release\Exe\PIRDVR.a90":a
pause