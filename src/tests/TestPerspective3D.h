#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Renderer.h"

#include <memory>

namespace test {
	class TestPerspective3D :public Test {
	public:
		TestPerspective3D();
		~TestPerspective3D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_CrateTexture;
		std::unique_ptr<Texture> m_DirtTexture;
		std::unique_ptr<Texture> m_MaskTexture;

		std::unique_ptr<Renderer> m_Renderer;

		glm::mat4 m_Proj, m_View, m_Model, m_MVP;

		glm::vec3 m_CamTranslation, m_CamRotate;

		int m_RenderChoice;
	};
}