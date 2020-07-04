#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Renderer.h"

#include "imgui/imgui.h"

#include <memory>

namespace test {
	class TestTexture2D : public Test {
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture, m_Texture_2;
		std::unique_ptr<Renderer> m_Renderer;

		glm::mat4 m_Proj, m_View, m_Model, m_MVP;

		int m_RenderChoice;

		float m_QuadColor[4];
	};
}