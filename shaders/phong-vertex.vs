#version 400

layout (location = 0) in vec3 vPos; // the p to use in the specular equation
layout (location = 1) in vec3 vNormals;
layout (location = 2) in vec2 vTextureCoords;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;

out vec3 phongReflec;

void main()
{
   vec3 lightColor; // light color
   vec3 constColor; // constant color
   vec3 ambient;

   vec4 lightPos; // light position
   vec4 eyePos; // eye position
   vec3 normLight; // normalized light, direction of light
   vec3 normal;
   float dotNormsLN; // dot product of the light normal and normal
   vec3 matColor; // material color
   vec3 diffuse;

   vec3 normVert; // normalized Vertex
   vec3 currP; // currecnt vertex
   vec3 normReflect; // normalized reflection
   float dotNormsVR; // dot product of the vertex normal and the reflection normal
   float alpha = 0.8;
   vec3 specular;

   lightColor = vec3(0.5, 0.5, 0.5);
   // constColor = vec3(0.52, 0.62, 1);
   constColor = vec3(0.4, 0.6, 1);
   ambient = vec3(constColor * lightColor);

   lightPos = vec4(15, 15, 15, 1);
   eyePos = ModelViewMatrix * vec4(vPos, 1.0);
   normLight = normalize(vec3(lightPos - eyePos));
   normal = normalize(vec3(NormalMatrix * vNormals));
   dotNormsLN = dot(normLight, normal);
   matColor = vec3(0.2, 0.2, 1);
   diffuse = vec3(max(dotNormsLN, 0) * lightColor);
   //vec3(constColor * dotNormsLN * lightColor * matColor);

   normVert = normalize(vec3(vec3(eyePos) - vPos));
   normReflect = 2 * dotNormsLN * normal - normLight;
   dotNormsVR = dot(normVert, normReflect);
   // specular = constColor * lightColor * pow(float(normReflect), alpha);
   int constant = 32; // size of highlight, the bigger the more concentrated the highlight is
   specular = vec3(pow(max(dotNormsVR, 0), constant)); 
   //(constColor * dotNormsLN) + (constColor * pow(normReflect, normal));

   phongReflec = ambient + diffuse + specular;

   gl_Position = MVP * vec4(vPos, 1.0);
}