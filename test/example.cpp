#include <cassert>
#define ASSERT(p) assert((p))

#include <pixval/pixval.hpp>

#include <iostream>

using namespace std;
using namespace pixval;

int main()
{
    enum { rows = 10,
        columns = rows };

    canvas c { columns, rows, "container" };
    c.canvas_properties().insert({
        { "width", "400px" },
        { "height", "400px" },
    });

    const auto delta = 1.0 / (rows * columns - 1);
    auto value = 0.0;
    for (auto i = 0; i < columns; ++i) {
        for (auto j = 0; j < rows; ++j) {
            c.set_pixel_value(value, i, j);
            value += delta;
        }
    }

    cout << "<!DOCTYPE html><html><header><style>" << endl;
    cout << c.make_css() << endl;
    cout << "</style></header><body>" << endl;
    cout << c.make_html() << endl;
    cout << "</body></html>" << endl;

    return 0;
}
