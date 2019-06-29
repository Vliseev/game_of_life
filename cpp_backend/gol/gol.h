//
// Created by vlad on 28.06.19.
//

#ifndef CPP_BACKEND_GOL_H
#define CPP_BACKEND_GOL_H

#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

class GameOfLife {
public:
    using bool_matrix = std::vector<std::vector<bool>>;

    GameOfLife(size_t width, size_t height) : __height(height), __width(width) {
        using namespace std;
        random_device rd;
        std::mt19937 gen(rd());
        std::binomial_distribution<> dis(1, 0.5);

        __state = bool_matrix(width, vector<bool>(height));
        for (auto& line : __state)
            generate(line.begin(), line.end(), [&]() { return dis(gen); });
    }

    GameOfLife(const bool_matrix& state) {
        using namespace std;
        __width = state.size();
        __height = state[0].size();
        if (any_of(state.begin(), state.end(),
                   [&](auto& el) { return el.size() != __height; })) {
            std::logic_error("state matrix isn't square");
        }
        __state = state;
    }

    GameOfLife(bool_matrix&& state) {
        using namespace std;
        __width = state.size();
        __height = state[0].size();
        if (any_of(state.begin(), state.end(),
                   [&](auto& el) { return el.size() != __height; })) {
            std::logic_error("state matrix isn't square");
        }
        __state = move(state);
    }

    GameOfLife() = delete;

    const std::vector<std::vector<bool>>& get__state() const { return __state; }
    void PrinState() const {
        using namespace std;
        std::ostream_iterator<bool> out_it(std::cout, " ");
        for (const auto& line : __state) {
            std::copy(line.begin(), line.end() - 1, out_it);
            cout << *(line.end() - 1) << "\n";
        }
    }

    void OneStep() {
        using namespace std;
        bool_matrix tmp_state = __state;
        for (int i = 0; i < __width; ++i) {
            for (int j = 0; j < __height; ++j) {
                auto num_neib = GetNumNeib(i, j);
                if (num_neib < 2 || num_neib > 3)
                    tmp_state[i][j] = false;
                else if (num_neib == 3)
                    tmp_state[i][j] = true;
            }
        }
        __state = move(tmp_state);
    }

private:
    size_t __width, __height;
    bool_matrix __state;

    int GetNumNeib(int i, int j) {
        int l_n = __state[i][(j - 1 + __height) % __height];
        int r_n = __state[i][(j + 1 + __height) % __height];
        int u_n = __state[(i - 1 + __height) % __height][j];
        int d_n = __state[(i + 1 + __height) % __height][j];

        int lu_n =
                __state[(i - 1 + __height) % __height][(j - 1 + __height) % __height];
        int ru_n =
                __state[(i - 1 + __height) % __height][(j + 1 + __height) % __height];
        int ld_n =
                __state[(i + 1 + __height) % __height][(j - 1 + __height) % __height];
        int rd_n =
                __state[(i + 1 + __height) % __height][(j + 1 + __height) % __height];

        return l_n + r_n + u_n + d_n + lu_n + ru_n + ld_n + rd_n;
    }
};


#endif //CPP_BACKEND_GOL_H
