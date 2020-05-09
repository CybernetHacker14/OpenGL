#include "TestTexture2D.h"
#include "ErrorManager.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

namespace test {
	TestTexture2D::TestTexture2D()
		:m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0),
		m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), // Projection Matrix
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))) // View Matrix
	{
		// Vertex Data
		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f,// Vertex 0 (X,Y)
			 50.0f, -50.0f, 1.0f, 0.0f,// Vertex 1 (X,Y)
			 50.0f,  50.0f, 1.0f, 1.0f,// Vertex 2 (X,Y)
			-50.0f,  50.0f, 0.0f, 1.0f// Vertex 3 (X,Y)
		};

		// Index Data
		unsigned int indices[] = {
			0, 1, 2,
			2 ,3, 0
		};

		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		// Vertex Array Object
		m_VAO = std::make_unique<VertexArray>();

		// Vertex Buffer Object
		m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

		// Create a layout for OpenGL to read data from VertexBuffer properly
		VertexBufferLayout layout;
		layout.Push<float>(2); // Two float values as one single 2d-position for vertex
		layout.Push<float>(2); // Two float values as texture co-ordinates per vertex

		// We add the vertex buffer and the layout to the vertex array object
		m_VAO->AddBuffer(*m_VBO, layout);

		// Index Buffer Object
		m_IBO = std::make_unique<IndexBuffer>(indices, 6);

		// Create and Compile shader from location and Bind
		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();

		m_Texture = std::make_unique<Texture>("res/textures/test_texture.png");

		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		m_Texture->Bind(); // slot value of this should match the slot uniform value below

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA); // Model Matrix
			glm::mat4 mvp = m_Proj * m_View * model; // The MVP Matrix. OpenGL expects multiplication in this order only.

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IBO, *m_Shader); // Draw Call
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB); // Model Matrix
			glm::mat4 mvp = m_Proj * m_View * model; // The MVP Matrix. OpenGL expects multiplication in this order only.

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IBO, *m_Shader); // Draw Call
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat2("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat2("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
	}
}