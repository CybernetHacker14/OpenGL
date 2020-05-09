#pragma once

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "glm/glm.hpp"

namespace test {
	class TestRenderQuad : public Test {
	public:
		TestRenderQuad();
		~TestRenderQuad();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_QuadColor[4];
		float m_Positions[16];

		float m_Indices[6];

		glm::vec2 m_VertexPos1;
		glm::vec2 m_VertexPos2;
		glm::vec2 m_VertexPos3;
		glm::vec2 m_VertexPos4;
	};
}