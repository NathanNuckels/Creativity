//commodore 64 serial port crap



//COMMODORE 64 ALTERNATIVE KERNEL

//Function 001: Send stuff over serial port

/*NOTES
0=ro 1=rw

$DD00 ...ACDcd
$DD02 11.11100

A - Attention
C - Clock
D - Data
c - Clock In
d - Data In

1. Set attention to 0 "Listen up!"
2. Send device number "Yo disk drive, you here?"
3. Wait for reply "yup" (d=0) [verify]
4. Send seccondary address "You got the file I wanted?"
5. Wait for reply [verify] "ye" (d=0) [verify]
6. Set attention high "Alright."

7. Communicate as usual.

Send a char:
0. Clock is 0, data is 0.
1. Release clock (C=1) "C: Imma send a bit"
2. Listener must release data (d=1) "8: Alright I'm ready."
3. Talker pulls clock (C=0) (Must be done within 0.0002 secconds) "Ok, here you go"
4. Set data to the opposite of the least segnificant bit. "I have a one for you"
5. Release clock (C=1) "Ok, here's the one."
6. Wait 0.00002 secconds to make sure listener catches it
(If the listener is the Commodore 64, hold it for 0.00006 secconds)
(VIC-II chip can interupt the processor every 0.000042s so the longer wait makes sure the 64 gets the bit.)
7. Go to the next segnificant bit and goto 4
8. After the 8th bit, (C=0 d=1) Listener pulls data to acknoledge (d=0)
9. If listener dosn't ACK within 0.001s, you messed up.
10. goto 0

Send the LAST char: (EOI)
0. Clock is 0, data is 0
Same as above...
3. Talker does nothing (0.0002 secconds passes, nothing happens) "Hey, this is the last one."
4. Listener Pulls data for 0.00006 secconds (d=0) and releases it (d=1) "ok"
5. Talker has 0.00006 secconds to pull clock (C=0) "Alright here it is."
6. Continue as usual. This is the final char to be transmitted.

Handshake commands:

(Must be sent with ATTENTION pulled, A=0)
Device, Listen, Chanel, Open (in that order)
Also, untalk and unlisten.
[TODO: Say what these commands actually look like by analizing the kernel]



Open a file:
(A=0) DEVICE; LISTEN; CHANNEL; OPEN;
(A=1) FILENAME; EOI;
(A=0) DEVICE; UNLISTEN;

Send stuff (in a file):
(A=0) DEVICE; LISTEN; CHANNEL; DATA
(A=1) data........; EOI;
(A=0) DEVICE; UNLISTEN;

Close file:
(A=0) DEVICE; LISTEN; CHANNEL; CLOSE;
(A=0) DEVICE; UNTALK;
device MAY NOT send EOI

TURNARROUND:
Computer sends a talk command to DEVICE, releases attention, then this happens:
0. Device becomes a listener
1. The data line is pulled low by the device and clock is pulled by CPU
2. CPU pulls the data line (even though its already pulled) (D=0)
and releases the clock line (C=1,D=0)
3. device releases data line and pulls clock line (d=0,c=0) (d=0 cause D=0)

*/

//KERNAL ANALYSIS
#include<c64.h>
#define ENABL *(0x2A1)
#define C3P0 *(0x94)
#define R2D2 *(0xA3)
#define COUNT *(0xA5)

#define CHARBUF C3P0
#define EOISWITCH R2D2
 
void W1MS(){
    __asm__("stuff");
}

//returns one bit.
char KERNEL_DEBPIA(){
    //Debounce the pia.
    char x=CIA2.pra;
    while(x!=CIA2.pra)x=CIA2.pra;
    return CIA2.pra&0x40;
}

void K_ISOUR(){
            //JSR $ED40
        __asm__("sei"); //No interupts
        CIA2.pra|=32; //DATA=HIGH
        if(KERNEL_DEBPIA()) //"debounce PIA"
            goto NODEV;
        CIA2.pra&=0xEF; //CLOCK=HIGH
        if(R2D2&CIA2.pra<0){ //Do EOI
            while(KERNEL_DEBPIA()==0); //wait for data high
            while(KERNEL_DEBPIA()==1); //wait for data low
        }
        while(KERNEL_DEBPIA()==0); //wait for data high
        CIA2.pra|=16; //CLOCK LOW
        
        COUNT=8;
        ISR01:
        if(KERNEL_DEBPIA()==0){goto FRMERR}
        if(ror(BSOUR)==1){goto ISRHI}
        CIA2.pra|=32; //DATA=LOW
        if(CIA2.pra!=0)goto ISRCLK;
        
        ISRHI: CIA2.pra&=0xDF;//DATAHI
        ISRCLK: CIA2.pra&=0xEF;//CLKHI
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        CIA2.pra=(CIA2.pra&0xDF)|16; //DATA HIGH CLOCK LOW
        COUNT--;
        if(COUNT!=0)goto ISR01;
        CIA2.tb_hi=4; //Set timer for one milliseccond
        CIA2.crb=0x19; //Start timer
        ISR04: if(CIA2.icr&2!=0)goto FRMERR;
        if(KERNEL_DEBPIA()==1)goto ISR04;
        __asm__("cli");
}

void KERNEL_LISTEN(char device){
    //JSR F0A4 //Wait for RS232 to finish so there are no interupts.
    if(ENABL!=0){ 
        while(ENABL&3==0);
        CIA2.icr=16;
        ENABL=0;
    } //RTS
    if((device|0x20)&C3P0<0){
        //set carry
        ror(R2D2); //Rotate right
        //send last char
        K_ISOUR();
        //RTS
        C3P0<<=1;
        R2D2<<=1;
        BSOUR=device|0x20;
        __asm__("sei");
        CIA2.pra&=0xDF; //DATA HIGH
        if(CIA2.pra==3F)CIA2.pra&=0xEF;
        CIA2.pra|=8; //Attention high
        __asm__("sei");
        CIA2.pra|=16; //CLOCK LOW
        CIA2.pra&=0xDF; //DATA HIGH
        W1MS();
        K_ISOUR();
        
        
    }
    //then //copy stuff up untill LIST2
    // 
}


//PROGRAMERS MANUAL ANALISYS:

/*
A: Attention, C: Clock, D: Data.
D and C are computer, d and c are device
Commands on the same time must happen at the same time.

Send with attention:
A=1 C=1 D=?
A=0 (Atention!)
C=0 D=0
C=1
d=1 (Byte accepted)
(When C goes from low to high, data is valid.)
(Send data LSB to MSB)
...
d=0
A=1

Send to listener:
C=0 d=0
C=1 (Ready to send)
d=1 (Listener ready)
   if EOI
     (0.0002 seccond pause)
     d=0 (EOI timeout)
     d=1 (Ready)
(send data same as above)
d=0 (Accepted)

Talk-Attention Turn Arround

A=0 C=0 d=0
A=1 (End attention)
c=1 D=0 (Talker becomes listener)
c=0 (Device ACKs it should TALK)
c=1 (Device ready to TALK)
D=1 (Ready to LISTEN)
(Send data as usual)
*/


/*
UNLISTEN = 3F
UNTALK = 5F
TALK = A|0x40
LISTEN = A|0x20
SECCOND (After listen) = litrly just send the byte.
SECCOND (talk) = send the byte, then JMP TKATN

Open: If seccond<0, done
      Else if no file name, done
      clear status
      tell device to listen
      send seccond
      send file name
      unlisten

TKATN:
    __asm__("sei");
    Data low
    attention high
    Clock high
    DEBOUNCE untill clock is low
    __asm__("cli");
*/

