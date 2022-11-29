#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class LineShape final : public Shape {
        public:
            void Render() override;
            void OnEvent(SDL_Event *event, ImVec2 mousePos) override {}
            std::string GetName() const override { return "LineShape"; }
        protected:
            bool CheckBounds(ImVec2 pos) override{}
        private:
            ImVec2 mPointBegin;
            ImVec2 mPointEnd;
        };

    }
}