#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class LineShape final : public Shape {
        public:
            LineShape() = default;
            LineShape(const LineShape& other) {}
            void Load(nlohmann::json* data, uint32_t* index) override {}
            void Save(nlohmann::json* data, uint32_t* index) override {}
            ImVec2 GetSize() override { return ImVec2(0, 0); };
            void Render() override;
            bool IsMouseHover(ImVec2 mousePos) override {}
            bool IsInFlexBorder(ImVec2 mouse) override {}
            void Amplify(ImVec2 mouse) override {}
            void Flex(double dist) override {}
            std::string GetName() const override { return "LineShape"; }
            Quad GetBounds(ImVec2 pos) override{ return Quad();}
            Shape* Copy() override {}
        private:
            ImVec2 mPointBegin;
            ImVec2 mPointEnd;
        };

    }
}