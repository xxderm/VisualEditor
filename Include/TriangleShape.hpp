#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class TriangleShape final : public Shape {
        public:
            void Render() override;
            bool IsMouseHover(ImVec2 mousePos) override;
            std::string GetName() const override { return "TriangleShape"; }
        protected:
            Quad GetBounds(ImVec2 pos) override;
        private:
            float Sign(ImVec2 p1, ImVec2 p2, ImVec2 p3);
        private:
            double mSize = 0.4;
        };

    }
}