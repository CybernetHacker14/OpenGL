#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

#include "imgui/imgui.h"

#include <memory>

namespace test {
	class TestCameraControls2D : public Test {
	public:
		TestCameraControls2D();
		~TestCameraControls2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Renderer> m_Renderer;

		glm::mat4 m_Proj, m_View, m_Model, m_MVP;

		glm::vec3 m_Translation;

		float m_QuadColor[4];
	};
}