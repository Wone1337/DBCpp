#include <ncurses.h>
#include <string.h>

void remove_char_from_buffer(char *buffer, int index) {
    int len = strlen(buffer);

    // Если индекс допустим
    if (index < 0 || index >= len) {
        return;
    }

    // Сдвигаем все символы после индекса на одну позицию влево
    for (int i = index; i < len; i++) {
        buffer[i] = buffer[i + 1];
    }

    buffer[len - 1] = '\0';
}

int main() {
        char buffer[100] = "Hello, World!";  
        int cursor_pos = 5;  // Позиция курсора (после "Hello")


    initscr();
    WINDOW *win_middle = newwin(10, 50, 0, 0);            // Инициализация ncurses
    raw();                // Отключаем стандартную обработку клавиш
    noecho();             // Отключаем эхо ввода
    keypad(win_middle, TRUE); // Включаем клавиши управления

    // Исходный текст
    // Окно для отображения текста

    // Выводим текст в окно
    wprintw(win_middle, "%s", buffer);
    wrefresh(win_middle);

    chtype ch;
    while ((ch = wgetch(win_middle)) != KEY_F(4)) { // Выход по F4
        getyx(win_middle, cursor_pos, cursor_pos); // Получаем текущую позицию курсора

        if (ch == KEY_BACKSPACE) {
            // Удаляем символ в буфере перед курсором
            remove_char_from_buffer(buffer, cursor_pos - 1);  

            // Удаляем символ из окна на текущей позиции
            wdelch(win_middle);

            // Перерисовываем текст в окне с нового состояния
            wclear(win_middle);  // Это нужно, чтобы очистить старую строку
            mvwprintw(win_middle, 0, 0, buffer); // Отображаем новый текст
            wrefresh(win_middle); // Обновляем окно

            // Перемещаем курсор на одну позицию назад
            wmove(win_middle, cursor_pos, cursor_pos - 1);
        }
    }

    endwin();  // Завершаем работу ncurses

    return 0;
}