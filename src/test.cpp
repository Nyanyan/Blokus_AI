// #include "mino.hpp"

// int main() {
//     init_unique_minos();
//     init_all_minos();

//     // print_all_unique_minos();
//     print_all_minos();
// }


#include "board.hpp"

int main() {
    init_unique_minos();
    init_all_minos();

    Board board;
    board.print_board();

    board.random_playout(0);

    return 0;
}