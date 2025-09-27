#include <stdio.h>
#include <unistd.h>
#include <termios.h> // library for terminal
#include <ctype.h>

void setRawMode(){

    // also CTRL-S and CTRL-Q functionalities disabled - using IXOFF and IXON from termios.h
    
    struct termios termios_struct;

    int echo_bit_flag = ECHO;
    int not_echo_bit_flag = ~ECHO;
    int ixoff_ixon = (IXOFF | IXON);

    int tcget = tcgetattr(STDIN_FILENO, &termios_struct); // tcgetattr - get the parameters associated with the terminal

    termios_struct.c_lflag = not_echo_bit_flag & tcget;
    termios_struct.c_iflag = ~(ixoff_ixon);

    // termios_struct.c_oflag = ~(OPOST);


    //now we will set the terminal in raw mode by passing new params to it
    tcsetattr(STDIN_FILENO, TCSANOW, &termios_struct);

    
    // printf("echo_bit_flag = %d\ntcget = %d", echo_bit_flag, tcget);

}

void setCanonicalMode(){
    struct termios termios_struct;
    int echo_bit_flag = ECHO;
    int tcget = tcgetattr(STDIN_FILENO, &termios_struct); // tcgetattr - get the parameters associated with the terminal
    termios_struct.c_lflag = echo_bit_flag;

    int ixoff_ixon = (IXOFF | IXON);
    termios_struct.c_iflag = (ixoff_ixon);
    
    termios_struct.c_oflag = (OPOST);

    tcsetattr(STDIN_FILENO, TCSANOW, &termios_struct);

}


int main(void){
    char c;

    setRawMode();
    printf("\n\n\n\n");

    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){  // once a q is found -> program stop
        if (iscntrl(c))
            printf("%d\n", c);
        else
            printf("%d ('%c')\n", c, c);

  }


    setCanonicalMode();


}