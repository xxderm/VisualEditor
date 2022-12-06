#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class TriangleShape final : public Shape {
        public:
            void Render() override;
            bool IsMouseHover(ImVec2 mousePos) override;
            bool IsInFlexBorder(ImVec2 mouse) override;
            void Amplify(ImVec2 mouse) override;
            void Flex(double dist) override;
            std::string GetName() const override { return "TriangleShape"; }
            Quad GetBounds(ImVec2 pos) override;
            void Move(ImVec2 delta) override;
            Shape* Copy() override;
        private:
            float Sign(ImVec2 p1, ImVec2 p2, ImVec2 p3);
        private:
            double mSize = 0.2;
        };

    }
}