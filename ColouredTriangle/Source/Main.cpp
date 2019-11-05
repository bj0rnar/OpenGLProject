#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

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
	-5.0f, 5.0f, -10.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-5.0f, -5.0f, -10.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	5.0f, -5.0f, -10.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	5.0f, 5.0f, -10.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

GLushort boxindices[]{
	// Front
	0, 1, 2, 2, 3, 0

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

//Camera variables 
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Mouse callback
void handleMouse(GLFWwindow* window, double xpos, double ypos);
float lastX = DEFAULT_WIDTH / 2.0f;
float lastY = DEFAULT_HEIGHT / 2.0f;
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;

int counter = 0;



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

	//EGEN BUFFER
	//glCreateBuffers(1, boxVertexBufferName);

	//NAMED BUFFER STORAGE.
	glNamedBufferStorage(vertexBufferNames[BOX_VERTICIES], 4 * 9 * sizeof(GLfloat), box, 0);
	glNamedBufferStorage(vertexBufferNames[BOX_INDICES],  6 * sizeof(GLshort), boxindices, 0);

	// Allocate storage for the vertex array buffers
	glNamedBufferStorage(vertexBufferNames[VERTICES], 6 * 4 * 9 * sizeof(GLfloat), vertices, 0);

	// Allocate storage for the triangle indices
	glNamedBufferStorage(vertexBufferNames[INDICES], 3 * 2 * 6 * sizeof(GLshort), indices, 0);

	//Allocate storage buffer for light position NEW 
	//glNamedBufferStorage(vertexBufferNames[DYNAMIC_LIGHT], 4 * sizeof(GLfloat), lightPosition, 0);

	// Allocate storage for the transformation matrices and retrieve their addresses
	glNamedBufferStorage(vertexBufferNames[GLOBAL_MATRICES], 16 * sizeof(GLfloat) * 2, NULL, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	glNamedBufferStorage(vertexBufferNames[MODEL_MATRIX], 16 * sizeof(GLfloat), NULL, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	
	glNamedBufferStorage(vertexBufferNames[BOX_MODEL], 16 * sizeof(GLfloat), NULL, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

	//GJØR LYS DYNAMISK.
	//glNamedBufferStorage(vertexBufferNames[DYNAMIC_LIGHT], 4 * sizeof(GLfloat), NULL, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

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
	glCreateVertexArrays(1, &boxVertexArray);


	// Associate attributes with binding points
	glVertexArrayAttribBinding(vertexArrayName, POSITION, STREAM0);
	glVertexArrayAttribBinding(vertexArrayName, COLOR, STREAM0);
	glVertexArrayAttribBinding(vertexArrayName, NORMAL, STREAM0);

	
	glVertexArrayAttribBinding(boxVertexArray, POSITION, STREAM0);
	glVertexArrayAttribBinding(boxVertexArray, COLOR, STREAM0);
	glVertexArrayAttribBinding(boxVertexArray, NORMAL, STREAM0);
	

	// Specify attribute format
	glVertexArrayAttribFormat(vertexArrayName, POSITION, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(vertexArrayName, COLOR, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT));
	glVertexArrayAttribFormat(vertexArrayName, NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT));
	
	glVertexArrayAttribFormat(boxVertexArray, POSITION, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(boxVertexArray, COLOR, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT));
	glVertexArrayAttribFormat(boxVertexArray, NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT));
	
	// Enable the attributes
	glEnableVertexArrayAttrib(vertexArrayName, POSITION);
	glEnableVertexArrayAttrib(vertexArrayName, COLOR);
	glEnableVertexArrayAttrib(vertexArrayName, NORMAL);
	
	glEnableVertexArrayAttrib(boxVertexArray, POSITION);
	glEnableVertexArrayAttrib(boxVertexArray, COLOR);
	glEnableVertexArrayAttrib(boxVertexArray, NORMAL);
	
	// Bind the indices to the vertex array
	glVertexArrayElementBuffer(vertexArrayName, vertexBufferNames[INDICES]);
	
	glVertexArrayElementBuffer(boxVertexArray, vertexBufferNames[BOX_INDICES]);

	// Bind the vertex buffer to the vertex array
	glVertexArrayVertexBuffer(vertexArrayName, STREAM0, vertexBufferNames[VERTICES], 0, 9 * sizeof(GLfloat));

	glVertexArrayVertexBuffer(boxVertexArray, STREAM0, vertexBufferNames[BOX_VERTICIES], 0, 9 * sizeof(GLfloat));

	//------------------------------RENDER TO TEXTURE ----------------------------------------------------------

	

	/*\
	//Mekk framebuffer
	glGenFramebuffers(1, &frameBuffer);
	//BIND FRAMEBUFFER
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	//LAG TEXTURE, KOBLE TEXTURE TE FRAMEBUFFER
	glGenTextures(1, &textureTest);
	//Bind
	glBindTexture(GL_TEXTURE_2D, textureTest);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureTest, 0);


	// RENDER BUFFER OBJECT
	glGenRenderbuffers(1, &renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1024, 768);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//Attach framebuffer & renderbufferobject
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);



	/*
	// Tom texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureTest, 0);
	*/

	/*

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	 
	*/

	/*
	// mekk framebuffer
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// generate texture
	unsigned int texColorBuffer;
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);


	//Render buffer object
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1024, 768);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);


	// DETTA KJØRE, MEN ALT BLI SVART.
	/*
	glGenTextures(1, &texture_map);
	glBindTexture(GL_TEXTURE_2D, texture_map);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 768, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Build the texture that will serve as the depth attachment for the framebuffer.
	GLuint depth_texture;
	glGenTextures(1, &depth_texture);
	glBindTexture(GL_TEXTURE_2D, depth_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 768, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build the framebuffer.
	GLuint framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_map, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		// Error

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	*/

	/*
	GLuint frameBuffer = 0;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	GLuint renderToTexture;
	glGenTextures(GL_TEXTURE_2D, &renderToTexture);

	glBindTexture(GL_TEXTURE_2D, renderToTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderToTexture, 0);


	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, 1024, 768);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;
		*/
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
	//glEnable(GL_DEPTH_TEST);


	// PROGRAM 2 -----------------------------------------------

	renderProgram = glCreateProgram();
	glAttachShader(renderProgram, renderVertex);
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

void drawGLScene() {
	/*
	//STEP 1
	glBindBuffer(GL_FRAMEBUFFER, frameBuffer);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	// Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	*/

	// Set the view matrix
	glm::mat4 view = glm::mat4(1.0f);

	//LookAt ny metode
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	memcpy(viewMatrixPtr, &view[0][0], 16 * sizeof(GLfloat));


	

	//LIght

	/*
	if (cameraPos.y >= -19.0f) {
		cameraPos.y -= 0.1f;
	}

	if (cameraPos.y < -19.0f) {
		cameraPos.y += 0.1f;
	}
	
	//Red warp to green
	if (cameraPos.z <= -19.0f) {
		cameraPos.z = 0.0f;
		cameraPos.x = 19.0f;

		glm::mat4 rotateCamera = glm::mat4(1.0f);
		rotateCamera = glm::rotate(rotateCamera, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		cameraFront = glm::mat3(rotateCamera) * cameraFront;
	}


	//Black warp to top
	if (cameraPos.z >= 19.0f) {
		cameraPos.x = 0.0f;
		cameraPos.z = 0.0f;
		cameraPos.y = 100.0f;

		/*
		glm::mat4 turnCameraDown = glm::mat4(1.0f);
		turnCameraDown = glm::rotate(turnCameraDown, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		
		cameraFront = glm::mat3(turnCameraDown) * cameraFront;
		*/
	//}

	

	/*
	if (cameraPos.z >= 19.0f) {
		cameraPos.z = -19.0f;
	}
	/*
	if (cameraPos.x <= -19.0f) {
		cameraPos.x = 19.0f;
	}

	if (cameraPos.x >= 19.0f) {
		cameraPos.x = -19.0f;
	}
	
	//glBufferData (something something, GL_STATIC_DRAW) versjon 3.3
	kan heller bruke glNamedBufferStorage(vertexBufferNames[MODEL_BOX]) nåvernende versjon.


	*/
	
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

	//memcpy(lightPosPtr, &light[0][0], 4 * sizeof(GLfloat));


	//Model treng ikkje rotetere, kommentere ut detta.
	// Set the model matrix
	
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
	
	
	/*
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime() * 0.3f, glm::vec3(0.0f, -1.0f, 0.0f));
	memcpy(modelMatrixPtr, &model[0][0], 16 * sizeof(GLfloat));
	*/

	//lightProperties[0] = 2.0f;
	//cameraProperties[0] = 4.0f;

	//lightProperties[0] = 1.0f;



	//ALL THIS STUFF.
	/**/

	/*
	float lightX = 2.0f * sin(glfwGetTime());
	float lightY = -0.3f;
	float lightZ = 1.5f * cos(glfwGetTime());

	glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);

	memcpy(lightPosPtr, &lightPos, 4 * sizeof(GLfloat));
	*/




	//Not working
	//glm::mat4 light = glm::mat4(1.0);
	//light = glm::rotate(light, (float)glfwGetTime() * 2.0f, glm::vec3(5.0f, 5.0f, 5.0f));
	//memcpy(lightPosPtr, &light[0][0], 4 * sizeof(GLfloat));

	//glUniform3f(LIGHT, lightX, lightY, lightZ);



	/*


	glm::vec4 lightPos(LIGHT);

	lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
	lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;


	glm::mat4 lightRotate(1.0f);
	lightRotate = glm::rotate(lightRotate, lightPos.x, glm::vec3(1.0f, 0.0f, 0.0f));
	lightRotate = glm::rotate(lightRotate, lightPos.y, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec4 rotatedLightPosition = lightRotate * lightPos;

	glUniform3f(LIGHT, rotatedLightPosition.x, rotatedLightPosition.y, rotatedLightPosition.z);
	*/

	//Sett 1:1 scale, denna ken stå statisk.


	/*
	GLfloat scale[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	memcpy(modelMatrixPtr, scale, 16 * sizeof(GLfloat));
	*/
	// Activate the program

	/*
	glBindBuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	*/

	glUseProgram(programName);


	//glBindBuffer(GL_FRAMEBUFFER, frameBuffer);


	// Activate the vertex array
	glBindVertexArray(vertexArrayName);
	

	
	// Bind buffers to GLSL uniform indices
	glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM0, vertexBufferNames[GLOBAL_MATRICES]);
	glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM1, vertexBufferNames[MODEL_MATRIX]);
	glBindBufferBase(GL_UNIFORM_BUFFER, LIGHT, vertexBufferNames[LIGHT_PROPERTIES]);
	glBindBufferBase(GL_UNIFORM_BUFFER, MATERIAL, vertexBufferNames[MATERIAL_PROPERTIES]);
	glBindBufferBase(GL_UNIFORM_BUFFER, CAMERA, vertexBufferNames[CAMERA_PROPERTIES]);
	//BIND TO GLSL
	glBindBufferBase(GL_UNIFORM_BUFFER, DYNAMICLIGHT, vertexBufferNames[DYNAMIC_LIGHT]);
	
	// Draw første gang
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	
	//glBindBuffer(GL_FRAMEBUFFER, 0);

	glUseProgram(0);

	glUseProgram(renderProgram);


	// ACtivate neste vertex
	glBindVertexArray(boxVertexArray);
	//glDisable(GL_DEPTH_TEST);
	
	
	
	//glBindTexture(GL_TEXTURE_2D, textureTest);

	// FRAMEBUFFAH
	//glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//glViewport(0, 0, 512, 512);

	//Bind GLSL for shader 2 
	glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM5, vertexBufferNames[GLOBAL_MATRICES]);
	glBindBufferBase(GL_UNIFORM_BUFFER, TRANSFORM6, vertexBufferNames[BOX_MODEL]);

	// Tegn greia
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);


	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Disable
	glUseProgram(0);
	glBindVertexArray(0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);

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

	/*	NOTAT TE KAMERA OBLIG

		glm::vec3 cameraPosition;
		glm::vec3 cameraForward;
		glm::vec3 cameraLeft;

		i main funksjonen:
		glfwSetKeyCallback <-- håndterer input
		keyevents æ bæd å laggy
		keycallback æ insta.
		key input > text input

		noe typ detta for tastatur:

		int movingForward = 0

		if(key == GLFW_KEY_W && action == GLFW_PRESS) {
			movingForward = 1
		}

		for å gjøre selve utregninga i render:
		Framover:
		cameraPos += cameraForward * speed * timeElapsed

		noe typ detta for mus:

		sjekk raw mouse motion ell cursor position
		bruker en av de for å hente ut X og Y coordinater til mus.

		OBS: trenger ikke noe ny kode på GPU siden, alt av input av keyboard/mus skjer på CPU siden.

		For kameragreier, google linear interpolation.

		Quaternion.

	*/



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

		// Draw OpenGL screne
		drawGLScene();

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
