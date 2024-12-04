#pragma once

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <text_utils/text_utils.hpp>

namespace pixval {
struct canvas {
    canvas(unsigned columns, unsigned rows, std::string name = "pixvalContainer");
    void set_canvas_size(std::string width, std::string height);
    void set_canvas_border_radius(std::string);
    void set_pixel_gap_size(std::string);
    void set_pixel_border_radius(std::string);
    void set_pixel_value(float, unsigned x, unsigned y);
    std::string make_css() const;
    std::string make_html() const;

private:
    const unsigned m_width;
    const unsigned m_height;
    const std::string m_name;
    std::vector<float> m_pixels;
    std::map<std::string, std::string> m_variables;
};

canvas::canvas(unsigned columns, unsigned rows, std::string name)
    : m_width(columns)
    , m_height(rows)
    , m_name(name)
    , m_pixels(m_width * m_height)
    , m_variables({ { "width", std::to_string(m_width) },
          { "height", std::to_string(m_height) },
          { "name", m_name },
          { "border_radius", "2px" },
          { "gap_size", "2px" },
          { "canvas_border_radius", "2px" } })
{
}

void canvas::set_canvas_size(std::string canvas_width, std::string canvas_height)
{
    m_variables["canvas_width"] = canvas_width;
    m_variables["canvas_height"] = canvas_height;
}

void canvas::set_canvas_border_radius(std::string value)
{
    m_variables["canvas_border_radius"] = value;
}

void canvas::set_pixel_gap_size(std::string gap_size)
{
    m_variables["gap_size"] = gap_size;
}

void canvas::set_pixel_border_radius(std::string border_radius)
{
    m_variables["border_radius"] = border_radius;
}

void canvas::set_pixel_value(float v, unsigned x, unsigned y)
{
    ASSERT(x < m_width);
    ASSERT(y < m_height);

    m_pixels[x * m_width + y] = v;
}

std::string canvas::make_css() const
{
    using namespace std;
    const string temp { R"(
            .{{name}}
            {
              background-color:black;
              width: {{canvas_width}};
              height: {{canvas_height}};
              display: grid;
              grid-template-columns: repeat({{width}}, 1fr);
              grid-template-rows: repeat({{height}}, 1fr);
              gap: {{gap_size}};
              padding: {{gap_size}};
              border-radius: {{canvas_border_radius}};
            }
            .pixel
            {
              border-radius: {{border_radius}};
            }
        )" };

    return text_utils::apply_variables(temp, m_variables);
}

std::string canvas::make_html() const
{
    using namespace std;
    auto pixel_temp { R"(<div class="pixel" style="background:rgb({{val}}, {{val}}, {{val}});"></div>)" };

    std::stringstream pixels;
    for (auto i = 0; i < m_width * m_height; ++i) {
        const auto value = 255.0 * m_pixels[i];
        pixels << text_utils::apply_variables(pixel_temp, { { "val", to_string(unsigned(round(value))) } }) << "\n";
    }

    const map<string, string> container_variables = {
        { "name", m_name },
        { "pixels", pixels.str() }
    };

    auto container_temp { R"(
            <div class="{{name}}">
                {{pixels}}
            </div>
        )" };

    return text_utils::apply_variables(container_temp, container_variables);
}
}
