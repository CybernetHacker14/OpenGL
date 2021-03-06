#include "TestCameraControls3D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

#include <imgui/imgui.h>

namespace test {
	TestCameraControls3D::TestCameraControls3D()
		:m_Proj{ glm::perspective(glm::radians(45.0f), 1920.0f / 1080.f, 0.1f, 50.0f) },
		m_View{ glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3)) },
		m_Model{ glm::translate(glm::mat4(1.0f), glm::vec3(-1, 0, 0)) },
		m_MVP{ m_Proj * m_View * m_Model }
	{
		// Vertex Data
		float positions[] = {
			-1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // Vertex 0 (X,Y,Z)
			 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, // Vertex 1 (X,Y,Z)
			 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, // Vertex 2 (X,Y,Z)
			-1.0f,  1.0f,  1.0f, 0.0f, 1.0f, // Vertex 3 (X,Y,Z)

			-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, // Vertex 4 (X,Y,Z)
			-1.0f, -1.0f,  1.0f, 1.0f, 0.0f, // Vertex 5 (X,Y,Z)
			-1.0f,  1.0f,  1.0f, 1.0f, 1.0f, // Vertex 6 (X,Y,Z)
			-1.0f,  1.0f, -1.0f, 0.0f, 1.0f, // Vertex 7 (X,Y,Z)

			-1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // Vertex 8 (X,Y,Z)
			 1.0f,  1.0f,  1.0f, 1.0f, 0.0f, // Vertex 9 (X,Y,Z)
			 1.0f,  1.0f, -1.0f, 1.0f, 1.0f, // Vertex 10 (X,Y,Z)
			-1.0f,  1.0f, -1.0f, 0.0f, 1.0f, // Vertex 11 (X,Y,Z)

			 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, // Vertex 12 (X,Y,Z)
			-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, // Vertex 13 (X,Y,Z)
			-1.0f,  1.0f, -1.0f, 1.0f, 1.0f, // Vertex 14 (X,Y,Z)
			 1.0f,  1.0f, -1.0f, 0.0f, 1.0f, // Vertex 15 (X,Y,Z)

			 1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // Vertex 15 (X,Y,Z)
			 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, // Vertex 15 (X,Y,Z)
			 1.0f,  1.0f, -1.0f, 1.0f, 1.0f, // Vertex 15 (X,Y,Z)
			 1.0f,  1.0f,  1.0f, 0.0f, 1.0f, // Vertex 15 (X,Y,Z)
		};

		// Index Data
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			8, 9, 10,
			10, 11, 8,

			12, 13, 14,
			14, 15, 12,

			16, 17, 18,
			18, 19, 16
		};

		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GLCALL(glEnable(GL_DEPTH_TEST));

		// Vertex Array Object
		m_VAO = std::make_unique<VertexArray>();

		// Vertex Buffer Object
		m_VBO = std::make_unique<VertexBuffer>(positions, 5 * 20 * sizeof(float));

		// Create a layout for OpenGL to read data from VertexBuffer properly
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);

		// We add the vertex buffer and the layout to the vertex array object
		m_VAO->AddBuffer(*m_VBO, layout);

		// Index Buffer Object
		m_IBO = std::make_unique<IndexBuffer>(indices, 6 * 5);

		// Create and Compile shader from location and Bind
		m_Shader = std::make_unique<Shader>("res/shaders/Grunge.shader");
		m_Shader->Bind();

		m_CrateTexture = std::make_unique<Texture>("res/textures/crate2_diffuse.png");
		m_DirtTexture = std::make_unique<Texture>("res/textures/dirt_diffuse.png");
		m_MaskTexture = std::make_unique<Texture>("res/textures/grunge/grunge2.png");

		m_CrateTexture->Bind();
		m_DirtTexture->Bind(1);
		m_MaskTexture->Bind(2);

		m_Shader->SetUniform1i("crateTexture", 0);
		m_Shader->SetUniform1i("dirtTexture", 1);
		m_Shader->SetUniform1i("maskTexture", 2);

		m_Shader->SetUniform1i("renderChoice", 1);

		m_Renderer = std::make_unique<Renderer>();
	}

	TestCameraControls3D::~TestCameraControls3D()
	{
	}

	void TestCameraControls3D::OnUpdate(float deltaTime)
	{
		m_MVP = m_Proj * m_View * m_Model;
	}

	void TestCameraControls3D::OnRender()
	{
		GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		m_Shader->SetUniformMat4f("u_MVP", m_MVP);

		m_Renderer->Draw(*m_VAO, *m_IBO, *m_Shader);
	}

	void TestCameraControls3D::OnImGuiRender()
	{
	}
}