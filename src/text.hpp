#ifndef BOOMHEADSHOT_TEXT_HPP
#define BOOMHEADSHOT_TEXT_HPP

#include <string>

namespace BH {

    class Text {
    public:
        Text() = delete;
        Text(std::string text, int x, int y, int fontSize);
        Text(const Text &otherText) = default;
        Text(const Text &&otherText) noexcept;
        ~Text() = default;

        void Draw() const;
        void DrawCenter() const;

        [[nodiscard]]
        int X() const;
        [[nodiscard]]
        int Y() const;
        [[nodiscard]]
        const std::string& GetText() const;
        [[nodiscard]]
        int FontSize() const;

        [[nodiscard]]
        int CenterX() const;
        [[nodiscard]]
        int CenterY() const;

        [[nodiscard]]
        int Width() const;
        [[nodiscard]]
        int Height() const;

    private:
        int m_X, m_Y;
        int m_FontSize;
        std::string m_Text;
    };
}
#endif
