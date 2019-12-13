#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <math.h>


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
#define BOX2_VERTICIES 11
#define NUM_BUFFERS 12


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
	-19.0f, 20.0f, -5.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-19.0f, -20.0f, -5.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-19.0f, -20.0f, 5.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-19.0f, 20.0f, 5.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
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
	-5.0f, -10.0f, -19.0f, 0.0f, 1.0f,
	-5.0f, -20.0f, -19.0f, 0.0f, 0.0f, 
	5.0f, -20.0f, -19.0f, 1.0f, 0.0f,
	5.0f, -10.0f, -19.0f, 1.0f, 1.0f, 
};

GLfloat box2[] = {
	19.0f, -10.0f, 5.0f, 0.0f, 1.0f,
	19.0f, -20.0f, 5.0f, 0.0f, 0.0f,
	19.0f, -20.0f, -5.0f, 1.0f, 0.0f,
	19.0f, -10.0f, -5.0f, 1.0f, 1.0f,
};


GLushort boxindices[]{
	//Front
	0, 1, 2, 2, 3, 0,
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
GLuint box2VertexArray;

// Texture

GLuint frameBuffer;
GLuint renderProgram;
GLuint renderBufferObject;

// HOLDER PÅ ALLE BUFFERE, CAPS ØVERST.
GLuint vertexBufferNames[12];

GLuint textureName;


//Verden nr 2??

GLuint framebuffer2;
GLuint renderBufferObject2;
GLuint textureName2;



GLint width, height, numChannels;

//Camera variables 
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Portal1 and Portal2 position
glm::vec3 portalOnePosition = glm::vec3(0.0f, -16.5f, -18.5f);
glm::vec3 portalTwoPosition = glm::vec3(18.0f, -16.5f, -0.5f);

//Check for portal distance
glm::vec3 playerPortal1Direction;
glm::vec3 playerPortal2Direction;

//Save individual position
float cameraPortal1X;
float cameraPortal1Y;
float cameraPortal1Z;

float cameraPortal2X;
float cameraPortal2Y;
float cameraPortal2Z;


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
	glCreateBuffers(12, vertexBufferNames);

	//NAMED BUFFER STORAGE.
	glNamedBufferStorage(vertexBufferNames[BOX_VERTICIES], 5 * 4 * 2 *  sizeof(GLfloat), box, 0);
	glNamedBufferStorage(vertexBufferNames[BOX2_VERTICIES], 5 * 4 * 2 *  sizeof(GLfloat), box2, 0);
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


	glCreateVertexArrays(1, &box2VertexArray);



	// Associate attributes with binding points
	glVertexArrayAttribBinding(vertexArrayName, POSITION, STREAM0);
	glVertexArrayAttribBinding(vertexArrayName, COLOR, STREAM0);
	glVertexArrayAttribBinding(vertexArrayName, NORMAL, STREAM0);

	
	glVertexArrayAttribBinding(boxVertexArray, POSITION, STREAM0);
	glVertexArrayAttribBinding(boxVertexArray, UV, STREAM0);
	
	glVertexArrayAttribBinding(box2VertexArray, POSITION, STREAM0);
	glVertexArrayAttribBinding(box2VertexArray, UV, STREAM0);


	// Specify attribute format
	glVertexArrayAttribFormat(vertexArrayName, POSITION, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(vertexArrayName, COLOR, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT));
	glVertexArrayAttribFormat(vertexArrayName, NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT));
	
	glVertexArrayAttribFormat(boxVertexArray, POSITION, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(boxVertexArray, UV, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT));
	
	glVertexArrayAttribFormat(box2VertexArray, POSITION, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(box2VertexArray, UV, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT));

	// Enable the attributes
	glEnableVertexArrayAttrib(vertexArrayName, POSITION);
	glEnableVertexArrayAttrib(vertexArrayName, COLOR);
	glEnableVertexArrayAttrib(vertexArrayName, NORMAL);
	
	glEnableVertexArrayAttrib(boxVertexArray, POSITION);
	glEnableVertexArrayAttrib(boxVertexArray, UV);

	glEnableVertexArrayAttrib(box2VertexArray, POSITION);
	glEnableVertexArrayAttrib(box2VertexArray, UV);
	
	// Bind the indices to the vertex array
	glVertexArrayElementBuffer(vertexArrayName, vertexBufferNames[INDICES]);
	
	glVertexArrayElementBuffer(boxVertexArray, vertexBufferNames[BOX_INDICES]);
	glVertexArrayElementBuffer(box2VertexArray, vertexBufferNames[BOX_INDICES]);

	// Bind the vertex buffer to the vertex array
	glVertexArrayVertexBuffer(vertexArrayName, STREAM0, vertexBufferNames[VERTICES], 0, 9 * sizeof(GLfloat));

	glVertexArrayVertexBuffer(boxVertexArray, STREAM0, vertexBufferNames[BOX_VERTICIES], 0, 5 * sizeof(GLfloat));
	glVertexArrayVertexBuffer(box2VertexArray, STREAM0, vertexBufferNames[BOX2_VERTICIES], 0, 5 * sizeof(GLfloat));

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
	//_-----------------------------------------------------------------------------------------------------------------------------
	//_-----------------------------------------------------------------------------------------------------------------------------
	//_------------------------------------------------VERDEN 2-------------------------------------------------------
	//_-----------------------------------------------------------------------------------------------------------------------------
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	glGenFramebuffers(1, &framebuffer2);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer2);

	// The texture we're going to render to
	glGenTextures(1, &textureName2);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureName2);

	// tomt bilde
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// CUSTOMIZE SJØL
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	// "render buffer object"
	glGenRenderbuffers(1, &renderBufferObject2);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject2);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject2);

	// COLOR ATTACHMENT
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureName2, 0);

	// draw buffaaaaaahs
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	// stjælt sjækk
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;


	//_-----------------------------------------------------------------------------------------------------------------------------
	//_-----------------------------------------------------------------------------------------------------------------------------
	//_------------------------------------------------VERDEN 2-------------------------------------------------------
	//_-----------------------------------------------------------------------------------------------------------------------------

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

void drawGLScene(glm::mat4 view, glm::mat4 proj) {

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

	memcpy(projectionMatrixPtr, &proj[0][0], 16 * sizeof(GLfloat));

	//memcpy(fboViewMatrixPtr, &view[0][0], 16 * sizeof(GLfloat));


	//PsuedoGravity
	if (cameraPos.y >= -16.5f) {
		cameraPos.y -= 0.1f;
	}

	if (cameraPos.y < -16.5f) {
		cameraPos.y += 0.1f;
	}
	/*
	counter++;

	if (counter == 500) {
		std::cout << "x: " << cameraPos.x << std::endl;
		std::cout << "y: " << cameraPos.y << std::endl;
		std::cout << "z: " << cameraPos.z << std::endl;
		std::cout << "----------- " << std::endl;

		counter = 0;
	}
	*/
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
	

	glBindTexture(GL_TEXTURE_2D, textureName2);
	//Draw før texture biten.
	glBindVertexArray(box2VertexArray);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// ACtivate neste vertex
	glBindVertexArray(boxVertexArray);
	glBindTexture(GL_TEXTURE_2D, textureName);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);




	// Disable
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	
}

void drawFBOScene(glm::mat4 view, glm::mat4 proj) {

	//glBindFrameBuffer(GL_FRAMEBUFFER, frameBuffer);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//glBindBuffer(GL_FRAMEBUFFER, frameBuffer);
	// Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//DETTA Æ DÆ EINASTE SOM UTGJØR EIN ENDRING

	// TEST
	/* NON-SOLUTION, DÆ Æ EIN ANNA MÅTE Å GJERRA DÆ PÅ
	if (playerPortal1Distance <= 3.0f) {
		glm::vec3 closeViewHack = glm::vec3(cameraPos.x, 0.0f, cameraPos.z);
		view = glm::lookAt(portalOnePosition, closeViewHack, cameraUp);
	}
	*/

	//REVERSER MODELL!!!!
	glm::mat4 model = glm::mat4(1.0f);

	//SCALE DEN TE MOTSATT, BLI RIKTIG OGMOGMOGMOGMOMGOMGOMGOMOG!!!!!!!
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	//TRENG IKKKJE SCALING HER, DETTA Æ WORKING SOM INTENDED

	memcpy(modelMatrixPtr, &model[0][0], 16 * sizeof(GLfloat));


	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, (float)glfwGetTime() * 0.3f, glm::vec3(0.0f, -1.0f, 0.0f));
	memcpy(viewMatrixPtr, &view[0][0], 16 * sizeof(GLfloat));
	

	//Custom proj
	memcpy(projectionMatrixPtr, &proj[0][0], 16 * sizeof(GLfloat));

	glUseProgram(programName);

	// Activate the vertex array
	glBindVertexArray(vertexArrayName);


	// Draw første gang
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

	
	

	glUseProgram(0);


	glUseProgram(renderProgram);
	

	//Draw utta texture
	glBindTexture(GL_TEXTURE_2D, textureName2);
	glBindVertexArray(box2VertexArray);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);


	// ACtivate neste vertex
	glBindVertexArray(boxVertexArray);
	glBindTexture(GL_TEXTURE_2D, textureName);


	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);


	// Disable
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

}

void drawFBO2Scene(glm::mat4 view, glm::mat4 proj) {

	//glBindFrameBuffer(GL_FRAMEBUFFER, frameBuffer);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//glBindBuffer(GL_FRAMEBUFFER, frameBuffer);
	// Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//DETTA Æ DÆ EINASTE SOM UTGJØR EIN ENDRING

	// calc distance
	
	
	
	//playerPortal1Distance = (float)sqrt(cameraPortalX * cameraPortalX + cameraPortalY * cameraPortalY + cameraPortalZ * cameraPortalZ);

	counter++;

	//Keep track of distance between portal 1 and player. Why tho?
	/*
	playerPortal1Distance = 
		glm::vec3(
		sqrt(cameraPortalX * cameraPortalX), 
		sqrt(cameraPortalY * cameraPortalY), 
		sqrt(cameraPortalZ * cameraPortalZ));

	*/
	
	//REVERSER MODELL!!!!
	glm::mat4 model = glm::mat4(1.0f);
	
	//Invert model
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	memcpy(modelMatrixPtr, &model[0][0], 16 * sizeof(GLfloat));
	


	//Custom proj
	memcpy(projectionMatrixPtr, &proj[0][0], 16 * sizeof(GLfloat));

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


	//Draw utta texture
	glBindTexture(GL_TEXTURE_2D, textureName2);
	glBindVertexArray(box2VertexArray);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);


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

bool checkForCollisions(glm::vec3 player, glm::vec3 portal) {
	if (player == portal) {
		std::cout << "COLLISION" << std::endl;
		return true;
	}

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
		
		/*
		TIL FRAMTIDSBJØRNAR:

		DU MÅ HA EIN VEKTOR FRA PORTAL 1 TE PLAYER, Å BRUKE DEN I "CENTER" DELEN AV LOOKAT
		PROBLEMET Æ ATT NÅR DU SER INN I VERDEN 1, SÅ SER DU INN I FORHOLD TE PORTAL 1, DERFOR RØRE DEN SE
		IKKJE NÅR DU FLØTTE DE FRAM Å TEBAKE. SÅ DETTA Æ BASICALLY IKKJE NO PROBLEM, BÆRRE TA EIN DISTANSE
		VEKTOR MELLOM PLAYER OG PORTAL, OG ROTER DEN MÆ 90 GRADER. 

		*/
		

		//Hacky method for only using X and Z coordinates.
		playerPortal1Direction = portalOnePosition - cameraPos;
		playerPortal1Direction.y = -16.5f;

		playerPortal2Direction = portalTwoPosition - cameraPos;
		playerPortal2Direction.y = -16.5f;


		//To handle all negative Z values multiply with -1. 
		playerPortal1Direction.z = playerPortal1Direction.z * (-1.0f);
		
		
		
		if (counter == 500) {
			/*
			std::cout << "1: distanceX: " << playerPortal1Direction.x << std::endl;
			std::cout << "1: distanceY: " << playerPortal1Direction.y << std::endl;
			std::cout << "1: distanceZ: " << playerPortal1Direction.z << std::endl;
			std::cout << "----------- " << std::endl;
			
			
			std::cout << "2: distanceX: " << playerPortal2Direction.x << std::endl;
			std::cout << "2: distanceY: " << playerPortal2Direction.y << std::endl;
			std::cout << "2: distanceZ: " << playerPortal2Direction.z << std::endl;
			std::cout << "----------- " << std::endl;
			

			/*
			std::cout << "portal x: " << portalOnePosition.x << std::endl;
			std::cout << "portal y: " << portalOnePosition.y << std::endl;
			std::cout << "portal z: " << portalOnePosition.z << std::endl;
			*/
			std::cout << "camera x: " << cameraPos.x << std::endl;
			std::cout << "camera y: " << cameraPos.y << std::endl;
			std::cout << "camera z: " << cameraPos.z << std::endl;
			std::cout << "----------- " << std::endl;
			


			counter = 0;
		}
		
		//Check for camera VS portal collision
		//checkForCollisions(cameraPos, portalOnePosition);




		/*
		glm::vec4 x = glm::make_vec4(portalOnePosition);

		//glm::mat4 destView = view * x;
		glm::mat4 rotation(1.0f);
		rotation = glm::rotate(rotation, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		
		glm::vec3 rotated = x * rotation;
		*/

		//playerPortal1Direction er en retningsvektor mellom player og portal1. Så her vet vi retning.

		//DETTA KINDA FUNKA?
		
		//Rotate 90 degrees since rendered world is perpendicular to portal
		glm::mat4 rotated(1.0f);
		rotated = glm::rotate(rotated, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		
		glm::vec4 convertportal1 = glm::make_vec4(playerPortal1Direction);

		glm::vec3 playerPortalRotation = convertportal1 * rotated;


		//BIND FRAMEBUFFER FØRST
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glViewport(0, 0, 1024, 768);

	
		view = glm::lookAt(portalTwoPosition, playerPortalRotation, cameraUp);


		float zdistance = portalOnePosition.z - cameraPos.z;
		float squaredDistance = sqrt(zdistance * zdistance);
		float zresult = (squaredDistance / 10) / 2;
		
		if (zresult < 1.0f)
			zresult = 2.58 - zresult;
		else
			zresult = 1.57;
			
		

		glm::mat4 fbo1proj = glm::perspective(zresult, 1024.0f / 768.0f, 0.1f, 100.0f);

		drawFBOScene(view, fbo1proj);

		//FENCING???
		//glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

		glFinish();

		//VERDEN 2???????????????

		//glm::mat4 rotated2(1.0f);
		//rotated2 = glm::rotate(rotated2, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));



		//Uses previously created rotation, same reason as other portal
		glm::vec4 convertPortal2 = glm::make_vec4(playerPortal2Direction);
		glm::vec3 playerPortal2Rotation = convertPortal2 * rotated;


		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer2);
		glViewport(0, 0, 1024, 768);

		//Draw in FBO
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		// " Riktig veig"
		//glm::mat4 rotateView(1.0f);
		//rotateView = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
		//glm::vec3 newPos = glm::mat3(rotateView) * cameraPos;
		view = glm::lookAt(portalOnePosition, playerPortal2Rotation, cameraUp);
		//view = glm::lookAt(glm::vec3(2.0f, -18.0f, -19.0f), cameraPos, cameraUp);
		//drawGLScene(view);


		float xdistance = portalTwoPosition.x - cameraPos.x;
		float xsquaredDistance = sqrt(xdistance * xdistance);
		float xresult = (xsquaredDistance / 10) / 2;
		

		if (xresult < 1.0f)
			xresult = 2.58 - xresult;
		else
			xresult = 1.57;

		std::cout << "xresult is: " << xresult << std::endl;

		glm::mat4 fbo2proj = glm::perspective(xresult, 1024.0f / 768.0f, 0.1f, 100.0f);
		

		drawFBO2Scene(view, fbo2proj);

		glFinish();


		//TELEPORT
		/*
		bool portal1enable = true;
		bool portal2enable = true;
		
		//1 til 2
		if (cameraPos.x > -5.0f && cameraPos.x < 5.0f && cameraPos.z <= -18.5f && portal1enable == true) {
			//cameraPos = portalTwoPosition;
			

			
			glm::mat4 camRotate(1.0f);
			camRotate = glm::rotate(camRotate, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			cameraFront = glm::mat3(camRotate) * cameraFront;
			


			//cameraFront = -playerPortal1Direction + cameraFront;

			cameraPos = portalTwoPosition;
			portal2enable = false;
			
		}

		
		//(cameraPos.z > -5.0f && cameraPos.z < 5.0f
		
		//2 til 1
		if (cameraPos.z > -5.0f && cameraPos.z < 5.0f && cameraPos.x >= 18.5f && portal2enable == true) {
			//std::cout << "INNAFOR" << std::endl;
			cameraPos = portalOnePosition;

			glm::mat4 camRotate(1.0f);
			camRotate = glm::rotate(camRotate, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			cameraFront = glm::mat3(camRotate) * cameraFront;

			portal1enable = false;

		}
		
		*/



		//FJERN FØR E KJØM TE SWAP BUFFER
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, 1024, 768);

		//Draw IRL
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glm::mat4 regproj =  glm::perspective(3.14f / 2.0f, 1024.0f / 768.0f, 0.1f, 100.0f);

		drawGLScene(view, regproj);

		glFinish();

		// Fencing?=???
		//glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

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
