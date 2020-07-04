#include "Renderer.h"

void Renderer::Clear() const
{
	/* Render here */
	GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	// Bind Shader
	shader.Bind();
	// Bind Vertex Array Object and Index Buffer Object
	va.Bind();
	ib.Bind();

	GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr)); // Draw Call
}