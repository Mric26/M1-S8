#version 330

// the layout number allows to make the relations with arrays
// it avoids using glGetAttribLocation*
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 modelviewMatrix; // modelview matrix (constant for all the vertices)
uniform mat4 projMatrix; // projection matrix (constant for all the vertices)

// output variables that will be interpolated during rasterization (equivalent to varying)
out vec4 fragmentColor;

void main() {
  vec3 p = position;
  p.z = 0.4*position.z;
  gl_Position = projMatrix*modelviewMatrix*vec4(p,1.0);
  fragmentColor = vec4(color,1.0);
}
