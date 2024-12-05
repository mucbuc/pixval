#pragma once

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <text_utils/text_utils.hpp>

namespace pixval {
struct canvas {
    using properties_type = std::map<std::string, std::string>;

    canvas(unsigned columns, unsigned rows, std::string name);

    properties_type& canvas_properties();
    properties_type canvas_properties() const;
    properties_type& pixel_properties();
    properties_type pixel_properties() const;

    void set_pixel_value(float, unsigned x, unsigned y);
    std::string make_css() const;
    std::string make_html() const;

private:
    static std::string make_properties_string(const properties_type& properties)
    {
        std::stringstream result;
        for (auto property : properties) {
            result << property.first << ": " << property.second << ";"
                   << "\n";
        }
        return result.str();
    }

    const unsigned m_width;
    const unsigned m_height;
    std::string m_name;
    properties_type m_canvas_properties;
    properties_type m_pixel_properties;
    std::vector<float> m_pixels;
};

canvas::canvas(unsigned columns, unsigned rows, std::string name)
    : m_width(columns)
    , m_height(rows)
    , m_name(name)
    , m_pixels(m_width * m_height)
    , m_canvas_properties()
    , m_pixel_properties()
{
}

auto canvas::canvas_properties() -> properties_type&
{
    return m_canvas_properties;
}

auto canvas::canvas_properties() const -> properties_type
{
    return m_canvas_properties;
}

auto canvas::pixel_properties() -> properties_type&
{
    return m_pixel_properties;
}

auto canvas::pixel_properties() const -> properties_type
{
    return m_pixel_properties;
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
              {{canvas_properties}}
                .pixel
                {
                {{pixel_properties}}
                }
            }
        )" };

    properties_type variables = {
        { "name", m_name },
        { "canvas_properties", make_properties_string(m_canvas_properties) },
        { "pixel_properties", make_properties_string(m_pixel_properties) }
    };

    return text_utils::apply_variables(temp, variables);
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
