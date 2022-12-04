#include "Shape.hpp"

namespace VisualEditor::Graphics {

    class CircleShape final : public Shape {
    public:
        void Render() override;
        void OnEvent(SDL_Event *event, ImVec2 mousePos) override;
        std::string GetName() const override { return "CircleShape"; }
        const bool IsMouseHover(ImVec2 mousePos) const override;
    protected:
        Quad GetBounds(ImVec2 pos) override;
    private:
        double mRadius = 0.2;
    };

}