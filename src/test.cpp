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

    // Mino mino = all_minos[0];
    // print_mino(mino);
    // std::cerr << mino.shiftable_left(2) << std::endl;
    // mino = mino << 2;
    // print_mino(mino);

    return 0;
}