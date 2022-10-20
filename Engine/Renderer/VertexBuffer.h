#pragma once
#include "Renderer.h"
#include "Resource\Resource.h"
#include <vector>

namespace neu
{
	class VertexBuffer : public Resource
	{
	public:
		VertexBuffer();
		virtual ~VertexBuffer();

		bool Create(std::string name, ...) override;

		// vertex buffer
		void CreateVertexBuffer(GLsizei size, GLsizei m_vertexCount, void* data);
		void SetAttribute(int index, GLint size, GLsizei stride, size_t offset);

		// Index Buffer
		void CreateindexBuffer(GLenum indexType, GLsizei count, void* data);

		virtual void Draw(GLenum primitiveType = GL_TRIANGLES);

		void Bind() { glBindVertexArray(m_vao); }

	protected:
		GLuint m_vao = 0; // vertex array object

		GLuint m_vbo = 0; // vertex buffer object
		GLuint m_vertexCount = 0; // number of vertices in vertex buffer

		GLuint m_ibo = 0; // Index buffer object
		GLuint m_indexCount = 0; // Number of indices index buffer
		GLenum m_indexType = 0; // Data type of index

	};
}