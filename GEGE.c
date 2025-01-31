/*****************DEFINES***********************************/
#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#define CTRL_KEY(K) ((K) & 0X1F)
#define ABUF_INIT {NULL,0}
#define TEXT_EDITOR "0.0.1"

/*****************INCLUDES***********************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/types.h>>

/*****************DATA***************************************/


enum KEYS
{
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    PAGE_UP,
    PAGE_DOWN,
    HOME_KEY,
    END_KEY,
    DELETE_KEY

};

typedef struct RowSaver 
{
    int str_len;
    char *str;

} rowSave;



struct WinConfig
{
    int cursor_x;
    int cursor_y;
    int rows;
    int cols;
    int numrows;
    rowSave *incoming_text;
    struct termios orig_state;
};

struct ABUF
{
    char *str_buff;
    int len;
};


struct WinConfig DefaultWindowSetting;

void disableRawMode();
void enableRawMode();
void errorHandlingStatus(const char *str);
int readEditorKey();
void pressEditorKey();
void clearScreen();
void drawRows(struct ABUF *buffer); 
int getWindowSize(int *rows,int *cols);
int initStartScreen();
int getCursorPosition(int *rows,int *cols);
void appendBuffer(struct ABUF *buff,const char* str, int len);
void freeBuffer(struct ABUF *buff);
void moveCursor(int key);
void openText(char *filename);
void appendRow(char* row,int len);


/******************FUNCS_REALIZATION**************************/

void appendRow(char* row,int len)
{
    DefaultWindowSetting.incoming_text = realloc(DefaultWindowSetting.incoming_text,sizeof(DefaultWindowSetting.incoming_text)  * ((DefaultWindowSetting.numrows + 1 )*2));
    
    int index = DefaultWindowSetting.numrows;

    DefaultWindowSetting.incoming_text[index].str_len = len;
    DefaultWindowSetting.incoming_text[index].str = (char*)malloc(len+1);

    memcpy(DefaultWindowSetting.incoming_text[index].str,row,len);

    DefaultWindowSetting.incoming_text[index].str[len] = '\0';
    ++DefaultWindowSetting.numrows;
}

void openText(char *filename)
{
    FILE *file_to_open = fopen(filename,"r");

    if(!file_to_open)
    {
        errorHandlingStatus("OPENTEXT: FILE IS NOT EXIST OR CANNOT OPEN");
    }
    
    char *line = NULL;
    ssize_t line_cap = 0;
    ssize_t len_line;


    
        while ((len_line = getline(&line,&line_cap,file_to_open)) != -1)
        {
            
            while(len_line > 0 && (line[len_line-1] == '\r' || line[len_line-1] == '\n'))
            {
               --len_line;
            }


            appendRow(line,len_line);
        
        }
    

    free(line);
    fclose(file_to_open);

}

void moveCursor(int key)
{
    switch (key)
    {

    case ARROW_UP:
        if(DefaultWindowSetting.cursor_y != 0)
        {       
            --DefaultWindowSetting.cursor_y;
        }
        break;
    case ARROW_LEFT:
        if(DefaultWindowSetting.cursor_x != 0)
        {
            --DefaultWindowSetting.cursor_x;
        }
        break;
    case ARROW_DOWN:
        if(DefaultWindowSetting.cursor_y != DefaultWindowSetting.rows -1)
        {
            ++DefaultWindowSetting.cursor_y; 
        }
        break;
    case ARROW_RIGHT:
        if(DefaultWindowSetting.cursor_x != DefaultWindowSetting.cols -1)
        {
            ++DefaultWindowSetting.cursor_x;
        }
        break;
    
    default:
        break;
    }


}
void appendBuffer(struct ABUF *buff,const char* str, int len)
{   
    char* temp_buff = realloc(buff->str_buff,buff->len + len);

    if(temp_buff == NULL)
    {
        return;
       // errorHandlingStatus("APPENDBUFFER:REALLOC FAILED");
    }

    memcpy(&temp_buff[buff->len],str,len);
    buff->str_buff = temp_buff;
    buff->len += len;

}
void freeBuffer(struct ABUF *buff)
{
    free(buff->str_buff);
}

int getCursorPosition(int *rows,int *cols)
{
  char buf[32] = {0};
  unsigned int i = 0;

  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
  {
    return -1;
  }
  while (i < sizeof(buf) - 1) 
  {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) 
    {
        break;
    }
    if (buf[i] == 'R') 
    {
        break;
    }

    ++i;
  }
  
  buf[i] = '\0';
  
  if (buf[0] != '\x1b' || buf[1] != '[') 
  {
    return -1;
  }
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) 
  {
    return -1;
  }

  return 0;
}

int initStartScreen()
{
    DefaultWindowSetting.cursor_x = 0;
    DefaultWindowSetting.cursor_y = 0;
    DefaultWindowSetting.numrows = 0;
    DefaultWindowSetting.incoming_text = NULL;
    

    if(getWindowSize(&DefaultWindowSetting.rows,&DefaultWindowSetting.cols) == -1)
    {
        errorHandlingStatus("INIT:FAILED");
    }
}

int getWindowSize(int *rows,int *cols)
{
    struct winsize sizeOfWindow;

    if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&sizeOfWindow) == -1 || sizeOfWindow.ws_col == 0)
    {
        if(write(STDOUT_FILENO,"\x1b[999B\x1b[999C",12) != 12) 
        {
           return -1;
        }

        return getCursorPosition(rows,cols);
    }
    else
    {
        *rows = sizeOfWindow.ws_row;
        *cols = sizeOfWindow.ws_col;
    }


    return 0;

}


void drawRows(struct ABUF *buffer)
{    
    for (size_t y = 0; y < DefaultWindowSetting.rows; ++y)
    {
        if(y >= DefaultWindowSetting.numrows)
        {

            if(DefaultWindowSetting.numrows == 0 && y == DefaultWindowSetting.rows/3)
            {
                char welcome[80] = {0};

                int welcomelen = snprintf(welcome,sizeof(welcome),"TEXT EDITOR %s VERSION ",TEXT_EDITOR);

                if(welcomelen > DefaultWindowSetting.cols)
                {
                    welcomelen = DefaultWindowSetting.cols;
                }

                int padding = (DefaultWindowSetting.cols - welcomelen)/2;

                if(padding)
                {
                    appendBuffer(buffer,"~",1);
                    --padding;
                }

                while(padding)
                {
                    appendBuffer(buffer," ",1);
                    --padding;
                }

                appendBuffer(buffer,welcome,welcomelen);
            }
            else
            {
                appendBuffer(buffer,"~\x1b[K",4);
            }
        }
        else
        {
            int len_str = DefaultWindowSetting.incoming_text[y].str_len;
            if(len_str > DefaultWindowSetting.cols)
            {
                len_str = DefaultWindowSetting.cols;
            }
            appendBuffer(buffer,DefaultWindowSetting.incoming_text[y].str,len_str);

        }

        if (y < DefaultWindowSetting.rows - 1) 
        {
            appendBuffer(buffer, "\r\n", 2);
        }        
    }

}

void clearScreen()
{   
    struct ABUF buffer = ABUF_INIT;
    appendBuffer(&buffer,"\x1b[?25l",6);
    appendBuffer(&buffer,"\x1b[H",3);
    drawRows(&buffer);

    char temp_buff[32] = {0};
    snprintf(temp_buff,sizeof(temp_buff),"\x1b[%d;%dH",DefaultWindowSetting.cursor_y + 1 ,DefaultWindowSetting.cursor_x + 1);
    appendBuffer(&buffer,temp_buff,strlen(temp_buff));
    
    appendBuffer(&buffer,"\x1b[?25h",6);

    write(STDOUT_FILENO,buffer.str_buff,buffer.len);
    freeBuffer(&buffer);
}

int readEditorKey()
{
    int read_status;
    char ch;

    read_status = read(STDIN_FILENO,&ch,1);
    
    if(read_status == -1 && errno != EAGAIN)
    {
        errorHandlingStatus("READ_KEY_EDITOR: READ ERROR");
    }    

    if(ch == '\x1b')
    {
        char esc_seq[24];
        
        if(read(STDIN_FILENO,&esc_seq[0],1) != 1)
        {
            return '\x1b';
        }

        if(read(STDIN_FILENO,&esc_seq[1],1) != 1)
        {
            return '\x1b';
        }

        if(esc_seq[0] == '[')
        {
            if (esc_seq[1] >= '0' &&  esc_seq[1] <= '9')
            {
                if(read(STDIN_FILENO,&esc_seq[2],1) != 1)
                {
                    return '\x1b';
                }
                     
                if(esc_seq[2] == '~')
                {
                    switch (esc_seq[1])
                    {
                           
                        case '6':
                            return PAGE_DOWN;
                            break;

                        case '5':
                            return PAGE_UP;
                            break;
                        
                        case '3':
                            return DELETE_KEY;
                            break;
                            
                        case '1':
                        case '7':
                            return HOME_KEY;
                            break;

                        case '4':
                        case '8':
                            return END_KEY;
                            break;

                        default:
                            break;
                    }
                }
            }
            else if(esc_seq[0] == 'O')
            {
                switch (esc_seq[1])
                {
                    case 'H':
                        return HOME_KEY;
                        break;

                    case 'F':
                        return END_KEY;
                        break;    
                
                    default:
                        break;
                }
            }
            else
            {

                switch(esc_seq[1])
                {
                    case 'A':
                       return ARROW_UP;
                        break;

                    case 'B':
                       return ARROW_DOWN;
                        break;

                    case 'C':
                       return ARROW_RIGHT;
                        break;

                    case 'D':
                       return ARROW_LEFT;
                        break;

                    case 'H':
                        return HOME_KEY;
                        break;

                    case 'F':
                        return END_KEY;
                        break;

                    default:
                        break;
                }
            }
           
        }

        return '\x1b';

    }


    return ch;

}

void pressEditorKey()
{
    int key_press = readEditorKey();

    switch (key_press)
    {
    case CTRL_KEY('Q'):
        write(STDOUT_FILENO,"\x1b[2J\x1b[1;1H",10);
        exit(0);
        break;
    
    case HOME_KEY:
        DefaultWindowSetting.cursor_x = 0;
    break;

    case END_KEY:
        DefaultWindowSetting.cursor_x = DefaultWindowSetting.cols - 1;
    break;

    case DELETE_KEY:
        
    break;


    case PAGE_DOWN:
    case PAGE_UP:
        int times = DefaultWindowSetting.rows;
        while (times)
        {
            moveCursor(key_press == PAGE_DOWN ? ARROW_DOWN : ARROW_UP);
            --times;
        }
        break;


    case ARROW_DOWN:
    case ARROW_UP:
    case ARROW_LEFT:
    case ARROW_RIGHT:
        moveCursor(key_press);
        break;
    default:
        //printf("%c\r\n",key_press);
        break;
    }
    
    return;
    
}

void errorHandlingStatus(const char *str)
{
    write(STDOUT_FILENO,"\x1b[2J\x1b[1;1H",10);
    perror(str);
    exit(1);
}

void disableRawMode()
{
    if(tcsetattr(STDIN_FILENO,TCSANOW,&DefaultWindowSetting.orig_state) == -1)
    {
        errorHandlingStatus("DISABLERAWMODE: tcsetattr");
    }
    
}

void enableRawMode()
{
    struct termios raw;
    

    if(tcgetattr(STDIN_FILENO,&DefaultWindowSetting.orig_state) == -1)
    {
        errorHandlingStatus("ENABLERAWMODE: tcgetattr");    
    }

    atexit(disableRawMode);

    raw = DefaultWindowSetting.orig_state;

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 30;
    raw.c_lflag = raw.c_lflag & ~(ECHO | ICANON | ISIG);

    if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw) == -1)
    {
        errorHandlingStatus("ENABLERAWMODE: tcsetattr");    
    }

}


/*****************START*************************************/

int main()
{   
    enableRawMode();
    initStartScreen();
    openText("/home/Bobik/Документы/another/FILE.txt");

    while (1)
    {
        clearScreen();
        pressEditorKey(); 

    }

    return 0;


}

