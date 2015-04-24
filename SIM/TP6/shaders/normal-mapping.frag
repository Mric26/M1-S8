#version 330

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
  
  // diffuse and specular components
  float diff = max(dot(l,n),0.0);
  float spec = pow(max(dot(reflect(l,n),e),0.0),et);

  // final diffuse and specular colors 
  vec4 diffColor = diff * texture(colormap0,uvcoord)*2;
  vec4 specColor = spec * texture(colormap1,uvcoord);

  // final color 
  bufferColor = (diffColor + specColor)*texture(colormap2,uvcoord);
}
