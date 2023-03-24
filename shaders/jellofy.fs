#version 400

in vec4 pEye;
in vec3 normalEye;

out vec4 FragColor;

void main()
{
   vec3 lightColor; // light color
   vec3 constColor; // constant color
   vec3 ambient;

   vec4 lightPos; // light position
   vec4 eyePos = pEye; // eye position
   vec3 normLight; // normalized light, direction of light
   vec3 normal = normalEye;
   float dotNormsLN; // dot product of the light normal and normal
   vec3 matColor; // material color
   vec3 diffuse;

   vec3 normVert; // normalized Vertex
   vec3 currP; // currecnt vertex
   vec3 normReflect; // normalized reflection
   float dotNormsVR; // dot product of the vertex normal and the reflection normal
   float alpha = 0.8;
   vec3 specular;

   lightColor = vec3(0.55, 0.55, 0.55);
   // constColor = vec3(0.52, 0.62, 1);
   constColor = vec3(0.4, 1, 0.4);
   ambient = vec3(constColor * lightColor);

   lightPos = vec4(15, 15, 15, 1);
   normLight = normalize(vec3(lightPos - eyePos));
   dotNormsLN = dot(normLight, normal);
   matColor = vec3(0.2, 1, 0.2);
   diffuse = vec3(max(dotNormsLN, 0) * lightColor); //vec3(constColor * dotNormsLN * lightColor * matColor);

   normVert = normalize(vec3(eyePos));
   normReflect = 2 * dotNormsLN * normal - normLight;
   dotNormsVR = dot(normVert, normReflect);
   // specular = constColor * lightColor * pow(float(normReflect), alpha);
   int constant = 30; // size of highlight, the bigger the more concentrated the highlight is
   specular = vec3(pow(max(dotNormsVR, 0), constant)); 
   //(constColor * dotNormsLN) + (constColor * pow(normReflect, normal));

   vec3 phongReflec = ambient + diffuse + specular;

   FragColor = vec4(phongReflec, 0.4);
}