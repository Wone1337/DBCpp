#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <panel.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define GetFileSize(FILE_PATH) getFileSize(FILE_PATH)

struct MemoryAllocator
{
    uint64_t size;
    char *text_of_file;
    
};

typedef struct MemoryAllocator TEXT_ALLOC;

struct MemoryAllocator;
uint64_t getFileSize(const char* FILE_PATH);
void FREE_MEMORY(TEXT_ALLOC* OBJ);

TEXT_ALLOC* ALLOC(const char* FILE_PATH)
{
    //TEMPORARY OBJECT TEXT_ALLOCATOR FOR RETURN
    TEXT_ALLOC* OBJ;

    //MEMORY ALLOCATION FOR STRUCT
    OBJ = (TEXT_ALLOC *)malloc(sizeof(TEXT_ALLOC));
    
    //CONDITION MEMORY ALLOCATED
    if(OBJ == NULL)
    {
        perror("ALLOCATION OF STRUCT IS FAILED!");
        return NULL;
    }

    //GET SIZE OF FILE 
    OBJ->size = GetFileSize(FILE_PATH);

    //IF FILE HAS A MAX SIZE , THEN FREE MEMORY AND RETURN NULL
    if(OBJ->size == SIZE_MAX)
    {
        perror("FILE SIZE IS TOO LARGE");
        FREE_MEMORY(OBJ);
        return NULL;
    }

    //MEMORY ALLOCATION ARRAY OF CHARS
    OBJ->text_of_file = (char*)malloc(OBJ->size * 2);

    //IF ALLOCATION FAILED RETURN NULL
    if(OBJ->text_of_file == NULL)
    {
        perror("ALLOCATION OF STRING FAILED!");
        return NULL;
    }

    //RETURN TEMP. OBJECT OF START DECLARE
    return OBJ;
}

void FREE_MEMORY(TEXT_ALLOC* OBJ)
{
    //IF OBJ HAVE NULL ADDRESS , THEN RETURN
    if(OBJ == NULL)
    {
        return;
    }

    //FREE MEMORY CHAR ARRAY AND STRUCT OF ALLOCATOR 
    free(OBJ->text_of_file);
    free(OBJ);

    //RETURN
    return;
}

uint64_t getFileSize(const char* FILE_PATH)
{
    //TEMP FILE FOR SIZE CHEK

    FILE* temp = NULL;

    //VARIABLE FOR RETURN SIZE

    uint64_t total_size_of_file = 0;

    //OPEN FILE

    temp = fopen(FILE_PATH,"r");

    //IF FILE IS NO EXIST

    if(temp == NULL)
    {
        total_size_of_file = SIZE_MAX;
        return total_size_of_file;
    }

    //IF FILE EXIST AND HE HAS A TEXT IN THERE, 
    //THEN SEEK END OF FILE IN "total_size_of_file"

    fseek(temp,0,SEEK_END);
    total_size_of_file = ftell(temp);

    //IF FILE EXIST AND HE HASN'T A TEXT IN THERE OR TEXT IS SO SMALL, 
    //THEN GIVE A TEMPORARY SIZE (1 MB) IN "total_size_of_file"

    if(total_size_of_file <= 1000)
    {
        total_size_of_file = SIZE_MAX%10000;
    }
    
    //CLOSE FILE

    fclose(temp);
    
    //RETURN THE FILE SIZE

    return total_size_of_file;
}

char* editedText(TEXT_ALLOC *obj, size_t cursor_y, size_t cursor_x)
{

    
    return obj->text_of_file;
}

int main(int argc,char *argv[])
{
    FILE *FILE_STREAM = NULL;

    TEXT_ALLOC *BUFFER = NULL;
    
    chtype ch = '\0';
    
    int win_size_x = 0 ,win_size_y = 0;
    
    int cursor_pos_x = 0,cursor_pos_y = 0;

    WINDOW *win_middle;

    if(argc != 2)
    {
        perror("FILE ARGUMENT REQUIRED");
        return EXIT_FAILURE;
    }

    if((BUFFER = ALLOC(argv[1])) == NULL)
    {
        perror("ALLOCATION FAILED");
        return EXIT_FAILURE;
    }


    FILE_STREAM = fopen(argv[1],"r+");

    fread(BUFFER->text_of_file, 1,BUFFER->size, FILE_STREAM);

    fclose(FILE_STREAM);
    
    initscr();
    
    getmaxyx(stdscr,win_size_y,win_size_x);

    win_middle = newwin(win_size_y,win_size_x,0,0);

    noecho();

    raw();

    keypad(win_middle,TRUE); 

    wprintw(win_middle,BUFFER->text_of_file);
    wmove(win_middle,0,0);
    wrefresh(win_middle);
    

    while((ch = wgetch(win_middle)) != KEY_F(4))
    {   
        

        getyx(win_middle,cursor_pos_y,cursor_pos_x);

        switch(ch)
        {
            case KEY_UP:
                if(cursor_pos_y > 0)
                { 
                    --cursor_pos_y;
                    wmove(win_middle,cursor_pos_y,cursor_pos_x);
                }
            break;

            case KEY_DOWN:
                if(cursor_pos_y < win_size_y - 1)
                { 
                    ++cursor_pos_y;
                    wmove(win_middle,cursor_pos_y,cursor_pos_x);
                }
            
            break;

            case KEY_LEFT:
                if(cursor_pos_x > 0)
                {
                    --cursor_pos_x;
                    wmove(win_middle,cursor_pos_y,cursor_pos_x);
                }
            break;

            case KEY_RIGHT:
                if(cursor_pos_x < win_size_x - 1)
                {
                    ++cursor_pos_x;
                    wmove(win_middle,cursor_pos_y,cursor_pos_x);
                }
            break;

            case KEY_BACKSPACE:
                wdelch(win_middle);
                wclear(win_middle);
                mvwprintw(win_middle,0,0,BUFFER->text_of_file);
                wrefresh(win_middle);
                wmove(win_middle,cursor_pos_y,--cursor_pos_x);
            break;              
                
            default:
                waddch(win_middle,ch);
                // BUFFER->text_of_file = editedText(BUFFER,cursor_pos_y,cursor_pos_x);
                // wprintw(win_middle,BUFFER->text_of_file);
                // wrefresh(win_middle);
            break;
        }


    }
    

    FILE_STREAM = fopen(argv[1],"w");

    fwrite(BUFFER->text_of_file,1,BUFFER->size,FILE_STREAM);

    fclose(FILE_STREAM);

    FREE_MEMORY(BUFFER);


    endwin();


    return EXIT_SUCCESS;
}