#version 460

///////////////////////////////// Data Structs /////////////////////////////////

// Must match C++ Side
struct Quadrant             // 8 Byte Alignment for std140
{
  vec2 vPositions[4];       // (2 x 4) x 4 = 32B

  vec2 vTexCoords[4];       // (2 x 4) x 4 = 32B
  
  uint vTexIndex;           // 1 x 4 = 4B
  uint unused;              // 1 x 4 = 4B
};

////////////////////////////////////// ? ///////////////////////////////////////

uniform vec2 resExtent;

///////////////////////////////////// UBOs /////////////////////////////////////

layout(std430, binding=0) buffer QuadBuffer
{
	Quadrant quads[];
};

/////////////////////////////////// Outputs ////////////////////////////////////

layout(location = 0) out vec2 texCoord;
layout(location = 1) out uint texIndex;

////////////////////////////////////////////////////////////////////////////////

void main()
{
  /**************************************************************************/

  // Calculate Indexes
  uint vIndex = gl_VertexID % 6;
  uint quadIndex = gl_VertexID / 6;
  uint posIndex = vIndex > 2 ? (vIndex - 1) % 4 : vIndex;

  // Calculate Vertex Position
  Quadrant quad = quads[quadIndex];
  vec2 pos = quad.vPositions[posIndex];
  // Normalize Position from Window Resolution to -1:1
  // pos *= vec2(widthScaleDown, heightScaleDown);

  // Set gl_Position
  gl_Position = vec4(pos, 0.0, 1.0);

  // Set Outputs
  texCoord = quad.vTexCoords[posIndex];
  texIndex = quad.vTexIndex;
}