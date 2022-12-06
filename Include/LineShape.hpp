#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class LineShape final : public Shape {
        public:
            LineShape() = default;
            LineShape(const LineShape& other) {}
            void Render() override;
            bool IsMouseHover(ImVec2 mousePos) override {}
            bool IsInFlexBorder(ImVec2 mouse) override {}
            void Amplify(ImVec2 mouse) override {}
            void Flex(double dist) override {}
            std::string GetName() const override { return "LineShape"; }
            Quad GetBounds(ImVec2 pos) override{ return Quad();}
            void Move(ImVec2 delta) override{}
            Shape* Copy() override {}
        private:
            ImVec2 mPointBegin;
            ImVec2 mPointEnd;
        };

    }
}