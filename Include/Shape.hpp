#pragma once
#include "pch.hpp"

namespace VisualEditor::Graphics {

    class Shape {
    public:
        Shape() = default;
        Shape(const Shape& other) = delete;
        virtual void Render() = 0;
        virtual void OnEvent(SDL_Event *event, ImVec2 mousePos) {
            if (event->type == SDL_KEYDOWN)
                if (event->key.keysym.sym == SDLK_LSHIFT)
                    mShift = true;
            if (event->type == SDL_KEYUP)
                if (event->key.keysym.sym == SDLK_LSHIFT)
                    mShift = false;
        }
        virtual std::string GetName() const { return "Shape"; }
        void Load(std::string projFile, uint32_t index) {

        }
        void Save(std::string projFile) {
            nlohmann::json data;
            std::fstream fin(projFile);
            data = nlohmann::json::parse(fin);
            fin.close();
            data[std::to_string(mIndex)]["ShapeName"] = this->GetName();
            data[std::to_string(mIndex)]["ShapeColor"]["r"] = this->GetColor().x;
            data[std::to_string(mIndex)]["ShapeColor"]["g"] = this->GetColor().y;
            data[std::to_string(mIndex)]["ShapeColor"]["b"] = this->GetColor().z;
            data[std::to_string(mIndex)]["ShapeColor"]["a"] = this->GetColor().w;
            data[std::to_string(mIndex)]["ShapePos"]["x"] = this->mPosition.x;
            data[std::to_string(mIndex)]["ShapePos"]["y"] = this->mPosition.y;
            std::ofstream fout(projFile);
            auto dump = data.dump(4);
            fout.write(dump.data(), dump.size());
            fout.close();
        }
        ImVec4 GetColor() const { return mColor; }
        void SetColor(ImVec4 color) { mColor = color; }
        void SetPos(ImVec2 pos) { mPosition = pos; }
        void SetIndex(uint32_t index) { mIndex = index; }
        bool IsSelected() const { return mSelected; }
        virtual ~Shape() {}
    protected:
        virtual bool CheckBounds(ImVec2 pos) = 0;
    protected:
        ImVec2 mPosition = ImVec2(0, 0);
        ImVec4 mColor = ImVec4(1, 1, 1, 1);
        bool mHovered = false;
        bool mSelected = false;
        bool mMousePressed = false;
        bool mShift = false;
        uint32_t mIndex = 0;
    };

    class GraphicUtility {
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
        static void LineEdge(ImVec2 point1, ImVec2 point2, ImVec4 color = ImVec4(1, 0, 0, 1)) {
            glLineWidth(10);
            glColor3f(color.x, color.y, color.z);
            glBegin(GL_LINES);
            glVertex2f(point1.x, point1.y);
            glVertex2f(point2.x, point2.y);
            glEnd();
        }
    };

}