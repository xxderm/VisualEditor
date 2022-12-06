#include "Shape.hpp"

namespace VisualEditor::Graphics {

    class CircleShape final : public Shape {
    public:
        CircleShape() = default;
        CircleShape(const CircleShape& other);
        void Render() override;
        std::string GetName() const override { return "CircleShape"; }
        bool IsMouseHover(ImVec2 mousePos) override;
        void Move(ImVec2 delta) override;
        Quad GetBounds(ImVec2 pos) override;
        bool IsInFlexBorder(ImVec2 mouse) override;
        void Amplify(ImVec2 mouse) override;
        void Flex(double dist) override;
        Shape* Copy() override;
    private:
        double mRadius = 0.2;
    };

}