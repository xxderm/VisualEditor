#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class TriangleShape final : public Shape {
        public:
            TriangleShape() = default;
            TriangleShape(const TriangleShape& other);
            void Load(nlohmann::json* data) override;
            void Save(nlohmann::json* data) override;
            void Render() override;
            ImVec2 GetSize() override { return ImVec2(mSize * 2., mSize * 2.); };
            bool IsMouseHover(ImVec2 mousePos) override;
            bool IsInFlexBorder(ImVec2 mouse) override;
            void Amplify(ImVec2 mouse) override;
            void Flex(double dist) override;
            std::string GetName() const override { return "TriangleShape"; }
            ShapeType GetShapeType() const override { return ShapeType::TRIANGLE; }
            Quad GetBounds(ImVec2 pos) override;
            Shape* Copy() override;
        private:
            float Sign(ImVec2 p1, ImVec2 p2, ImVec2 p3);
        private:
            double mSize = 0.2;
        };

    }
}