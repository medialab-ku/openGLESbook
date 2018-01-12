#ifndef OPENGLES_OBJECT_H
#define OPENGLES_OBJECT_H

#include "global.h"
#include "render/program.h"
#include "render/uniform.h"
#include "render/material.h"

class Object {
public:
    enum class DrawType { POINTS, LINES, TRIANGLES, PATCHES };
    Object(const ObjData& objData, const Material& material = Material({}));
    virtual void draw(const Program& program, const DrawType drawType = DrawType::TRIANGLES) const;
    glm::mat4 getWorldMatrix() const;
    float getTessLevel() const;
    float getDispFactor() const;
    Object& setWorldMatrix(const glm::mat4& worldMatrix);
    Object& setTessLevel(const float tessLevel);
    Object& setDispFactor(const float dispFactor);
protected:
    GLuint abo{ 0 };
    GLuint eabo{ 0 };
    GLsizei count{ 0 };
    glm::mat4 worldMatrix{ 1.0f };
    float tessLevel{ 10.0f };
    float dispFactor{ 10.0f };
    std::vector<Uniform> uniforms{ {
            { Uniform::Type::MAT4, "worldMat", glm::value_ptr(worldMatrix) },
            { Uniform::Type::FLOAT, "tessLevel", &tessLevel },
            { Uniform::Type::FLOAT, "dispFactor", &dispFactor }
    } };
    Material material;
private:
    void createBuffers();
    void setBufferData(const ObjData& objData);
};

#endif // OPENGLES_OBJECT_H
