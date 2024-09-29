#include "text.hpp"

#include <raylib-cpp.hpp>

using namespace BH;

Text::Text(std::string text, int x, int y, int fontSize) {
    m_Text = text;
    m_X = x;
    m_Y = y;
    m_FontSize = fontSize;
}

Text::Text(const Text &&otherText) noexcept {
    m_Text = std::move(otherText.m_Text);
    m_X = otherText.m_X;
    m_Y = otherText.m_Y;
    m_FontSize = otherText.m_FontSize;
}

void Text::Draw() const {
    DrawText(m_Text.c_str(), X(), Y(), FontSize(), BLACK);
}

void Text::DrawCenter() const {
    DrawText(m_Text.c_str(), CenterX(), CenterY(), FontSize(), BLACK);
}

int Text::X() const {
    return m_X;
}

int Text::Y() const {
    return m_Y;
}

const std::string& Text::GetText() const {
    return m_Text;
}

int Text::FontSize() const {
    return m_FontSize;
}

int Text::CenterX() const {
    return m_X - Width() / 2;
}
int Text::CenterY() const {
    return m_Y - Height() / 2;
}

int Text::Width() const {
    return MeasureText(GetText().c_str(), 32);
}
int Text::Height() const {
    return m_FontSize;
}