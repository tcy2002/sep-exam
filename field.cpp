#include "field.h"

#include <iostream>

void Field::initField(int mm, int nn) {
    m = mm;
    n = nn;
    field = new int[m * n];
}

void Field::findPath() {
    int total = 2 * m + 2 * n - 4;

    std::vector<QPoint> paths[total];
    int sums[total];

    int j = 0;
    for (int i = 0; i < m; i++)
        sums[i] = one_step(j++, 0, 0, paths[i]);

    j = 1;
    for (int i = m; i < m + n - 1; i++)
        sums[i] = one_step(m - 1, j++, 0, paths[i]);

    j = m - 2;
    for (int i = m + n - 1; i < 2 * m + n - 2; i++)
        sums[i] = one_step(j--,  n - 1, 0, paths[i]);

    j = n - 2;
    for (int i = 2 * m + n - 2; i < total; i++)
        sums[i] = one_step(0, j--, 0, paths[i]);

    for (int i = 0; i < total; i++)
        std::cout << sums[i] << std::endl;
    int max = -1;
    for (int i = 0; i < total; i++)
        if (sums[i] >= max)
            max = sums[i];

    std::vector<int> max_paths;
    for (int i = 0; i < total; i++)
        if (sums[i] >= max)
            max_paths.push_back(i);

    for (auto i : max_paths)
        for (auto &p : paths[i])
            (*this)[p.x()][p.y()] = -3;
}

int Field::one_step(int x, int y, int pre_sum, std::vector<QPoint> &que) {
    if (x < 0 || y < 0 || x >= m || y >= n || (*this)[x][y] <= 0)
        return pre_sum;


    int tmp = (*this)[x][y];
    pre_sum += tmp;
    (*this)[x][y] = -1;
    que.push_back(QPoint(x, y));

    std::vector<QPoint> child[4];
    int rest[4]{};
    rest[0] = one_step(x + 1, y, pre_sum, child[0]);
    rest[1] = one_step(x, y + 1, pre_sum, child[1]);
    rest[2] = one_step(x - 1, y, pre_sum, child[2]);
    rest[3] = one_step(x, y - 1, pre_sum, child[3]);

    int max = -1, idx = -1;
    for (int i = 0; i < 4; i++)
        if (rest[i] > max) {
            max = rest[i];
            idx = i;
        }

    (*this)[x][y] = tmp;
    if (idx != -1) {
        for (auto &p : child[idx])
            que.push_back(p);
        pre_sum = rest[idx];
    }

    return pre_sum;
}
