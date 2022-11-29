#pragma once
#include "CircleShape.hpp"
#include "TriangleShape.hpp"
#include "QuadShape.hpp"
#include "LineShape.hpp"
#include "GroupShape.hpp"

namespace VisualEditor {
    namespace Graphics {

        enum ShapeType {
            CIRCLE,
            TRIANGLE,
            QUAD,
            LINE,
            GROUP
        };

        class ShapeFactory final {
        public:
            static std::shared_ptr<Shape> CreateShape(ShapeType shapeType);
        };

    }
}