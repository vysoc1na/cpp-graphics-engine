#include <iostream>
#include <string>

#include <Core/Mesh.h>

Mesh::Mesh(Geometry *inputGeometry, Material *inputMaterial) : geometry(inputGeometry), material(inputMaterial) {
    vao = 0;
    vbo = 0;
    ebo = 0;

    geometry->setupVertices();
    geometry->setupIndices();

    setupModelMatrix();
    setupVertexData();

    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec3 color;
        uniform float alpha;
        void main() {
            // vec2 uv = gl_FragCoord.xy / vec2(1600, 1200);
            FragColor = vec4(color, alpha);
        }
    )";

    GLuint vertexShader = loadShaderFromSource(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShaderFromSource(fragmentShaderSource, GL_FRAGMENT_SHADER);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glDeleteProgram(shaderProgram);
}

void Mesh::render(glm::mat4 view, glm::mat4 projection, float deltaTime) {
    glUseProgram(shaderProgram);

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

    glUseProgram(0);
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
    std::vector<GLint> indices = geometry->getIndices();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(indices.size() * sizeof(float)), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::checkShaderCompileErrors(GLuint shader, const std::string &type) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Error: " << type << " compilation failed\n" << infoLog << std::endl;
        std::exit(-1);
    }
}

GLuint Mesh::loadShaderFromSource(const char* shaderSource, GLenum shaderType) {
    // Create and compile shader
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // Check for shader compilation errors
    checkShaderCompileErrors(shader, "Shader");

    return shader;
}