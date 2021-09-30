#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Centers the cone on the origin
	float centerZ = a_fHeight / 2;

	// GENERATE CIRCULAR BASE
	GenerateCircle(a_fRadius, -centerZ, a_nSubdivisions);

	// Convert the number of subdivisions into a radian equal to 2*PI / n, where n = number of subdivisions
	float radians = (360.0f / a_nSubdivisions) * (PI / 180.0f);

	// GENERATE THE CONICAL FACE
	// Create 1 triangle for each subdivision, resulting in a shape with n sides, where n = number of subdivisions
	for (int i = 1; i <= a_nSubdivisions; i++) {
		AddTri(vector3(0.0f, 0.0f, centerZ),
			vector3(a_fRadius * cosf(radians * (i - 1)), a_fRadius * sinf(radians * (i - 1)), -centerZ),
			vector3(a_fRadius * cosf(radians * i), a_fRadius * sinf(radians * i), -centerZ));
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Centers the cylinder on the origin
	float centerZ = a_fHeight / 2;

	// GENERATE THE CIRCULAR FACES
	GenerateCircle(a_fRadius, -centerZ, a_nSubdivisions);
	GenerateCircle(a_fRadius, centerZ, a_nSubdivisions);

	// Convert the number of subdivisions into a radian equal to 2*PI / n, where n = number of subdivisions
	float radians = (360.0f / a_nSubdivisions) * (PI / 180.0f);

	// GENERATE THE CYLINDRICAL FACE
	// Create 1 quad for each subdivision, resulting in a shape with n sides, where n = number of subdivisions
	for (int i = 1; i <= a_nSubdivisions; i++) {
		// Create the front of the circle
		AddQuad(vector3(a_fRadius * cosf(radians * (i - 1)), a_fRadius * sinf(radians * (i - 1)), -centerZ),
			vector3(a_fRadius * cosf(radians * i), a_fRadius * sinf(radians * i), -centerZ),
			vector3(a_fRadius * cosf(radians * (i - 1)), a_fRadius * sinf(radians * (i - 1)), centerZ),
			vector3(a_fRadius * cosf(radians * i), a_fRadius * sinf(radians * i), centerZ));
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Centers the tube on the origin
	float centerZ = a_fHeight / 2;

	// Convert the number of subdivisions into a radian equal to 2*PI / n, where n = number of subdivisions
	float radians = (360.0f / a_nSubdivisions) * (PI / 180.0f);

	// GENERATE THE TUBE
	for (int i = 1; i <= a_nSubdivisions; i++) {
		// Create the outer side
		AddQuad(vector3(a_fOuterRadius * cosf(radians * (i - 1)), a_fOuterRadius * sinf(radians * (i - 1)), -centerZ),
			vector3(a_fOuterRadius * cosf(radians * i), a_fOuterRadius * sinf(radians * i), -centerZ),
			vector3(a_fOuterRadius * cosf(radians * (i - 1)), a_fOuterRadius * sinf(radians * (i - 1)), centerZ),
			vector3(a_fOuterRadius * cosf(radians * i), a_fOuterRadius * sinf(radians * i), centerZ));

		// Create the inner side
		AddQuad(vector3(a_fInnerRadius * cosf(radians * (i - 1)), a_fInnerRadius * sinf(radians * (i - 1)), -centerZ),
			vector3(a_fInnerRadius * cosf(radians * (i - 1)), a_fInnerRadius * sinf(radians * (i - 1)), centerZ),
			vector3(a_fInnerRadius * cosf(radians * i), a_fInnerRadius * sinf(radians * i), -centerZ),
			vector3(a_fInnerRadius * cosf(radians * i), a_fInnerRadius * sinf(radians * i), centerZ));

		// Create the top circle
		AddQuad(vector3(a_fOuterRadius * cosf(radians * (i - 1)), a_fOuterRadius * sinf(radians * (i - 1)), centerZ),
			vector3(a_fOuterRadius * cosf(radians * i), a_fOuterRadius * sinf(radians * i), centerZ),
			vector3(a_fInnerRadius * cosf(radians * (i - 1)), a_fInnerRadius * sinf(radians * (i - 1)), centerZ),
			vector3(a_fInnerRadius * cosf(radians * i), a_fInnerRadius * sinf(radians * i), centerZ));

		// Create the bottom circle
		AddQuad(vector3(a_fOuterRadius * cosf(radians * (i - 1)), a_fOuterRadius * sinf(radians * (i - 1)), -centerZ),
			vector3(a_fInnerRadius * cosf(radians * (i - 1)), a_fInnerRadius * sinf(radians * (i - 1)), -centerZ),
			vector3(a_fOuterRadius * cosf(radians * i), a_fOuterRadius * sinf(radians * i), -centerZ),
			vector3(a_fInnerRadius * cosf(radians * i), a_fInnerRadius * sinf(radians * i), -centerZ));
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	// The amount of radians between each point in a segment
	float radiansCylinderBase = (360.0f / a_nSubdivisionsA) * (PI / 180.0f);

	// The amount of radians between each segment
	float radiansTotalCylinders = (360.0f / a_nSubdivisionsB) * (PI / 180.0f);

	// The radius of the tube
	float tubeRadius = (a_fOuterRadius - a_fInnerRadius) / 2;

	// The distance from the origin to the center of the tube
	float holeToTubeCenterRadius = a_fInnerRadius + tubeRadius;

	// GENERATE THE TORUS
	for (int currentCylinder = 1; currentCylinder <= a_nSubdivisionsB; currentCylinder++) {
		for (int currentFace = 1; currentFace <= a_nSubdivisionsA; currentFace++) {
			// Represents each of the four corners for each quad that makes up the torus
			float x1 = (holeToTubeCenterRadius + (tubeRadius * cos(radiansCylinderBase * (currentFace - 1)))) * (cos(radiansTotalCylinders * (currentCylinder - 1)));
			float y1 = (holeToTubeCenterRadius + (tubeRadius * cos(radiansCylinderBase * (currentFace - 1)))) * (sin(radiansTotalCylinders * (currentCylinder - 1)));
			float z1 = tubeRadius * sin(radiansCylinderBase * (currentFace - 1));

			float x2 = (holeToTubeCenterRadius + (tubeRadius * cos(radiansCylinderBase * currentFace))) * (cos(radiansTotalCylinders * (currentCylinder - 1)));
			float y2 = (holeToTubeCenterRadius + (tubeRadius * cos(radiansCylinderBase * currentFace))) * (sin(radiansTotalCylinders * (currentCylinder - 1)));
			float z2 = tubeRadius * sin(radiansCylinderBase * (currentFace));

			float x3 = (holeToTubeCenterRadius + (tubeRadius * cos(radiansCylinderBase * (currentFace - 1)))) * (cos(radiansTotalCylinders * currentCylinder));
			float y3 = (holeToTubeCenterRadius + (tubeRadius * cos(radiansCylinderBase * (currentFace - 1)))) * (sin(radiansTotalCylinders * currentCylinder));
			float z3 = tubeRadius * sin(radiansCylinderBase * (currentFace - 1));

			float x4 = (holeToTubeCenterRadius + (tubeRadius * cos(radiansCylinderBase * currentFace))) * (cos(radiansTotalCylinders * currentCylinder));
			float y4 = (holeToTubeCenterRadius + (tubeRadius * cos(radiansCylinderBase * currentFace))) * (sin(radiansTotalCylinders * currentCylinder));
			float z4 = tubeRadius * sin(radiansCylinderBase * (currentFace));

			AddQuad(vector3(x1, y1, z1),
				vector3(x3, y3, z3),
				vector3(x2, y2, z2),
				vector3(x4, y4, z4));
		}
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 12)
		a_nSubdivisions = 12;

	Release();
	Init();

	// The x, y, and z coordinates in terms of spherical coordinates
	// x = r * sin(phi) * cos(theta)
	// y = r * sin(phi) * sin(theta)
	// z = r * cos(phi)

	// Theta will wrap around the entire sphere to determine which vertical section will be generated
	float thetaStep = glm::radians(360.0f / a_nSubdivisions);

	// Phi will run from the north pole to the south pole of the sphere to generate each vertical section as theta wraps around the circumference of the sphere
	float phiStep = glm::radians(180.0f / a_nSubdivisions);

	for (int i = 0; i < a_nSubdivisions; i++) {

		for (int j = 0; j < a_nSubdivisions; j++) {
			// BOTTOM LEFT
			float x1 = a_fRadius * glm::sin(phiStep * i) * glm::cos(thetaStep * j);
			float y1 = a_fRadius * glm::sin(phiStep * i) * glm::sin(thetaStep * j);
			float z1 = a_fRadius * glm::cos(phiStep * i);

			// BOTTOM RIGHT
			float x2 = a_fRadius * glm::sin(phiStep * i) * glm::cos(thetaStep * (j + 1));
			float y2 = a_fRadius * glm::sin(phiStep * i) * glm::sin(thetaStep * (j + 1));
			float z2 = a_fRadius * glm::cos(phiStep * i);

			// TOP LEFT
			float x3 = a_fRadius * glm::sin(phiStep * (i + 1)) * glm::cos(thetaStep * j);
			float y3 = a_fRadius * glm::sin(phiStep * (i + 1)) * glm::sin(thetaStep * j);
			float z3 = a_fRadius * glm::cos(phiStep * (i + 1));

			// TOP RIGHT
			float x4 = a_fRadius * glm::sin(phiStep * (i + 1)) * glm::cos(thetaStep * (j + 1));
			float y4 = a_fRadius * glm::sin(phiStep * (i + 1)) * glm::sin(thetaStep * (j + 1));
			float z4 = a_fRadius * glm::cos(phiStep * (i + 1));

			AddQuad(vector3(x1, y1, z1),
				vector3(x3, y3, z3),
				vector3(x2, y2, z2),
				vector3(x4, y4, z4));
		}
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::GenerateCircle(float a_fRadius, float a_fHeight, int a_nSubdivisions)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	/*
		Calculate a_nSubdivisions number of points around a center point in a radial manner
		then call the AddTri function to generate a_nSubdivision number of faces
	*/

	// Convert the number of subdivisions into a radian equal to 2*PI / n, where n = number of subdivisions
	float radians = (360.0f / a_nSubdivisions) * (PI / 180.0f);

	// Create 1 triangle for each subdivision, resulting in a shape with n sides, where n = number of subdivisions
	for (int i = 1; i <= a_nSubdivisions; i++) {
		// Create the front of the circle
		AddTri(vector3(0.0f, 0.0f, a_fHeight),
			vector3(a_fRadius * cosf(radians * (i - 1)), a_fRadius * sinf(radians * (i - 1)), a_fHeight),
			vector3(a_fRadius * cosf(radians * i), a_fRadius * sinf(radians * i), a_fHeight));

		// Create the back of the circle
		AddTri(vector3(0.0f, 0.0f, a_fHeight),
			vector3(a_fRadius * cosf(radians * i), a_fRadius * sinf(radians * i), a_fHeight),
			vector3(a_fRadius * cosf(radians * (i - 1)), a_fRadius * sinf(radians * (i - 1)), a_fHeight));
	}
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh & other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh & other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh & other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader);

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));

	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}