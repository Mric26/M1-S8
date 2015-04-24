#version 330

in  vec3 normalView;
in  vec3 eyeView;
in  vec2 coordVec;

out vec4 bufferColor;

uniform vec3 light;

uniform sampler2D text;
uniform sampler2D text2;

void main() {
  // Phong parameters (colors and roughness)
  const vec3 ambient  = vec3(0.3,0.3,0.2);
  const vec3 diffuse  = vec3(0.3,0.5,0.8);
  const vec3 specular = vec3(0.8,0.2,0.2);
  const float et = 50.0;

  // normal / view and light directions (in camera space)
  vec3 n = normalize(normalView);
  vec3 e = normalize(eyeView);
  vec3 l = normalize(light);

  // diffuse and specular components of the phong shading model
  float diff = max(dot(l,n),0.0);
  float spec = pow(max(dot(reflect(l,n),e),0.0),et);

  // final color 
  vec3 color = ambient + diff*diffuse + spec*specular;
  bufferColor = texture(text,coordVec);
}
