//--------------------------------------------------
// Author: Grace Choe
// Date:
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

      for (string shader : shadersVec) {
         renderer.loadShader(shader, "../shaders/" + shader + ".vs", "../shaders/" + shader + ".fs");
      }

      // renderer.loadShader("normals", "../shaders/normals.vs", "../shaders/normals.fs");
      // renderer.loadShader("phong-vertex", "../shaders/phong-vertex.vs", "../shaders/phong-vertex.fs");
      // renderer.loadShader("phong-pixel", "../shaders/phong-pixel.vs", "../shaders/phong-pixel.fs");

      // shadersVec.push_back("normals");
      // shadersVec.push_back("phong-vertex");
      // shadersVec.push_back("phong-pixel");
   }

   float mouseX() const {
      double xpos, ypos;
      glfwGetCursorPos(_window, &xpos, &ypos);
      return static_cast<float>(xpos);
   }

   float mouseY() const {
      double xpos, ypos;
      glfwGetCursorPos(_window, &xpos, &ypos);
      return static_cast<float>(height() - ypos);
   }

   // I added camPos()
   vec3 camLocation(float rad, float azi, float elev) {
      camPos.x = rad * cos(azi) * cos(elev);
      camPos.y = rad * sin(elev);
      camPos.z = rad * sin(azi) * cos(elev);

      return camPos;
   }

   // Controls the camera's backward and forward direction, Z
   // vec3 backwardDir() const {
   //    vec2 mousePos = mousePosition();



   // }

   // Controls the camera's up and down direction, Y
   void upDir(int x, int dx) {
      mousePos = mousePosition();
      float windHeight = height();

      azimuth = (mousePos.x / windHeight) * 360;
      std::cout << azimuth << std::endl;
   }

   // Controls the camera's right and left direction, X
   void rightDir(int y, int dy) {
      mousePos = mousePosition();
      float windWidth = width();

      elevation = ((mousePos.y / windWidth) * 180) - 90;

   }

   void mouseMotion(int x, int y, int dx, int dy) override {
      if (mouseClicked) { //mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
         upDir(x, dx);
         rightDir(y, dy);
         camLocation(radius, azimuth, elevation);
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

   // void keyUp(int key, int mods) override {
   // }

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
      } else if ((key == GLFW_MOD_SHIFT) && (mouseClicked == true)) {
         scale = {scale.x + 10, scale.y + 10, scale.z + 10};
      }
   }

   void draw() override {
      renderer.beginShader(shadersVec[currShaderLoc]); // activates shader with given name
   
      float aspect = ((float)width()) / height(); 
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
      
      // eyePos = renderer.camPos(10, 20, 0);
      eyePos = camLocation(radius, azimuth, elevation);
      // eyePos = {10, 20, 0};
      vec3 camZ = camPos - lookPos;
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
      struct GLFWwindow* _window = 0;
      float alpha = 0.3; // alpha for specular var
      bool mouseClicked = false;
      vec3 scale;
      vec2 mousePos;

   protected:
      PLYMesh mesh, tempMesh;
      vec3 eyePos = vec3(10, 0, 0);
      vec3 lookPos = vec3(0, 0, 0);
      vec3 up = vec3(0, 1, 0);
      vec3 camPos = vec3(10, 0, 0);
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