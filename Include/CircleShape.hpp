#include "Shape.hpp"

namespace VisualEditor::Graphics {

    class CircleShape final : public Shape {
    public:
        CircleShape() = default;
        CircleShape(const CircleShape& other);
        void Render() override;
        void Load(nlohmann::json* data, uint32_t* index) override;
        void Save(nlohmann::json* data, uint32_t* index) override;
        ImVec2 GetSize() override { return ImVec2(mRadius, mRadius); };
        std::string GetName() const override { return "CircleShape"; }
        bool IsMouseHover(ImVec2 mousePos) override;
        Quad GetBounds(ImVec2 pos) override;
        bool IsInFlexBorder(ImVec2 mouse) override;
        void Amplify(ImVec2 mouse) override;
        void Flex(double dist) override;
        Shape* Copy() override;
    private:
        double mRadius = 0.2;
    };

}