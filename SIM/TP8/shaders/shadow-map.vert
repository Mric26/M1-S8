#version 330

// input attributes 
layout(location = 0) in vec3 position; 

// input uniforms
uniform mat4 mvpDepthMat;

void main() {
  // *** TODO: update vertex position accoding to the (light space) modelviewprojection matrix  *** 
  gl_Position =  mvpDepthMat * vec4(position,1.0);
}
