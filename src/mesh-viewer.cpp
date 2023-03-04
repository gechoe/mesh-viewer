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

   void setup() {
      filenames_vec = GetFilenamesInDir("../models", "ply");
      curr_file = filenames_vec[0];
      // mesh.load("../models/cube.ply");
   }

   void mouseMotion(int x, int y, int dx, int dy) override {
   }

   void mouseDown(int button, int mods) override {
   }

   void mouseUp(int button, int mods) override {
   }

   void scroll(float dx, float dy) override {
   }

   void keyUp(int key, int mods) override {
   }

   // keyDown()
   // Changes brush size, brush transparency, and clears screen if certain keys
   // are pressed
   void keyDown(int key, int mods) override {
      if (key == GLFW_KEY_N) { // 'N' or 'n' key
         curr_file_loc++;
         if (curr_file_loc == filenames_vec.size()) {
            curr_file_loc = 0;
         }
      } else if (key == GLFW_KEY_P) {
         curr_file_loc--;
         if (curr_file_loc == -1) {
            curr_file_loc = filenames_vec.size() - 1;
         }
      }
   }

   void draw() {
      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
      renderer.lookAt(eyePos, lookPos, up);

      renderer.translate(vec3(0, 0, 0));
      renderer.rotate(vec3(0, 0, 0));
      renderer.scale(vec3(1, 1, 1));
      //renderer.mesh(mesh); // this line draws the mesh, affected by the given transforms
      // renderer.teapot(); // you can try built-in meshes for testing

      // float aspect = ((float)width()) / height();
      // renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

      // renderer.rotate(vec3(0,0,0));
      // renderer.scale(vec3(1,1,1));
      // renderer.translate(vec3(0,0,0));
      // renderer.mesh(mesh);
      mesh = PLYMesh(curr_file);
      renderer.mesh(mesh);
      // renderer.cube(); // for debugging!
      
      // for (int i = 0; i < filenames_vec.size(); i++) {
      //    if (filenames_vec[i].compare(curr_file) == 0) {
      //       curr_file_loc = i;
      //    }
      // }
   }

   private:
      std::vector<std::string> filenames_vec; // filenames of all meshes
      int curr_file_loc = 0;
      std::string curr_file = "cube.ply";

   protected:
      PLYMesh mesh;
      vec3 eyePos = vec3(10, 0, 0);
      vec3 lookPos = vec3(0, 0, 0);
      vec3 up = vec3(0, 1, 0);
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}

