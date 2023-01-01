#version 460

///////////////////////////////// Data Structs /////////////////////////////////

// Must match C++ Side
struct Quadrant             // 8 Byte Alignment (std430)
{
  vec2 vPositions[4];       // (2 x 4) x 4 = 32B

  vec2 vTexCoords[4];       // (2 x 4) x 4 = 32B
  
  uint vTexIndex;           // 1 x 4 = 4B
  uint unused;              // 1 x 4 = 4B
};

///////////////////////////////////// UBOs /////////////////////////////////////

layout(std430, binding=0) readonly buffer QuadBuffer
{
	Quadrant quads[];
};

//////////////////////////////////// Inputs ////////////////////////////////////

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

/////////////////////////////////// Outputs ////////////////////////////////////

out vec4 vertexColor;

////////////////////////////////////////////////////////////////////////////////

void main ()
{
  gl_Position = vec4(aPos, 1.0);
  vertexColor = vec4(aColor, 1.0);
}
