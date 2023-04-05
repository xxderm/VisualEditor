#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class LineShape final : public Shape {
        public:
            LineShape() = default;
            LineShape(const LineShape& other) {}
            void Load(nlohmann::json* data) override {}
            void Save(nlohmann::json* data) override {}
            ImVec2 GetSize() override { return ImVec2(0, 0); };
            void Render() override;
            bool IsMouseHover(ImVec2 mousePos) override { return false; }
            bool IsInFlexBorder(ImVec2 mouse) override { return false; }
            ShapeType GetShapeType() const override { return ShapeType::LINE; }
            void Amplify(ImVec2 mouse) override {}
            void Flex(double dist) override {}
            std::string GetName() const override { return "LineShape"; }
            Quad GetBounds(ImVec2 pos) override{ return Quad();}
            Shape* Copy() override { return nullptr; }
        private:
            ImVec2 mPointBegin;
            ImVec2 mPointEnd;
        };

    }
}