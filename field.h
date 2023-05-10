#ifndef FIELD_H
#define FIELD_H

#include <QPoint>
#include <vector>

class Field
{
private:
    int *field;

    int one_step(int x, int y, int pre_sum, std::vector<QPoint> &que);

public:
    int m = 0;
    int n = 0;
    int *operator[](int idx) {
        return field + idx * n;
    }

    void initField(int mm, int nn);

    void findPath();
};

#endif // FIELD_H
