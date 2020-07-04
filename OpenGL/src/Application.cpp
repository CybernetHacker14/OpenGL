#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestRenderQuad.h"
#include "tests/TestTransformation2D.h"
#include "tests/TestCameraControls2D.h"
#include "tests/TestPerspective3D.h"
#include "tests/TestCameraControls3D.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// Set OpenGL version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "OpenGL Tutorial", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Kind of vsync
	glfwSwapInterval(1);

	// Shows if any error has turned up
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
	}

	// Prints the current used OpenGL version to the console
	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		Renderer renderer;

		// Setup IMGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::TestRenderQuad>("Render Quad");
		testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
		testMenu->RegisterTest<test::TestTransformation2D>("2D Transformations");
		testMenu->RegisterTest<test::TestCameraControls2D>("2D Camera Controls");
		testMenu->RegisterTest<test::TestPerspective3D>("3D Perspective");

		while (!glfwWindowShouldClose(window))
		{
			GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest) {
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();

				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-")) {
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		delete currentTest;
		if (currentTest != testMenu) {
			delete testMenu;
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}