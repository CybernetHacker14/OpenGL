#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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
	window = glfwCreateWindow(960, 540, "OpenGL Tutorial", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Setup IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

	// Kind of vsync
	glfwSwapInterval(1);

	// Shows if any error has turned up
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
	}

	// Prints the current used OpenGL version to the console
	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		// Vertex Data
		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f,// Vertex 0 (X,Y)
			 50.0f, -50.0f, 1.0f, 0.0f,// Vertex 1 (X,Y)
			 50.0f,  50.0f, 1.0f, 1.0f,// Vertex 2 (X,Y)
			-50.0f,  50.0f, 0.0f, 1.0f// Vertex 3 (X,Y)
		};

		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		// Index Data
		unsigned int indices[] = {
			0, 1, 2,
			2 ,3, 0
		};

		// Vertex Array Object
		VertexArray va;

		// Vertex Buffer Object
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		// Create a layout for OpenGL to read data from VertexBuffer properly
		VertexBufferLayout layout;
		layout.Push<float>(2); // Two float values as one single 2d-position for vertex
		layout.Push<float>(2); // Two float values as texture co-ordinates per vertex

		// We add the vertex buffer and the layout to the vertex array object
		va.AddBuffer(vb, layout);

		// Index Buffer Object
		IndexBuffer ib(indices, 6);

		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f); // Projection Matrix
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // View Matrix
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0)); // Model Matrix

		glm::mat4 mvp = proj * view * model; // The MVP Matrix. OpenGL expects multiplication in this order only.

		// Create and Compile shader from location and Bind
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		Texture texture("res/textures/test_texture.png");
		texture.Bind(); // slot value of this should match the slot uniform value below
		shader.SetUniform1i("u_Texture", 0);

		// Unbind everything
		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		Renderer renderer;

		glm::vec3 translationA(200, 200, 0);

		glm::vec3 translationB(400, 200, 0);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			// New Frame IMGUI
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			shader.Bind();

			// Switch modes based on key press
			if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
				GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
			}
			if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
				GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
			}
			if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
				GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_POINT));
			}

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA); // Model Matrix
				glm::mat4 mvp = proj * view * model; // The MVP Matrix. OpenGL expects multiplication in this order only.
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(va, ib, shader); // Draw Call
			}

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB); // Model Matrix
				glm::mat4 mvp = proj * view * model; // The MVP Matrix. OpenGL expects multiplication in this order only.
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(va, ib, shader); // Draw Call
			}

			{
				//ImGui::Begin("Object Controls");
				ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);
				ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
				//ImGui::End();
			}

			// Render IMGUI
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	// Shutdown IMGUI
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}