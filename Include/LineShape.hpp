#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class LineShape final : public Shape {
        public:
            void Render() override;
            bool IsMouseHover(ImVec2 mousePos) override {}
            std::string GetName() const override { return "LineShape"; }
            Quad GetBounds(ImVec2 pos) override{ return Quad();}
            std::shared_ptr<Shape> Copy() override {}
        private:
            ImVec2 mPointBegin;
            ImVec2 mPointEnd;
        };

    }
}