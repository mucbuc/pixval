#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <text_utils/text_utils.hpp>

namespace pixval
{
    struct canvas
    {
        canvas(unsigned width, unsigned height, std::string name = "pixvalContainer");
        void set_value(float, unsigned x, unsigned y);
        std::string make_css() const;
        std::string make_html() const;

    private:
        const unsigned m_width;
        const unsigned m_height;
        const std::string m_name;
        std::vector<float> m_pixels;
    };

    canvas::canvas(unsigned width, unsigned height, std::string name)
    : m_width(width)
    , m_height(height)
    , m_name(name)
    , m_pixels(m_width * m_height)
    {}

    void canvas::set_value(float v, unsigned x, unsigned y)
    {
        m_pixels[x * m_width + y] = v;
    }

    std::string canvas::make_css() const
    {
        using namespace std;
        const string temp { R"(
            .{{name}}
            {
              --width: {{width}};
              --height: {{height}};
              background-color:black;
              height: 800px;
              display: grid;
              grid-template-columns: repeat(var(--width), 1fr);
              grid-template-rows: repeat(var(--height), 1fr);
              gap: 2px;
              padding: 2px;
            }
            .pixel
            {
              border-radius: 2px;
            }
        )" };

        const map<string, string> variables = {
            {"width", to_string(m_width)},
            {"height", to_string(m_height)},
            {"name", m_name },
        };

        return text_utils::apply_variables( temp, variables );
    }

    std::string canvas::make_html() const
    {
        using namespace std;
        auto pixel_temp { R"(
            <div class="pixel" sytle="background:rgb(10, 10, 10);"></div>
        )" };

        const map<string, string> variables = {

        };

        return text_utils::apply_variables( pixel_temp, variables );
    }
}


/*



unsigned long make_RGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

std::cout << "Output of (unsigned char)0xc0: "
    << std::hex << std::setw(2) << std::setfill('0') << make_RGB(r, g, b) << '\n';
  return 0;

-    template<class T>
-    static std::array<uint8_t, 4> get_colors(T hexColors) {
-        uint8_t red = stoi( hexColors.first.substr(1, 2), 0, 16 );
-        uint8_t green = stoi( hexColors.first.substr(3, 2), 0, 16 );
-        uint8_t blue = stoi( hexColors.first.substr(5, 2), 0, 16 );
-        uint8_t alpha = hexColors.second * 255;
-        return std::array<uint8_t, 4>({red, green, blue, alpha});
-    }


*/
