//--------------------------------------------------
// Author: Grace Choe
// Date: 3/1/2023
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"
#include "plymesh.h"
#include "osutils.h"

using namespace std;
using namespace glm;
using namespace agl;

class MeshViewer : public Window {
public:
   MeshViewer() : Window() {
   }

   void setup() override {
      meshFNVec = GetFilenamesInDir("../models", "ply");

      for (string meshFile : meshFNVec) {
         tempMesh = PLYMesh("../models/" + meshFile);
         meshesVec.push_back(tempMesh);
      }

      shadersVec.push_back("normals");
      shadersVec.push_back("phong-vertex");
      shadersVec.push_back("phong-pixel");
      shadersVec.push_back("toon");
      shadersVec.push_back("jellofy");
      shadersVec.push_back("glass");
      shadersVec.push_back("vroom");
      shadersVec.push_back("wiggle");
      shadersVec.push_back("color-change");

      for (string shader : shadersVec) {
         renderer.loadShader(shader, "../shaders/" + shader + ".vs", "../shaders/" + shader + ".fs");
      }

      texturesVec.push_back("angelBear");
      texturesVec.push_back("diff-widths-color");
      texturesVec.push_back("fill-shapes-colorful");
      texturesVec.push_back("squishy-tv-colors");
      texturesVec.push_back("squishy");
      texturesVec.push_back("triangle-randomized");

      for (string texture : texturesVec) {
         renderer.loadTexture(texture, "../textures/" + texture + ".png", slot);
         slot++;
      }
   }

   // I added camPos()
   vec3 camPos(float rad, float azi, float elev) {
      vec3 camPOV;
      camPOV.x = rad * cos(azi) * cos(elev);
      camPOV.y = rad * sin(elev);
      camPOV.z = rad * sin(azi) * cos(elev);

      return camPOV;
   }

   // Controls the camera's backward and forward direction, Z
   // vec3 backwardDir() const {
   //    vec2 mousePos = mousePosition();

   // }

   // Controls the camera's up and down direction, Y
   void upDir(int x, int dx) {
      float windHeight = height();

      azimuth += dx / 5;
   }

   // Controls the camera's right and left direction, X
   void rightDir(int y, int dy) {
      float windWidth = width();

      elevation += dy / 5;
   }

   void mouseMotion(int x, int y, int dx, int dy) override {
      if (mouseClicked) { //mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
         upDir(x, dx);
         rightDir(y, dy);

         if (azimuth > 360) {
            azimuth = fmod(azimuth, 360);
         } else if (azimuth < 0) {
            azimuth = 360 - fmod(azimuth, 360);
         }

         if (elevation > 90) {
            elevation = -90 + fmod(elevation, 90);
         } else if (elevation < -90) {
            elevation = 90 + fmod(elevation, -90);
         }

         // eyePos = camLocation(radius, azimuth, elevation);
      }
   }

   void mouseDown(int button, int mods) override {
      // button is clicked
      if (button == GLFW_MOUSE_BUTTON_LEFT) {
         mouseClicked = true;
      }
   }

   void mouseUp(int button, int mods) override {
      // button is not clicked
      if (button == GLFW_MOUSE_BUTTON_LEFT) {
         mouseClicked = false;
      }
   }

   void scroll(float dx, float dy) override {
      // Not implemented bc I do not have access to a scrolling mechanic to test
   }

   // keyUp()
   // Changes mesh or shader type or camera view
   void keyUp(int key, int mods) override {
      if ((key == GLFW_KEY_N) || (key == GLFW_KEY_N && key == GLFW_MOD_SHIFT)) { // 'N' or 'n' key
         currMeshLoc++;
         if (currMeshLoc == meshFNVec.size()) {
            currMeshLoc = 0;
         }

         currMesh = meshFNVec[currMeshLoc];
      } else if ((key == GLFW_KEY_P) || (key == GLFW_KEY_P && key == GLFW_MOD_SHIFT)) {
         currMeshLoc--;
         if (currMeshLoc == -1) {
            currMeshLoc = meshFNVec.size() - 1;
         }

         currMesh = meshFNVec[currMeshLoc];
      } else if ((key == GLFW_KEY_S) || (key == GLFW_KEY_S && key == GLFW_MOD_SHIFT)) {
         currShaderLoc++;
         if (currShaderLoc == shadersVec.size()) {
            currShaderLoc = 0;
         }

         if ((shadersVec[currShaderLoc] == "jellofy") || (shadersVec[currShaderLoc] == "glass")) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
            glDisable(GL_CULL_FACE);
         } else {
            glDisable(GL_BLEND);
            glEnable(GL_CULL_FACE);
         }
      } else if ((key == GLFW_KEY_T) || (key == GLFW_KEY_T && key == GLFW_MOD_SHIFT)) {
         currTextureLoc++;
         texturize = false;

         if (currTextureLoc == texturesVec.size()) {
            currTextureLoc = 0;
            texturize = false;
         }
      } else if (key == GLFW_KEY_Z) { // Zooms in
         scaleFactor = scaleFactor + 0.05f;
      } else if (key == GLFW_KEY_X) { // Zooms out
         scaleFactor = scaleFactor - 0.05f;

         if (scaleFactor < 0.1f) {
            scaleFactor = 0.05f;
         }
      }
   }

   void draw() override {
      renderer.beginShader(shadersVec[currShaderLoc]); // activates shader with given name
   
      renderer.setUniform("uTime", elapsedTime());

      float aspect = ((float)width()) / height(); 
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
      
      // eyePos = renderer.camPos(10, 20, 0);
      cameraPos = camPos(radius, azimuth, elevation);
      eyePos = cameraPos;
      // eyePos = {10, 20, 0};
      vec3 d = lookPos - cameraPos;
      vec3 camZ = d - cameraPos - lookPos;
      vec3 camX = cross(vec3(0, 1, 0), camZ);
      vec3 camY = cross(camZ, camX);
      // renderer.lookAt(eyePos, lookPos, up);
      renderer.lookAt(eyePos, lookPos, camY);
      
      mesh = meshesVec[currMeshLoc];
      renderer.setUniform("numTriangles", mesh.numTriangles());
      renderer.rotate(vec3(0, 0, 0));
      
      scale = mesh.scaleVal();

      renderer.scale(scale * scaleFactor);
      renderer.translate(mesh.translateVal());
      
      renderer.mesh(mesh);
      renderer.endShader();
   }

   private:
      vector<string> meshFNVec; // all filenames of meshes
      vector<PLYMesh> meshesVec; // all meshes
      vector<string> shadersVec; // all shaders
      //vector<string> textFNVec; // all filenames of textures
      vector<string> texturesVec; // all textures
      int currMeshLoc = 20;
      int currShaderLoc = 0;
      int currTextureLoc = 0;
      int slot = 1;
      string currMesh = "cube.ply";
      bool mouseClicked = false;
      vec3 scale;
      float scaleFactor = 1;
      bool texturize = false;

   protected:
      PLYMesh mesh, tempMesh;
      vec3 eyePos = vec3(10, 0, 0);
      vec3 lookPos = vec3(0, 0, 0);
      vec3 up = vec3(0, 1, 0);
      vec3 cameraPos = vec3(10, 0, 0);
      float azimuth = 0;
      float elevation = 0;
      float radius = 10;
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}