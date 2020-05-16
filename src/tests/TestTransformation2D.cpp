#include "TestTransformation2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace test {
	TestTransformation2D::TestTransformation2D()
		:m_Translation{ 400, 200, 0 },
		m_Proj{ glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f) },
		m_View{ glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)) },
		m_Model{ glm::translate(glm::mat4(1.0f), m_Translation) },
		m_MVP{ m_Proj * m_View * m_Model },
		m_QuadColor{ 0.2f,0.3f,0.4f,1.0f },
		m_Rotate{ 1.0f }, m_Scale{ 1.0f }
	{
		// Vertex Data
		float positions[] = {
			-100.0f, -100.0f,
			 100.0f, -100.0f,
			 100.0f,  100.0f,
			-100.0f,  100.0f
		};

		// Index Data
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GLCALL(glDisable(GL_DEPTH_TEST));

		// Vertex Array Object
		m_VAO = std::make_unique<VertexArray>();

		// Vertex Buffer Object
		m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 2 * sizeof(float));

		// Create a layout for OpenGL to read data from VertexBuffer properly
		VertexBufferLayout layout;
		layout.Push<float>(2);

		// Add the buffer and the vertex layout to the vertex array object
		m_VAO->AddBuffer(*m_VBO, layout);

		// Index Buffer Object
		m_IBO = std::make_unique<IndexBuffer>(indices, 6);

		// Create and compile shader from location and bind
		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();

		m_Shader->SetUniform1i("u_RenderChoice", 2);

		m_Renderer = std::make_unique<Renderer>();
	}

	TestTransformation2D::~TestTransformation2D()
	{
	}

	void TestTransformation2D::OnUpdate(float deltaTime)
	{
		m_Model = glm::translate(glm::mat4(1.0f), *&m_Translation);
		m_Model = glm::rotate(m_Model, glm::radians(*&m_Rotate), glm::vec3(0.0f, 0.0f, 1.0f));
		m_Model = glm::scale(m_Model, glm::vec3(*&m_Scale, *&m_Scale, 0.0f));

		m_MVP = m_Proj * m_View * m_Model;
	}

	void TestTransformation2D::OnRender()
	{
		GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));

		m_Shader->SetUniformMat4f("u_MVP", m_MVP);
		m_Shader->SetUniform4f("u_Color", m_QuadColor[0], m_QuadColor[1], m_QuadColor[2], m_QuadColor[3]);

		m_Renderer->Draw(*m_VAO, *m_IBO, *m_Shader); // Draw Call
	}

	void TestTransformation2D::OnImGuiRender()
	{
		ImGui::ColorEdit4("Quad Color", m_QuadColor);
		ImGui::Spacing();
		ImGui::SliderFloat2("Translation", &m_Translation.x, 0.0f, 960.0f);
		ImGui::SliderFloat("Rotation", &m_Rotate, 0.0f, 360.0f);
		ImGui::SliderFloat("Scaling", &m_Scale, 0.0f, 10.0f);
	}
}