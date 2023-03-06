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
      // curr_file = "cube.ply";//filenames_vec[0];
      // mesh.load("../models/cube.ply");
      int num = 0;

      for (string file : filenamesVec) {
         tempMesh = PLYMesh("../models/" + file);
         meshesVec.push_back(tempMesh);
         // std::cout << mesh.numVertices() << std::endl;
      }

      // vector<float> nums;
      // nums.push_back(14.145);
      // nums.push_back(3.14159);

      // std::cout << std::max(nums[0], nums[1]) << std::endl;

      // for (string file : filenamesVec) {
      //    std::cout << file << std::endl;
      // }
   }

   void mouseMotion(int x, int y, int dx, int dy) override {
   }

   void mouseDown(int button, int mods) override {
   }

   void mouseUp(int button, int mods) override {
   }

   void scroll(float dx, float dy) override {
   }

   // void keyUp(int key, int mods) override {
   // }

   // keyDown()
   // Changes brush size, brush transparency, and clears screen if certain keys
   // are pressed
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
      }
   }

   // void changeMesh() {
   //    mesh.load(currFile);
   //    // std::cout << mesh.numVertices() << std::endl;
   //    renderer.mesh(mesh);
   // }

   void draw() override {
      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
      renderer.lookAt(eyePos, lookPos, up);
      // renderer.scale(vec3(1, 1, 1));
      renderer.translate(vec3(0, 0, 0));
      renderer.rotate(vec3(0, 0, 0));

      renderer.scale(vec3(0.5, 0.5, 0.5));
      //renderer.mesh(mesh); // this line draws the mesh, affected by the given transforms
      // renderer.teapot(); // you can try built-in meshes for testing

      // float aspect = ((float)width()) / height();
      // renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

      // renderer.rotate(vec3(0,0,0));
      // renderer.scale(vec3(1,1,1));
      // renderer.translate(vec3(0,0,0));
      // renderer.mesh(mesh);
      // std::cout << curr_file << std::endl;
      // changeMesh();
      // mesh.load(currFile);
      mesh = meshesVec[currFileLoc];

      vec3 min = mesh.minBounds();
      vec3 max = mesh.maxBounds();

      // renderer.scale(vec3(1, 1, 1));
      //    renderer.translate(vec3(0, 0, 0));
      //    renderer.rotate(vec3(0, 0, 0));

      // if ((max.x - min.x) > width() || (max.y - min.y) > height()) {
      //    std::cout << width() << std::endl;
      //    renderer.scale(vec3(0.1, 0.1, 0.1));
      //    renderer.translate(vec3((max.x - min.x) / 2, (max.y - min.y) / 2, (max.z - min.z) / 2));
      //    renderer.rotate(vec3(0, 0, 0));
      // } else {
      //    renderer.scale(vec3(1, 1, 1));
      //    renderer.translate(vec3(0, 0, 0));
      //    renderer.rotate(vec3(0, 0, 0));
      // }

      // std::cout << mesh.numVertices() << std::endl;
      // mesh.load(curr_file);
      // // std::cout << mesh.numVertices() << std::endl;
      renderer.mesh(mesh);
      // renderer.cube(); // for debugging!
      
      // for (int i = 0; i < filenames_vec.size(); i++) {
      //    if (filenames_vec[i].compare(curr_file) == 0) {
      //       curr_file_loc = i;
      //    }
      // }
   }

   private:
      vector<string> filenamesVec; // filenames of all meshes
      vector<PLYMesh> meshesVec;
      int currFileLoc = 20;
      string currFile = "cube.ply";

   protected:
      PLYMesh mesh, tempMesh;
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