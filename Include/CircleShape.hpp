#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class CircleShape final : public Shape {
        public:
            void Render() override;
            void OnEvent(SDL_Event *event, ImVec2 mousePos) override;
            std::string GetName() const override { return "CircleShape"; }
        protected:
            bool CheckBounds(ImVec2 pos) override;
        private:
            double mRadius = 0.2;
        };

    }
}