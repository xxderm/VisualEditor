#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class LineShape final : public Shape {
        public:
            void Render() override;
            bool IsMouseHover(ImVec2 mousePos) override {}
            std::string GetName() const override { return "LineShape"; }
        protected:
            Quad GetBounds(ImVec2 pos) override{ return Quad();}
        private:
            ImVec2 mPointBegin;
            ImVec2 mPointEnd;
        };

    }
}