#include <cassert>
#define ASSERT(p) assert((p))

#include <pixval/pixval.hpp>

#include <iostream>

using namespace std;
using namespace pixval;

int main()
{
    enum { width = 10,
        height = 10 };

    canvas c { width, height };
    c.set_canvas_size("400px", "400px");

    const auto delta = 1.0 / (width * height - 1);
    auto value = 0.0;

    for (auto i = 0; i < width; ++i) {
        for (auto j = 0; j < height; ++j) {
            c.set_pixel_value(value, i, j);
            value += delta;
        }
    }

    cout << "<!DOCTYPE html><html>" << endl;
    cout << "<header><style>" << endl;

    cout << c.make_css() << endl;
    cout << "</style></header>" << endl;
    cout << "<body>" << endl;
    cout << c.make_html() << endl;
    cout << "</body>" << endl;
    cout << "</html>" << endl;

    return 0;
}
