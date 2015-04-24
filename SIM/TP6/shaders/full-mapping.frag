#version 330
#define PI 3.1415926535897932384626433832795

in  vec3 normalView;
in  vec3 tangentView;
in  vec3 eyeView;
in  vec2 uvcoord;

out vec4 bufferColor;

uniform vec3      light;
uniform sampler2D colormap0;
uniform sampler2D colormap1;
uniform sampler2D colormap2;
uniform sampler2D colormapNormal;
uniform sampler2D colormapEnv;

vec2 convVec3ToVec2(vec3 vec) {
  float u = (atan(vec.x, vec.z) + PI) / 2*PI;
  float v = (acos(-vec.y)) / PI;

  vec2 vecRes = vec2(u, v);
  return vecRes;
}

void main() {
  float et = 10.0; // exponent for the Phong lobe 
  
  // normalized vectors needed for shading 
  vec3 n = normalize(normalView);
  vec3 e = normalize(eyeView);
  vec3 l = normalize(light);
  vec3 t = normalize(tangentView);
  vec3 b = cross(n,t);
  
  mat3 tbn = mat3(t, b, n);

  vec3 norme = texture(colormapNormal,uvcoord).xyz*2-1;
  n = norme * tbn;
  
  vec2 machin = convVec3ToVec2(n);

  // diffuse and specular components
  float diff = max(dot(l,n),0.0);
  float spec = pow(max(dot(reflect(l,n),e),0.0),et);

  // final diffuse and specular colors 
  vec4 diffColor = diff * texture(colormap0,machin)*2;
  vec4 specColor = spec * texture(colormap1,machin);

  // final color 
  bufferColor = (diffColor + specColor)*texture(colormap2,uvcoord);
}
