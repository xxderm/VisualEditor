#pragma once
#include <memory>

namespace VisualEditor::Graphics {

        enum ShapeType {
            CIRCLE,
            TRIANGLE,
            QUAD,
            LINE,
            GROUP
        };

        class Shape;

        class ShapeFactory final {
        public:
            static std::shared_ptr<Shape> CreateShape(ShapeType shapeType);
        };

    }