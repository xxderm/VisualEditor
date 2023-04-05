#include "Shape.hpp"

namespace VisualEditor::Graphics {

    class CircleShape final : public Shape {
    public:
        CircleShape() = default;
        CircleShape(const CircleShape& other);
        void Render() override;
        void Load(nlohmann::json* data) override;
        void Save(nlohmann::json* data) override;
        ImVec2 GetSize() override { return ImVec2(mRadius * 2., mRadius * 2.); };
        std::string GetName() const override { return "CircleShape"; }
        ShapeType GetShapeType() const override { return ShapeType::CIRCLE; }
        bool IsMouseHover(ImVec2 mousePos) override;
        Quad GetBounds(ImVec2 pos) override;
        bool IsInFlexBorder(ImVec2 mouse) override;
        void Amplify(ImVec2 mouse) override;
        void Flex(double dist) override;
        Shape* Copy() override;
    private:
        double mRadius = 0.2;
    };

}