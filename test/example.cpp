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
    c.canvas_properties().insert({
        { "width", "400px" },
        { "height", "400px" },
        { "display", "grid" },
        { "background-color", "black" },
        { "grid-template-columns", "repeat(" + to_string(width) + ", 1fr)" },
        { "grid-template-rows", "repeat(" + to_string(height) + ", 1fr)" },
        { "gap", "2px" },
        { "padding", "2px" },
    });

    c.pixel_properties().insert({ { "border-radius", "2px" } });

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
