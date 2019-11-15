#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768

// Vertex Buffer Identifiers
#define VERTICES 0
#define INDICES 1
#define GLOBAL_MATRICES 2
#define MODEL_MATRIX 3
#define LIGHT_PROPERTIES 4
#define MATERIAL_PROPERTIES 5
#define CAMERA_PROPERTIES 6
//Run, would you kindly?
#define DYNAMIC_LIGHT 7
#define BOX_MODEL 8
#define BOX_INDICES 9
#define BOX_VERTICIES 10
#define NUM_BUFFERS 11


// Vertex Array attributes
#define POSITION 0
#define COLOR 1
#define NORMAL 2
#define UV 3

// Vertex Array binding points
#define STREAM0 0

// GLSL Uniform indices
#define TRANSFORM0 0
#define TRANSFORM1 1
#define LIGHT 2
#define MATERIAL 3
#define CAMERA 4
#define DYNAMICLIGHT 9

// GLSL SHADER 2
#define TRANSFORM5 5
#define TRANSFORM6 6

// Vertices
GLfloat vertices[] = {
	// Front
	-20.0f, 20.0f, 20.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-20.0f, -20.0f, 20.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	20.0f, -20.0f, 20.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	20.0f, 20.0f, 20.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	// Back
	20.0f, 20.0f, -20.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	20.0f, -20.0f, -20.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	-20.0f, -20.0f, -20.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	-20.0f, 20.0f, -20.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
	// Left
	-10.0f, 10.0f, -20.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-20.0f, -10.0f, -20.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-10.0f, -10.0f, 20.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-10.0f, 10.0f, 20.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	// Right
	20.0f, 20.0f, 20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	20.0f, -20.0f, 20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	20.0f, -20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	20.0f, 20.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	// Top
	-20.0f, 20.0f, -20.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-20.0f, 20.0f, 20.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	20.0f, 20.0f, 20.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	20.0f, 20.0f, -20.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	// Bottom
	-20.0f, -20.0f, 20.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
	-20.0f, -20.0f, -20.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
	20.0f, -20.0f, -20.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
	20.0f, -20.0f, 20.0f,  0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
};

GLfloat box[] = {
	//Front
	-5.0f, -10.0f, -19.0f, 0.0f, 1.0f,
	-5.0f, -20.0f, -19.0f, 0.0f, 0.0f, 
	5.0f, -20.0f, -19.0f, 1.0f, 0.0f,
	5.0f, -10.0f, -19.0f, 1.0f, 1.0f, 
	//Back
	19.0f, -10.0f, 5.0f, 0.0f, 1.0f,
	19.0f, -20.0f, 5.0f, 0.0f, 0.0f,
	19.0f, -20.0f, -5.0f, 1.0f, 0.0f,
	19.0f, -10.0f, -5.0f, 1.0f, 1.0f,
};

GLushort boxindices[]{
	//Front
	0, 1, 2, 2, 3, 0,
	//Back
	4, 5, 6, 6, 7, 4
};

GLushort indices[]{
	// Front
	0, 1, 2, 2, 3, 0,
	// Back
	4, 5, 6, 6, 7, 4,
	// Left
	8, 9, 10, 10, 11, 8,
	// Right
	12, 13, 14, 14, 15, 12,
	// Top
	16, 17, 18, 18, 19, 16,
	// Bottom
	20, 21, 22, 22, 23, 20
};

// Eget array for lightPosition! Fjerne position fra lightproperties.
GLfloat lightPosition[]{
	0.0f, 0.0f, 4.0f, 0.0f
};


// Light properties (4 valued vectors due to std140 see OpenGL 4.5 reference)
GLfloat lightProperties[]{
	// Position
	// 0.0f, 0.0f, 4.0f, 0.0f,
	// Ambient Color
	0.3f, 0.3f, 0.3f, 0.0f,
	//0.0f, 0.0f, 0.2f, 0.0f,
	// Diffuse Color
	0.5f, 0.5f, 0.5f, 0.0f,
	// Specular Color
	0.6f, 0.6f, 0.6f, 0.0f
};

GLfloat materialProperties[] = {
	// Shininess color
	1.0f, 1.0f, 1.0f, 1.0f,
	// Shininess
	32.0f
};

// Camera properties 
GLfloat cameraProperties[]{
	0.0f, 0.0f, 4.0f
};

// Pointers for updating GPU data
GLfloat *projectionMatrixPtr;
GLfloat *viewMatrixPtr;
GLfloat *modelMatrixPtr;

// POINTER FOR BOX
GLfloat *boxModelMatrixPtr;

// Pointer for light pos
GLfloat *lightPosPtr;

// Names
GLuint programName;
GLuint vertexArrayName;

// EGEN BOX VERTEX ARRAY
GLuint boxVertexArray;

// Texture
GLuint textureTest;
GLuint frameBuffer;
GLuint renderProgram;

GLuint renderBufferObject;

// HOLDER PÅ ALLE BUFFERE, CAPS ØVERST.
GLuint vertexBufferNames[11];

GLuint textureName;


GLint width, height, numChannels;

//Camera variables 
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Virtual view 
glm::mat4 view = glm::mat4(1.0f);

//Fencing


//Mouse callback
void handleMouse(GLFWwindow* window, double xpos, double ypos);
float lastX = DEFAULT_WIDTH / 2.0f;
float lastY = DEFAULT_HEIGHT / 2.0f;
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;

int counter = 0;

//Brukt for å toggle FBO
bool fboToggle = false;



/*
 * Read shader source file from disk
 */
char *readSourceFile(const char *filename, int *size) {

	// Open the file as read only
	FILE *file = fopen(filename, "r");

	// Find the end of the file to determine the file size
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);

	// Rewind
	fseek(file, 0, SEEK_SET);

	// Allocate memory for the source and initialize it to 0
	char *source = (char *)malloc(fileSize + 1);
	for (int i = 0; i <= fileSize; i++) source[i] = 0;

	// Read the source
	fread(source, fileSize, 1, file);

	// Close the file
	fclose(file);

	// Store the size of the file in the output variable
	*size = fileSize - 1;

	// Return the shader source
	return source;

}

/*
 * Callback function for OpenGL debug messages
 */
void glDebugCallback(GLenum sources, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, const void *userParam) {
	printf("DEBUG: %s\n", msg);
}

/*
 * Initialize OpenGL
 */
int initGL() {

	// Register the debug callback function
	glDebugMessageCallback(glDebugCallback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	// Create and initialize 4 buffer names, DENNA Æ 9 NÅ.
	glCreateBuffers(11, vertexBufferNames);

	//NAMED BUFFER STORAGE.
	glNamedBufferStorage(vertexBufferNames[BOX_VERTICIES], 5 * 4 * 2 *  sizeof(GLfloat), box, 0);
	glNamedBufferStorage(vertexBufferNames[BOX_INDICES],  6 * 2 * sizeof(GLshort), boxindices, 0);

	// Allocate storage for the vertex array buffers
	glNamedBufferStorage(vertexBufferNames[VERTICES], 6 * 4 * 9 * sizeof(GLfloat), vertices, 0);

	// Allocate storage for the triangle indices
	glNamedBufferStorage(vertexBufferNames[INDICES], 3 * 2 * 6 * sizeof(GLshort), indices, 0);


	// Allocate storage for the transformation matrices and retrieve their addresses
	glNamedBufferStorage(vertexBufferNames[GLOBAL_MATRICES], 16 * sizeof(GLfloat) * 2, NULL, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	glNamedBufferStorage(vertexBufferNames[MODEL_MATRIX], 16 * sizeof(GLfloat), NULL, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	
	glNamedBufferStorage(vertexBufferNames[BOX_MODEL], 16 * sizeof(GLfloat), NULL, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

	// Allocate storage for the buffers used for lighting calculations ENDRET LIGHT TIL 12
	glNamedBufferStorage(vertexBufferNames[LIGHT_PROPERTIES], 12 * sizeof(GLfloat), lightProperties, 0);
	//GJØR LIGHTPOSITION SKRIVBAR.
	glNamedBufferStorage(vertexBufferNames[DYNAMIC_LIGHT], 4 * sizeof(GLfloat), lightPosition, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	glNamedBufferStorage(vertexBufferNames[MATERIAL_PROPERTIES], 5 * sizeof(GLfloat), materialProperties, 0);
	glNamedBufferStorage(vertexBufferNames[CAMERA_PROPERTIES], 3 * sizeof(GLfloat), cameraProperties, 0);

	// Get a pointer to the global matrices data
	GLfloat *globalMatricesPtr = (GLfloat *)glMapNamedBufferRange(vertexBufferNames[GLOBAL_MATRICES], 0, 16 * sizeof(GLfloat) * 2,
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	projectionMatrixPtr = globalMatricesPtr;
	viewMatrixPtr = globalMatricesPtr + 16;

	// Get a pointer to the model matrix data
	modelMatrixPtr = (GLfloat *)glMapNamedBufferRange(vertexBufferNames[MODEL_MATRIX], 0, 16 * sizeof(GLfloat),
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	boxModelMatrixPtr = (GLfloat *)glMapNamedBufferRange(vertexBufferNames[BOX_MODEL], 0, 16 * sizeof(GLfloat),
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	lightPosPtr = (GLfloat *)glMapNamedBufferRange(vertexBufferNames[DYNAMIC_LIGHT], 0, 4 * sizeof(GLfloat),
		GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	// Create and initialize a vertex array object
	glCreateVertexArrays(1, &vertexArrayName);

	//BOX
	glCreateVertexArrays(1, &boxVertexArray);


	// Associate attributes with binding points
	glVertexArrayAttribBinding(vertexArrayName, POSITION, STREAM0);
	glVertexArrayAttribBinding(vertexArrayName, COLOR, STREAM0);
	glVertexArrayAttribBinding(vertexArrayName, NORMAL, STREAM0);

	
	glVertexArrayAttribBinding(boxVertexArray, POSITION, STREAM0);
	glVertexArrayAttribBinding(boxVertexArray, UV, STREAM0);
	

	// Specify attribute format
	glVertexArrayAttribFormat(vertexArrayName, POSITION, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(vertexArrayName, COLOR, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT));
	glVertexArrayAttribFormat(vertexArrayName, NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT));
	
	glVertexArrayAttribFormat(boxVertexArray, POSITION, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(boxVertexArray, UV, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT));
	
	// Enable the attributes
	glEnableVertexArrayAttrib(vertexArrayName, POSITION);
	glEnableVertexArrayAttrib(vertexArrayName, COLOR);
	glEnableVertexArrayAttrib(vertexArrayName, NORMAL);
	
	glEnableVertexArrayAttrib(boxVertexArray, POSITION);
	glEnableVertexArrayAttrib(boxVertexArray, UV);
	
	// Bind the indices to the vertex array
	glVertexArrayElementBuffer(vertexArrayName, vertexBufferNames[INDICES]);
	
	glVertexArrayElementBuffer(boxVertexArray, vertexBufferNames[BOX_INDICES]);

	// Bind the vertex buffer to the vertex array
	glVertexArrayVertexBuffer(vertexArrayName, STREAM0, vertexBufferNames[VERTICES], 0, 9 * sizeof(GLfloat));

	glVertexArrayVertexBuffer(boxVertexArray, STREAM0, vertexBufferNames[BOX_VERTICIES], 0, 5 * sizeof(GLfloat));

	//------------------------------RENDER TO TEXTURE ----------------------------------------------------------

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	// The texture we're going to render to
	glGenTextures(1, &textureName);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureName);

	// tomt bilde
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// CUSTOMIZE SJØL
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	// "render buffer object"
	glGenRenderbuffers(1, &renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);

	// COLOR ATTACHMENT
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureName, 0);

	// draw buffaaaaaahs
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	// stjælt sjækk
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	//glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//glViewport(0, 0, 1024, 768);



		//------------------------------RENDER TO TEXTURE ----------------------------------------------------------

	// Load and compile vertex shader
	GLuint vertexName = glCreateShader(GL_VERTEX_SHADER);
	int vertexLength = 0;
	char *vertexSource = readSourceFile("res/shaders/Shader.vert", &vertexLength);
	glShaderSource(vertexName, 1, (const char * const *)&vertexSource, &vertexLength);
	GLint compileStatus;
	glCompileShader(vertexName);
	glGetShaderiv(vertexName, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		GLint logSize = 0;
		glGetShaderiv(vertexName, GL_INFO_LOG_LENGTH, &logSize);
		char *errorLog = (char *)malloc(sizeof(char) * logSize);
		glGetShaderInfoLog(vertexName, logSize, &logSize, errorLog);
		glDeleteShader(vertexName);
		printf("VERTEX ERROR %s\n", errorLog);
		return 0;
	}
	free(vertexSource);

	// Load and compile fragment shader
	GLuint fragmentName = glCreateShader(GL_FRAGMENT_SHADER);
	int fragmentLength = 0;
	char *fragmentSource = readSourceFile("res/shaders/Shader.frag", &fragmentLength);
	glShaderSource(fragmentName, 1, (const char * const *)&fragmentSource, &fragmentLength);
	glCompileShader(fragmentName);
	glGetShaderiv(fragmentName, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		GLint logSize = 0;
		glGetShaderiv(fragmentName, GL_INFO_LOG_LENGTH, &logSize);
		char *errorLog = (char *)malloc(sizeof(char) * logSize);
		glGetShaderInfoLog(fragmentName, logSize, &logSize, errorLog);
		glDeleteShader(fragmentName);

		printf("FRAGMENT ERROR %s\n", errorLog);
		return 0;
	}
	free(fragmentSource);

	// RENDER TO TEXTURE --------------------------------------------------
	/* PRØVE UTTA DENNA
	GLuint renderVertex = glCreateShader(GL_VERTEX_SHADER);
	int rendervertexLength = 0;
	char *rendervertexSource = readSourceFile("res/shaders/RenderShader.vert", &rendervertexLength);
	glShaderSource(renderVertex, 1, (const char * const *)&rendervertexSource, &rendervertexLength);
	glCompileShader(renderVertex);
	glGetShaderiv(renderVertex, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		GLint logSize = 0;
		glGetShaderiv(renderVertex, GL_INFO_LOG_LENGTH, &logSize);
		char *errorLog = (char *)malloc(sizeof(char) * logSize);
		glGetShaderInfoLog(renderVertex, logSize, &logSize, errorLog);
		glDeleteShader(renderVertex);
		printf("VERTEX ERROR %s\n", errorLog);
		return 0;
	}
	free(rendervertexSource);
	*/
	// Load and compile fragment shader
	GLuint renderFragment = glCreateShader(GL_FRAGMENT_SHADER);
	int renderfragmentLength = 0;
	char *renderfragmentSource = readSourceFile("res/shaders/RenderShader.frag", &renderfragmentLength);
	glShaderSource(renderFragment, 1, (const char * const *)&renderfragmentSource, &renderfragmentLength);
	glCompileShader(renderFragment);
	glGetShaderiv(renderFragment, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		GLint logSize = 0;
		glGetShaderiv(renderFragment, GL_INFO_LOG_LENGTH, &logSize);
		char *errorLog = (char *)malloc(sizeof(char) * logSize);
		glGetShaderInfoLog(renderFragment, logSize, &logSize, errorLog);
		glDeleteShader(renderFragment);

		printf("FRAGMENT ERROR %s\n", errorLog);
		return 0;
	}
	free(renderfragmentSource);

	// RENDER TO TEXTURE --------------------------------------------------

	// Create and link vertex program
	programName = glCreateProgram();
	glAttachShader(programName, vertexName);
	glAttachShader(programName, fragmentName);
	glLinkProgram(programName);
	GLint linkStatus;
	glGetProgramiv(programName, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus) {
		GLint logSize = 0;
		glGetProgramiv(programName, GL_INFO_LOG_LENGTH, &logSize);
		char *errorLog = (char *)malloc(sizeof(char) * logSize);
		glGetProgramInfoLog(programName, logSize, &logSize, errorLog);

		printf("LINK ERROR %s\n", errorLog);
		return 0;
	}

	// Enable depth buffer testing
	glEnable(GL_DEPTH_TEST);


	// PROGRAM 2 -----------------------------------------------

	renderProgram = glCreateProgram();
	glAttachShader(renderProgram, vertexName);
	glAttachShader(renderProgram, renderFragment);
	glLinkProgram(renderProgram);
	GLint renderlinkStatus;
	glGetProgramiv(renderProgram, GL_LINK_STATUS, &renderlinkStatus);
	if (!renderlinkStatus) {
		GLint logSize = 0;
		glGetProgramiv(renderProgram, GL_INFO_LOG_LENGTH, &logSize);
		char *errorLog = (char *)malloc(sizeof(char) * logSize);
		glGetProgramInfoLog(renderProgram, logSize, &logSize, errorLog);

		printf("LINK ERROR %s\n", errorLog);
		return 0;
	}


	// PROGRAM 2 -----------------------------------------------


	return 1;

}


/*
 * Draw OpenGL screne
 */

void drawGLScene(glm::mat4 view) {

	//glBindFrameBuffer(GL_FRAMEBUFFER, frameBuffer);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//glBindBuffer(GL_FRAMEBUFFER, frameBuffer);
	// Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	// Någgå slekk her tenkte e.

	//memcpy Viewmatrise
	//memcpy(viewMatrixPtr, &view[0][0], 16 * sizeof(GLfloat));
	//memcpy(fboViewMatrixPtr, &view[0][0], 16 * sizeof(GLfloat));

	memcpy(viewMatrixPtr, &view[0][0], 16 * sizeof(GLfloat));

	//memcpy(fboViewMatrixPtr, &view[0][0], 16 * sizeof(GLfloat));

	//LIght

	//PsuedoGravity
	if (cameraPos.y >= -19.0f) {
		cameraPos.y -= 0.1f;
	}

	if (cameraPos.y < -19.0f) {
		cameraPos.y += 0.1f;
	}
	
	counter++;

	if (counter == 500) {
		std::cout << "x: " << cameraPos.x << std::endl;
		std::cout << "y: " << cameraPos.y << std::endl;
		std::cout << "z: " << cameraPos.z << std::endl;
		std::cout << "----------- " << std::endl;

		counter = 0;
	}

	glm::vec4 lightP = glm::make_vec4(lightPosition);

	glm::mat4 lightM = glm::mat4(1.0f);
	lightM = glm::rotate(lightM, (float)glfwGetTime() * 0.3f, glm::vec3(0.0f, 1.0f, 0.0f));
	lightP = lightM * lightP;
	memcpy(lightPosPtr, &lightP, 16 * sizeof(float));

	
	GLfloat scale[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	memcpy(modelMatrixPtr, scale, 16 * sizeof(GLfloat));
	
	
	GLfloat test[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	memcpy(boxModelMatrixPtr, test, 16 * sizeof(GLfloat));
	

	glUseProgram(programName);



	// Activate the vertex array
	glBindVertexArray(vertexArrayName);
	
	
	
	// Bind buffers to GLSL uniform indices
	glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM0, vertexBufferNames[GLOBAL_MATRICES]);
	//glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM0, vertexBufferNames[GLOBAL_MATRICES]);
	glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM1, vertexBufferNames[MODEL_MATRIX]);
	glBindBufferBase(GL_UNIFORM_BUFFER, LIGHT, vertexBufferNames[LIGHT_PROPERTIES]);
	glBindBufferBase(GL_UNIFORM_BUFFER, MATERIAL, vertexBufferNames[MATERIAL_PROPERTIES]);
	glBindBufferBase(GL_UNIFORM_BUFFER, CAMERA, vertexBufferNames[CAMERA_PROPERTIES]);
	//BIND TO GLSL
	glBindBufferBase(GL_UNIFORM_BUFFER, DYNAMICLIGHT, vertexBufferNames[DYNAMIC_LIGHT]);
	


	// Draw første gang
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	

	glUseProgram(0);

	
	glUseProgram(renderProgram);
	

	// ACtivate neste vertex
	glBindVertexArray(boxVertexArray);
	glBindTexture(GL_TEXTURE_2D, textureName);




	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

	

	// Disable
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	
}

void drawFBOScene(glm::mat4 view) {

	//glBindFrameBuffer(GL_FRAMEBUFFER, frameBuffer);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//glBindBuffer(GL_FRAMEBUFFER, frameBuffer);
	// Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//DETTA Æ DÆ EINASTE SOM UTGJØR EIN ENDRING

	// TEST
	
	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, (float)glfwGetTime() * 0.3f, glm::vec3(0.0f, -1.0f, 0.0f));
	memcpy(viewMatrixPtr, &view[0][0], 16 * sizeof(GLfloat));
	

	glUseProgram(programName);

	// Activate the vertex array
	glBindVertexArray(vertexArrayName);


	// Draw første gang
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);


	glUseProgram(0);


	glUseProgram(renderProgram);


	// ACtivate neste vertex
	glBindVertexArray(boxVertexArray);
	glBindTexture(GL_TEXTURE_2D, textureName);


	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);


	// Disable
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

}


void handleButtons(GLFWwindow *window) {

	float speed = 0.01f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += speed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= speed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
}

void handleMouse(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void resizeGL(int width, int height) {

	// Prevent division by zero
	if (height == 0)
		height = 1;

	// Change the projection matrix
	glm::mat4 proj = glm::perspective(3.14f / 2.0f, (float)width / height, 0.1f, 100.0f);
	memcpy(projectionMatrixPtr, &proj[0][0], 16 * sizeof(GLfloat));

	// Set the OpenGL viewport
	glViewport(0, 0, width, height);

}

/*
 * Error callback function for GLFW
 */
static void glfwErrorCallback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

/*
 * Input event callback function for GLFW
 */
static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

/*
 * Window size changed callback function for GLFW
 */
void glfwWindowSizeCallback(GLFWwindow* window, int width, int height) {

	resizeGL(width, height);

}

/*
 * Program entry function
 */
int main(void) {

	// Set error callback
	glfwSetErrorCallback(glfwErrorCallback);

	// Initialize GLFW
	if (!glfwInit()) {
		printf("Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	// Specify minimum OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	// Create window
	GLFWwindow* window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Minimal", NULL, NULL);
	if (!window) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	// Set input key event callback
	glfwSetKeyCallback(window, glfwKeyCallback);

	// Set window resize callback
	glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);

	// Make the context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize GLEW\n");
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Make GLFW swap buffers directly 
	glfwSwapInterval(0);

	// Initialize OpenGL
	if (!initGL()) {
		printf("Failed to initialize OpenGL\n");
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Initialize OpenGL view
	resizeGL(DEFAULT_WIDTH, DEFAULT_HEIGHT);

	//Nytt!
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, handleMouse);

	// Run a loop until the window is closed
	while (!glfwWindowShouldClose(window)) {

		//BIND FRAMEBUFFER FØRST
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glViewport(0, 0, 1024, 768);

		//Draw in FBO
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		view = glm::lookAt(glm::vec3(2.0f, -18.0f, -18.0f), cameraPos, cameraUp);
		//drawGLScene(view);
		drawFBOScene(view);

		//FENCING???
		//glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

		glFinish();

		//FJERN FØR E KJØM TE SWAP BUFFER
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, 1024, 768);

		//Draw IRL
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		drawGLScene(view);

		// Fencing?=???
		glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

		// ACtivate buttons!
		handleButtons(window);

		// Swap buffers
		glfwSwapBuffers(window);

		// Poll fow input events
		glfwPollEvents();

	}

	// Shutdown GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	// Exit
	exit(EXIT_SUCCESS);

}
