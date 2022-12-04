#include "Shape.hpp"

namespace VisualEditor::Graphics {

    class CircleShape final : public Shape {
    public:
        void Render() override;
        std::string GetName() const override { return "CircleShape"; }
        bool IsMouseHover(ImVec2 mousePos) override;
        Quad GetBounds(ImVec2 pos) override;
    private:
        double mRadius = 0.2;
    };

}