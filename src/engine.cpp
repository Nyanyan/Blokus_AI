#include "board.hpp"






int main() {
    init_unique_minos();
    init_all_minos();

    Board board;
    board.random_play(0);

    return 0;
}
