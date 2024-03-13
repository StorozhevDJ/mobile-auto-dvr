# Automatic DVR powered from solar battery with ATMega 8 MCU #

Control board based on the ATMega 8 MCU with a connected MD80 mini camera.
For activate power and record used PIR sensor HC-SR501 connecting over BC847 transistor to Pin D2 (INT0) MCU.
Additional battery are is parallel connected to MD80 batterey over charging board. 5V solar panel conect to charging board with 4056 IC and battery protect circuit.

Control and signal diagram

```
Step              01    2 3   4     5   6                7    8      9   10
Pir sensor      __/"""""""""""""""\__________/""""\_____________________________
Blue Led        ________/""""""""""""""""""""""""""""""""""""""""""""""""\______
Red Led         ______________/""\______/""\__/""\__/""\______/\/\/\____________
Power button    ___/""""""\__________________________________________/"\________
Rec buttton     ____________________/""\_________________/""\___________________
```
