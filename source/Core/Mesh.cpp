#include <iostream>
#include <string>

#include <Core/Mesh.h>

Mesh::Mesh(Geometry *inputGeometry, Material *inputMaterial, GLuint inputShaderProgram, GLuint inputShaderProgramShadows)
    : geometry(inputGeometry), material(inputMaterial), shaderProgram(inputShaderProgram), shaderProgramShadows(inputShaderProgramShadows)
{
    vao = 0;
    vbo = 0;
    nbo = 0;
    ibo = 0;

    geometry->setupVertices();
    geometry->setupNormals();
    geometry->setupIndices();

    setupModelMatrix();
    setupVertexData();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &nbo);
    glDeleteBuffers(1, &ibo);
}

void Mesh::render(glm::mat4 view, glm::mat4 projection, float deltaTime) {
    setupModelMatrix();
    // setupVertexData();

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(material->getColor()));
    glUniform1f(glGetUniformLocation(shaderProgram, "alpha"), material->getAlpha());

    glBindVertexArray(vao);
    std::vector<GLint> indices = geometry->getIndices();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size() * sizeof(float)), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh::setupModelMatrix() {
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0), geometry->getPosition());

    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0), glm::radians(geometry->getRotation().x), glm::vec3(1.0, 0.0, 0.0));
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(geometry->getRotation().y), glm::vec3(0.0, 1.0, 0.0));
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(geometry->getRotation().z), glm::vec3(0.0, 0.0, 1.0));

    glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0), geometry->getScale());

    model = translation_matrix * rotation_matrix * scale_matrix;
}

void Mesh::setupVertexData() {
    std::vector<GLfloat> vertices = geometry->getVertices();
    std::vector<GLfloat> normals = geometry->getNormals();
    std::vector<GLint> indices = geometry->getIndices();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // position buffer
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);
    // normals buffer
    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(normals.size() * sizeof(float)), normals.data(), GL_STATIC_DRAW);
    // indices
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(indices.size() * sizeof(int)), indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);
    // normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}