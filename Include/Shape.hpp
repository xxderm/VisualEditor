#pragma once
#include "pch.hpp"
#include "ShapeFactory.hpp"

namespace VisualEditor::Graphics {

    class IObserver {
    public:
        virtual void Update() = 0;
    };

    class Observable {
    public:
        void AddObserver(IObserver* observer) {
            mObservers.push_back(observer);
        }
        void NotifyUpdate() {
            for (auto& obs : mObservers)
                obs->Update();
        }
    private:
        std::vector<IObserver*> mObservers;
    };

    struct Quad {
        ImVec2 TopLeft{};
        ImVec2 TopRight{};
        ImVec2 BtmLeft{};
        ImVec2 BtmRight{};
    };

    class IFlexible {
    public:
        virtual bool IsInFlexBorder(ImVec2 mouse) = 0;
        virtual void Amplify(ImVec2 mouse) = 0;
        virtual void Flex(double dist) = 0;
    };

    class IMemorable {
    public:
        virtual void Load(nlohmann::json* data) = 0;
        virtual void Save(nlohmann::json* data) = 0;
    };

    class Shape : public IFlexible, public IMemorable {
    public:
        Shape() = default;
        Shape(const Shape& other);
        virtual void Render() = 0;
        void OnEvent(SDL_Event *event, ImVec2 mousePos);
        virtual void Move(ImVec2 delta) {
            mPosition.x += delta.x;
            mPosition.y += delta.y;
        };
        virtual bool IsMouseHover(ImVec2 mousePos) = 0;
        virtual Shape* Copy() = 0;
        virtual ImVec2 GetSize() = 0;
        virtual void SetColor(ImVec4 color) { mColor = color; }
        virtual void Load(nlohmann::json* data) override;
        virtual void Save(nlohmann::json* data) override;
        void SetPos(ImVec2 pos) { mPosition = pos; }
        void Select(bool status = true) { mSelected = status; }
        virtual std::string GetName() const { return "Shape"; }
        virtual ShapeType GetShapeType() const = 0;
        ImVec2 GetPosition() const { return mPosition; }
        ImVec4 GetColor() const { return mColor; }
        bool IsSelected() const { return mSelected; }
        virtual ~Shape() = default;
        virtual Quad GetBounds(ImVec2 pos) = 0;
        bool CheckBounds(ImVec2 pos);
    protected:
        ImVec2 mPosition = ImVec2(0, 0);
        ImVec4 mColor = ImVec4(1, 1, 1, 1);
        bool mHovered = false;
        bool mSelected = false;
        bool mMousePressed = false;
        bool mShift = false;
        bool mIsFlex = false;
        ImVec2 mDeltaDiff{};
    };

    class GraphicUtility final {
    public:
        static void QuadEdge(ImVec2 point, ImVec2 size, ImVec4 color = ImVec4(1, 0, 0, 1)) {
            auto topLeftPoint = ImVec2(point.x - size.x / 2., point.y + size.y / 2);
            auto topRightPoint = ImVec2(point.x + size.x / 2., point.y + size.y / 2);
            auto btmLeftPoint = ImVec2(point.x - size.x / 2., point.y - size.y / 2);
            auto btmRightPoint = ImVec2(point.x + size.x / 2., point.y - size.y / 2);
            glColor3f(color.x, color.y, color.z);
            glBegin(GL_POLYGON);
            glVertex2f(topLeftPoint.x, topLeftPoint.y);
            glVertex2f(topRightPoint.x, topRightPoint.y);
            glVertex2f(btmRightPoint.x, btmRightPoint.y);
            glVertex2f(btmLeftPoint.x, btmLeftPoint.y);
            glEnd();
        }
        static void CircleEdge(ImVec2 point, double radius, ImVec4 color = ImVec4(1, 0, 0, 1)) {
            glBegin(GL_POLYGON);
            for (int i = 0; i <= 300; i++) {
                double angle = 2 * M_PI * i / 300;
                double x = cos(angle) * radius;
                double y = sin(angle) * radius;
                glColor3f(color.x, color.y, color.z);
                glVertex2d(point.x + x, point.y + y);
            }
            glEnd();
        }
        static void TriangleEdge(ImVec2 point, double size, ImVec4 color = ImVec4(1, 0, 0, 1)) {
            auto topPoint = ImVec2(point.x, point.y - size);
            auto leftPoint = ImVec2(point.x - size, point.y + size);
            auto rightPoint = ImVec2(point.x + size, point.y + size);
            glColor3f(color.x, color.y, color.z);
            glBegin(GL_TRIANGLES);
            glVertex2f(topPoint.x, topPoint.y);
            glVertex2f(leftPoint.x, leftPoint.y);
            glVertex2f(rightPoint.x, rightPoint.y);
            glEnd();
        }
        static void LineEdge(ImVec2 point1, ImVec2 point2, ImVec4 color = ImVec4(1, 0, 0, 1), uint32_t lineSize = 10) {
            glLineWidth(lineSize);
            glColor3f(color.x, color.y, color.z);
            glBegin(GL_LINES);
            glVertex2f(point1.x, point1.y);
            glVertex2f(point2.x, point2.y);
            glEnd();
        }
        static void Grid(ImVec2 pos, double size) {
            glLineWidth(3);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3f(1, 1, 0.6);
            glBegin(GL_QUADS);
            glVertex2f(pos.x - size / 2., pos.y + size / 2.);
            glVertex2f(pos.x + size / 2., pos.y + size / 2.);
            glVertex2f(pos.x + size / 2., pos.y - size / 2.);
            glVertex2f(pos.x - size / 2., pos.y - size / 2.);
            glEnd();
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        static void Grid(ImVec2 pos, ImVec2 size) {
            glLineWidth(3);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3f(1, 1, 0.6);
            glBegin(GL_QUADS);
            glVertex2f(pos.x - size.x / 2., pos.y + size.y / 2.);
            glVertex2f(pos.x + size.x / 2., pos.y + size.y / 2.);
            glVertex2f(pos.x + size.x / 2., pos.y - size.y / 2.);
            glVertex2f(pos.x - size.x / 2., pos.y - size.y / 2.);
            glEnd();
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    };

}