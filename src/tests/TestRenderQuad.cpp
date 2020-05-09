#include "TestRenderQuad.h"
#include "ErrorManager.h"

#include "imgui/imgui.h"

namespace test {
	TestRenderQuad::TestRenderQuad()
		: m_QuadColor{ 0.2f,0.3f,0.1f,1.0f },
		m_VertexPos1{ 0.0f,0.0f },
		m_VertexPos2{ 0.0f,0.0f },
		m_VertexPos3{ 0.0f,0.0f },
		m_VertexPos4{ 0.0f,0.0f }
	{
	}

	TestRenderQuad::~TestRenderQuad()
	{
	}

	void TestRenderQuad::OnUpdate(float deltaTime)
	{
	}

	void TestRenderQuad::OnRender()
	{
	}

	void TestRenderQuad::OnImGuiRender()
	{
	}
}