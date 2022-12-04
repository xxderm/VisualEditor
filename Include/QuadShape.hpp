#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class QuadShape final : public Shape {
        public:
            void Render() override;
            void OnEvent(SDL_Event *event, ImVec2 mousePos) override;
            std::string GetName() const override { return "QuadShape"; }
        protected:
            Quad GetBounds(ImVec2 pos) override;
        private:
            ImVec2 mSize = ImVec2(0.4, 0.4);
        };

    }
}