#include <stdio.h>

// SNAKE GAME RISC V TEMPLATE?
// no game logic yet
// can print blank state
// board is an array of 64 chars
// cell (r,c) is at index r * 8 + c
// length, score, turn are globals
// snake coords in an array of 16 ints
//

#define ROWS 8
#define COLS 8
#define MAX_SNAKE_LEN 8
#define EMPTY_SYMBOL '.'
#define FOOD_SYMBOL  '*'
#define BODY_SYMBOL  'O'
#define UP_SYMBOL    '^'
#define DOWN_SYMBOL  'v'
#define LEFT_SYMBOL  '<'
#define RIGHT_SYMBOL '>'

char board[ROWS * COLS];
int snake_coord[2 * MAX_SNAKE_LEN] = {3,3,3,2,3,1};

// STATES
int length = 3;
int score = 0;
int turn = 0;
char head_symbol = RIGHT_SYMBOL; //start the game with the snake facing right

void clear_board() {
    for (int i = 0; i < ROWS * COLS; i++) {
        board[i] = EMPTY_SYMBOL;
    }
}

int idx(int row, int col) {
    // converts coord to index
    return row * COLS + col;
}

char direction_symbol(int r, int c){
    if (r == -1 && c == 0){
        return UP_SYMBOL;
    } else if (r == 1 && c ==0){
        return DOWN_SYMBOL;
    } else if (r == 0 && c == -1){
        return LEFT_SYMBOL;
    } else{
        return RIGHT_SYMBOL;
    }
}

void insert_snake() {
    for (int i = 0; i < length * 2; i += 2) {
        if (i == 0) {
            board[idx(snake_coord[0], snake_coord[1])] = head_symbol;
        } else {
            board[idx(snake_coord[i], snake_coord[i+1])] = BODY_SYMBOL;
        }

    }
}

void insert_food(int food_r, int food_c) {
    // inserts food at r, c (pano ba randomization sa risc-v?)
    if (food_r >= 0 && food_c >= 0 && food_r < ROWS && food_c < COLS){
        board[idx(food_r, food_c)] = FOOD_SYMBOL;
    }
}

void spawn_food(){
    // TODO 
    // call insert food after eating the current food
    // Figure out how to find a cell to spawn the food
}

void slither(int dir_r, int dir_c) {
    for (int i = 2 * length - 2; i > 0; i -= 2) {
        snake_coord[i] = snake_coord[i - 2];
        snake_coord[i + 1] = snake_coord[i - 1];
    }
    snake_coord[0] += dir_r;
    snake_coord[1] += dir_c;

    head_symbol = direction_symbol(dir_r, dir_c);

    // add logic for collision (body or food)

    //

    if (food_eaten){
        score++;
        // grow the snake

        //
        spawn_food();
    }

    turn++;
}

// function for collision? not sure if tama logic double check later.
void hit_border(){
    if (snake_coord[0] < 0 || snake_coord[0] > ROWS || snake_coord[1] < 0 || snake_coord[1] > COLS){
        return true;
    } else {
        return false;
    }
}

void hit_body(){
    for (int l = 1; l < length; l++){
        if (snake_coord[0] == snake_coord[l * 2] && snake_coord[1] == snake_coord[l * 2 + 1]){
            return true;
        }
    }
    return false;
}
//

void draw_horiz_border() {
    printf("%c",'+');
    for (int i = 0; i < COLS * 2 + 1; i++) {
        printf("%c",'-');
    }
    printf("%c",'+');
    printf("%c",'\n');
}

void draw_state() {
    clear_board();
    insert_snake();
    draw_horiz_border();
    for (int r = 0; r < ROWS; r++) {
        printf("%c",'|');
        printf("%c",' ');
        for (int c = 0; c < COLS; c++) {
            printf("%c",board[idx(r, c)]);
            printf("%c",' ');
        }
        printf("%c",'|');
        printf("%c",'\n');
    }
    draw_horiz_border();
    printf("Length: %d, Score: %d\n", length, score);
}

char read_char() {
    // first char only
    int ch = getchar();
    int first = ch;
    while (ch != '\n' && ch != -1) {
        ch = getchar();
    }
    return (char)first;
}

char read_menu_choice() {
    char choice;
    printf("Choose [1] or [2]:\n");
    printf("[1] New Game\n");
    printf("[2] Start from a State\n");
    do {
        printf("Choice: ");
        choice = read_char();
    } while (choice != '1' && choice != '2');
    return choice;
}

char read_move() {
    char m;
    while (1) {
        printf("Turn %d: <enter a move> ", turn);
        m = read_char();
        // lowercase possible by shifting
        if (m >= 'a' && m <= 'z') {
            m = m - 'a' + 'A';
        }
        if (m == 'W' || m == 'A' || m == 'S' || m == 'D' || m == 'X') {
            return m;
        }
        printf("Invalid move\n");
    }
}

void new_game_setup() {
    clear_board();
    length = 3;
    score = 0;
    turn = 0

    // Going left
    initial_direction_r = 0;
    initial_direction_c = 1;
    //

    // TODO
    // place snake [(3,3),(3,2),(3,1)]
    // use 1 array for new game and state setup?
}

void state_setup(void) {
    clear_board();
    // TODO
}

int main() {
    char choice = read_menu_choice();

    if (choice == '1') {
        new_game_setup();
    } else {
        state_setup();
    }

    draw_state();
    while (1) {
        char move = read_move();

        if (move == 'X') {
            break;
        }
        if (move == 'W') {
            slither(-1, 0);
        }
        if (move == 'A') {
            slither(0, -1);
        }
        if (move == 'S') {
            slither(1, 0);
        }
        if (move == 'D') {
            slither(0, 1);
        }
        turn++;
        draw_state();
    }

    return 0;
}