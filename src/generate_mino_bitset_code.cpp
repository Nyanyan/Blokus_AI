#include <iostream>
#include <vector>
#include <bitset>

constexpr int DNC = 0; // do not care
constexpr int FIL = 1; // filled
constexpr int CNR = 2; // corner
constexpr int EDG = 3; // edge

constexpr int BOARD_SIZE = 20; // board size
constexpr int BOARD_WITH_WALL_SIZE = BOARD_SIZE + 2;
constexpr int BOARD_BIT_SIZE = BOARD_WITH_WALL_SIZE * BOARD_WITH_WALL_SIZE;

const std::vector<std::vector<int>> M1 = {
    {CNR, EDG, CNR},
    {EDG, FIL, EDG},
    {CNR, EDG, CNR}
};

const std::vector<std::vector<int>> M2 = {
    {CNR, EDG, EDG, CNR},
    {EDG, FIL, FIL, EDG},
    {CNR, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M3V = {
    {DNC, CNR, EDG, CNR},
    {CNR, EDG, FIL, EDG},
    {EDG, FIL, FIL, EDG},
    {CNR, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M3I = {
    {CNR, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M4I = {
    {CNR, EDG, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M4L = {
    {CNR, EDG, CNR, DNC, DNC},
    {EDG, FIL, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M4N = {
    {CNR, EDG, EDG, CNR, DNC},
    {EDG, FIL, FIL, EDG, CNR},
    {CNR, EDG, FIL, FIL, EDG},
    {DNC, CNR, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M4P = {
    {CNR, EDG, EDG, CNR},
    {EDG, FIL, FIL, EDG},
    {EDG, FIL, FIL, EDG},
    {CNR, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M4T = {
    {CNR, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, FIL, EDG, CNR},
    {DNC, CNR, EDG, CNR, DNC}
};

const std::vector<std::vector<int>> M5F = {
    {DNC, CNR, EDG, EDG, CNR},
    {CNR, EDG, FIL, FIL, EDG},
    {EDG, FIL, FIL, EDG, CNR},
    {CNR, EDG, FIL, EDG, DNC},
    {DNC, CNR, EDG, CNR, DNC}
};

const std::vector<std::vector<int>> M5I = {
    {CNR, EDG, EDG, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5L = {
    {CNR, EDG, CNR, DNC, DNC, DNC},
    {EDG, FIL, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5N = {
    {DNC, DNC, CNR, EDG, EDG, CNR},
    {CNR, EDG, EDG, FIL, FIL, EDG},
    {EDG, FIL, FIL, FIL, EDG, CNR},
    {CNR, EDG, EDG, EDG, CNR, DNC}
};

const std::vector<std::vector<int>> M5P = {
    {CNR, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, FIL, FIL, EDG},
    {DNC, CNR, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5T = {
    {CNR, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, FIL, EDG, CNR},
    {DNC, EDG, FIL, EDG, DNC},
    {DNC, CNR, EDG, CNR, DNC}
};

const std::vector<std::vector<int>> M5U = {
    {CNR, EDG, CNR, EDG, CNR},
    {EDG, FIL, EDG, FIL, EDG},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5V = {
    {DNC, DNC, CNR, EDG, CNR},
    {DNC, DNC, EDG, FIL, EDG},
    {CNR, EDG, EDG, FIL, EDG},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5W = {
    {DNC, DNC, CNR, EDG, CNR},
    {DNC, CNR, EDG, FIL, EDG},
    {CNR, EDG, FIL, FIL, EDG},
    {EDG, FIL, FIL, EDG, CNR},
    {CNR, EDG, EDG, CNR, DNC}
};


const std::vector<std::vector<int>> M5X = {
    {DNC, CNR, EDG, CNR, DNC},
    {CNR, EDG, FIL, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, FIL, EDG, CNR},
    {DNC, CNR, EDG, CNR, DNC}
};


const std::vector<std::vector<int>> M5Y = {
    {DNC, CNR, EDG, CNR, DNC, DNC},
    {CNR, EDG, FIL, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5Z = {
    {CNR, EDG, EDG, CNR, DNC},
    {EDG, FIL, FIL, EDG, DNC},
    {CNR, EDG, FIL, EDG, CNR},
    {DNC, EDG, FIL, FIL, EDG},
    {DNC, CNR, EDG, EDG, CNR}
};

std::vector<std::vector<std::vector<int>>> unique_minos = {
    M1, M2, M3V, M3I, M4I, M4L, M4N, M4P, M4T,
    M5F, M5I, M5L, M5N, M5P, M5T,
    M5U, M5V, M5W, M5X, M5Y, M5Z
};

std::vector<std::string> mino_name = {
    "M1", "M2", "M3V", "M3I", "M4I", "M4L", "M4N", "M4P", "M4T",
    "M5F", "M5I", "M5L", "M5N", "M5P", "M5T",
    "M5U", "M5V", "M5W", "M5X", "M5Y", "M5Z"
};

constexpr int N_MINO_CELL_TYPE = 3;



void print_mino_bitset(std::string name, const std::vector<std::vector<int>>& mino_vec) {
    std::cout << "const std::bitset<BOARD_BIT_SIZE> " << name << "[N_MINO_CELL_TYPE] = {\n";
    std::string biteset_strs[N_MINO_CELL_TYPE]; // FIL, CNR, EDG
    for (int i = 0; i < N_MINO_CELL_TYPE; ++i) {
        std::cout << "    std::bitset<BOARD_BIT_SIZE>(\n";

        for (int y = 0; y < mino_vec.size(); ++y) {
            std::cout << "        \"";
            for (int x = 0; x < BOARD_WITH_WALL_SIZE - mino_vec[y].size(); ++x) {
                std::cout << "0";
            }
            for (int x = 0; x < mino_vec[y].size(); ++x) {
                if (mino_vec[y][x] == i + 1) { // FIL=1, CNR=2, EDG=3
                    std::cout << "1";
                } else {
                    std::cout << "0";
                }
            }
            std::cout << "\"\n";
        }

        std::cout << "    )";
        if (i != N_MINO_CELL_TYPE - 1) {
            std::cout << ",";
        }
        std::cout << "\n";
    }
    std::cout << "};\n\n";
}

int main() {
    for (size_t idx = 0; idx < unique_minos.size(); ++idx) {
        print_mino_bitset(mino_name[idx], unique_minos[idx]);
    }
    // print_mino_bitset("M1", M1);
}