/* (c) 2024 Conál Paxton
 * This code is licensed under MIT license(see LICENSE.txt for details) */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <chrono>
#include <thread>

#include <stdio.h>
#include <stdlib.h>

int width = 1024, height = 768;


int total = 0;

void draw(int frame) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho((float)-width/(float)height, (float)width/(float)height, -1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(frame, 0.0, 1.0, 0.0);
	glRotatef(total += (rand()%5-3), 1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
		glColor3f(glm::abs(glm::cos(frame/60.0f)), glm::abs(glm::sin(frame / 600.0f)), glm::abs(glm::sinh(frame/60.0f)));
		for (float t = 0.0; t < glm::two_pi<float>(); t += 0.00001f) {
			glVertex3f(glm::cos(10.0f*t)/10.0, glm::sin(10.0f*t)/10.0, t*glm::one_over_two_pi<float>());
		}
	glEnd();
}

int main() {
	glfwInit();
	

	/* create window, make resizeable, set simple lambda as callback, and set OpenGL version to 4.6 */
	glfwWindowHint(GLFW_RESIZABLE, true);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	GLFWwindow* win = glfwCreateWindow(width, height, "Cothrom", NULL, NULL);

	if (!win) {
		const char* err = NULL;
		glfwGetError(&err);
		fprintf(stderr, "[FATAL] GLFW Error: %s\n", err);
		exit(1);
	}
	
	glfwMakeContextCurrent(win);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "[FATAL] Error: failed to initialize GLAD (GL function loader)\n");
		exit(1);
	}

	glfwSetFramebufferSizeCallback(win, [](GLFWwindow* win, int x, int y) {
		width = x;
		height = y;
		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	});

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);
	int frame = 0;

	glPointSize(0.5);

	auto begin_frame = std::chrono::steady_clock::now();
	while (!glfwWindowShouldClose(win)) {
		auto end_frame = begin_frame + 
			std::chrono::duration_cast<std::chrono::steady_clock::duration>
				(std::chrono::duration<double>{ 1.0 / 60.0 });
		draw(frame);
		glfwPollEvents();
		glFlush();
		std::this_thread::sleep_until(end_frame);
		begin_frame = end_frame;
		frame++;
	}

	return 0;

}
