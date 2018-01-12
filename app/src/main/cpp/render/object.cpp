#include "object.h"

Object::Object(const ObjData& objData, const Material& material) : material(material) {
    // create buffers
    createBuffers();

    // set buffer data to object data
    setBufferData(objData);
}

void Object::draw(const Program& program, const DrawType drawType) const {
    // update uniforms
    for (const Uniform& uniform : uniforms) uniform.update(program);

    // update material
    material.update(program);

    // bind
    glBindBuffer(GL_ARRAY_BUFFER, abo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eabo);

    // set vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (const GLvoid*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (const GLvoid*) offsetof(Vertex, nor));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (const GLvoid*) offsetof(Vertex, tex));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (const GLvoid*) offsetof(Vertex, tan));

    // draw elements by draw type
    switch (drawType) {
        case DrawType::POINTS:
            glDrawElements(GL_POINTS, count, GL_UNSIGNED_SHORT, (const GLvoid*) 0);
            break;
        case DrawType::LINES:
            glDrawElements(GL_LINES, count, GL_UNSIGNED_SHORT, (const GLvoid*) 0);
            break;
        case DrawType::TRIANGLES:
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, (const GLvoid*) 0);
            break;
        case DrawType::PATCHES:
            glDrawElements(GL_PATCHES, count, GL_UNSIGNED_SHORT, (const GLvoid*) 0);
            break;
    }
}

glm::mat4 Object::getWorldMatrix() const {
    return worldMatrix;
}

float Object::getTessLevel() const {
    return tessLevel;
}

float Object::getDispFactor() const {
    return dispFactor;
}

Object& Object::setWorldMatrix(const glm::mat4& worldMatrix) {
    this->worldMatrix = worldMatrix;
    return *this;
}

Object &Object::setTessLevel(const float tessLevel) {
    this->tessLevel = tessLevel;
    return *this;
}

Object &Object::setDispFactor(const float dispFactor) {
    this->dispFactor = dispFactor;
    return *this;
}

void Object::createBuffers() {
    LOG_PRINT_DEBUG("Create buffer objects");

    // create array buffer object
    glGenBuffers(1, &abo);
    if (!abo) LOG_PRINT_ERROR("Fail to create array buffer object");

    // create elementary array buffer object
    glGenBuffers(1, &eabo);
    if (!eabo) LOG_PRINT_ERROR("Fail to create element array buffer object");
}

void Object::setBufferData(const ObjData &objData) {
    LOG_PRINT_DEBUG("Set data of buffer objects");

    // set array buffer object data
    glBindBuffer(GL_ARRAY_BUFFER, abo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) objData.vertices.size() * sizeof(Vertex),
                 objData.vertices.data(), GL_STATIC_DRAW);

    // set element array buffer object data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eabo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) objData.indices.size() * sizeof(Index),
                 objData.indices.data(), GL_STATIC_DRAW);

    // set element count
    count = (GLsizei) objData.indices.size();
}
