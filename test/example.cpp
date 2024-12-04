#include <pixval/pixval.hpp>

#include <iostream>

using namespace std;
using namespace pixval;

int main()
{
    enum { width = 5, height = 5 };

    canvas c { width, height };

    const auto delta = 1.0 / (width * height);
    auto value = 0.0;

    for (auto i = 0; i < width; ++i) {
        for (auto j = 0; j < height; ++j) {
            c.set_value(value, i, j);
            value += delta;
        }
    }

    cout << c.make_css() << endl;

    return 0;
}
