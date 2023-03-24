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
      filenamesVec = GetFilenamesInDir("../models", "ply");
      int num = 0;

      for (string file : filenamesVec) {
         tempMesh = PLYMesh("../models/" + file);
         meshesVec.push_back(tempMesh);
      }

      shadersVec.push_back("normals");
      shadersVec.push_back("phong-vertex");
      shadersVec.push_back("phong-pixel");
      shadersVec.push_back("toon");
      shadersVec.push_back("jellofy");
      shadersVec.push_back("wiggle");

      for (string shader : shadersVec) {
         renderer.loadShader(shader, "../shaders/" + shader + ".vs", "../shaders/" + shader + ".fs");
      }
   }

   // float mouseX() const {
   //    double xpos, ypos;
   //    glfwGetCursorPos(_window, &xpos, &ypos);
   //    return static_cast<float>(xpos);
   // }

   // float mouseY() const {
   //    double xpos, ypos;
   //    glfwGetCursorPos(_window, &xpos, &ypos);
   //    return static_cast<float>(height() - ypos);
   // }

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
      // mousePos.x = mousePosition();
      float windHeight = height();

      azimuth += dx / 4; //(mousePos.x / windHeight) * 4.8; //(mousePos.x / windHeight) * 360;
      std::cout << azimuth << std::endl;
   }

   // Controls the camera's right and left direction, X
   void rightDir(int y, int dy) {
      // mousePos.y = mousePosition();
      float windWidth = width();

      elevation += (-1 * dy) / 4;//((mousePos.y / windWidth) * 4) - 90;
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

   }

   // keyDown()
   // Changes mesh or shader type
   void keyUp(int key, int mods) override {
      if ((key == GLFW_KEY_N) || (key == GLFW_KEY_N && key == GLFW_MOD_SHIFT)) { // 'N' or 'n' key
         currFileLoc++;
         if (currFileLoc == filenamesVec.size()) {
            currFileLoc = 0;
         }

         currFile = filenamesVec[currFileLoc];
      } else if ((key == GLFW_KEY_P) || (key == GLFW_KEY_P && key == GLFW_MOD_SHIFT)) {
         currFileLoc--;
         if (currFileLoc == -1) {
            currFileLoc = filenamesVec.size() - 1;
         }

         currFile = filenamesVec[currFileLoc];
      } else if ((key == GLFW_KEY_S) || (key == GLFW_KEY_S && key == GLFW_MOD_SHIFT)) {
         currShaderLoc++;
         if (currShaderLoc == shadersVec.size()) {
            currShaderLoc = 0;
         }

         if (shadersVec[currShaderLoc] == "jellofy") {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
            glDisable(GL_CULL_FACE);
         } else {
            glDisable(GL_BLEND);
            glEnable(GL_CULL_FACE);
         }
      } else if ((key == GLFW_MOD_SHIFT) && (mouseClicked == true)) {
         scale = {scale.x + 10, scale.y + 10, scale.z + 10};
      }
   }

   void draw() override {
      renderer.beginShader(shadersVec[currShaderLoc]); // activates shader with given name
   
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
      
      mesh = meshesVec[currFileLoc];
      renderer.rotate(vec3(0, 0, 0));
      
      scale = mesh.scaleVal();

      renderer.scale(scale);
      renderer.translate(mesh.translateVal());
      
      renderer.mesh(mesh);
      renderer.endShader();
   }

   private:
      vector<string> filenamesVec; // all filenames of meshes
      vector<PLYMesh> meshesVec; // all meshes
      vector<string> shadersVec; // all shaders
      int currFileLoc = 20;
      int currShaderLoc = 0;
      string currFile = "cube.ply";
      bool mouseClicked = false;
      vec3 scale;

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