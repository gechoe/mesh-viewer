//--------------------------------------------------
// Author: Grace Choe
// Date: 2/28/2023
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include "plymesh.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace glm;

namespace agl {

   PLYMesh::PLYMesh(const std::string& filename) {
      load(filename);
   }

   PLYMesh::PLYMesh() {
   }

   void PLYMesh::init() {
      assert(_positions.size() != 0);
      initBuffers(&_faces, &_positions, &_normals);
   }

   PLYMesh::~PLYMesh() {
   }

   void PLYMesh::splitString(std::string line, std::string splitVar = " ") {
      words_vec.clear();
      int begin = 0;
      int end = line.find(splitVar);
      while (end != -1) {
        //cout << line.substr(begin, end - begin) << endl;
        words_vec.push_back(line.substr(begin, end - begin));
        begin = end + splitVar.size();
        end = line.find(splitVar, begin);
      }
      
      words_vec.push_back(line.substr(begin, end - begin));
   }

   long PLYMesh::stoNumber(std::string number) {
      long i;
      i = 0;
      

      for (char c : number) {
         if (c >= '0' && c <= '9') {
            i = i * 10 + (c - '0');
            c++;
         }
      }
     
      return i;
   }

   bool PLYMesh::load(const std::string& filename) {
      _positions.clear();
      _faces.clear();
      
      if (_positions.size() != 0) {
         std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
         return false;
      }

      // todo: your code here
      std::string fileText;

      std::cout << filename << std::endl;
      std::ifstream FileReader("../models/" + filename);

      if (FileReader.is_open()) {
         getline(FileReader, fileText);

         if (fileText.compare("ply") != 0) {
            std::cout << "WARNING: Ply file is incorrect." << std::endl;
            return false;
         }

         getline(FileReader, fileText); // Skips "format ascii 1.0" line
         getline(FileReader, fileText); // Skips comment line
      
         getline(FileReader, fileText); // Reads "element vertex [number]"
         splitString(fileText); // Splits string by spaces
         // Gets only the number from the element vertex line
         string vAmount = words_vec[words_vec.size() - 1];
         int vertexAmount = stoNumber(vAmount);

         getline(FileReader, fileText);
         splitString(fileText);
         
         while (words_vec[0].compare("element") != 0) {
            getline(FileReader, fileText);
            splitString(fileText);
         }

         splitString(fileText); // Splits string by spaces
         // Gets only the number from the element face line
         int faceAmount = stoNumber(words_vec[words_vec.size() - 1]);

         // Skips "property list uint8 int32 vertex_indices" line
         getline(FileReader, fileText);

         getline(FileReader, fileText); // Skips "end_header" line
         words_vec.clear();

         for (int i = 0; i < vertexAmount; i++) {
            getline(FileReader, fileText); // Reads vertex information
            splitString(fileText); // Splits string by spaces
            // float x = 
            _positions.push_back(stof(words_vec[0]));
            // float y = 
            _positions.push_back(stof(words_vec[1]));
            // float z = 
            _positions.push_back(stof(words_vec[2]));
            // vertexPos vert = {x, y, z};

            // vertices_vec.push_back(vert);
            words_vec.clear();
         }

         for (int j = 0; j < faceAmount; j++) {
            getline(FileReader, fileText); // Reads face information
            splitString(fileText); // Splits string by spaces
            // int vertOne = 
            _faces.push_back(stoi(words_vec[1]));
            // int vertTwo = 
            _faces.push_back(stoi(words_vec[2]));
            // int vertThree = 
            _faces.push_back(stoi(words_vec[3]));
            // facePos face = {vertOne, vertTwo, vertThree};

            // faces_vec.push_back(face);
            words_vec.clear();
         }

         FileReader.close();
      } else {
         std::cout << "WARNING: Ply file cannot be opened." << std::endl;
      }

      return false;
      // if (_positions.size() != 0) {
      //    std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
      //    return false;
      // }
      // // todo: your code here
      // std::string fileText;

      // ifstream FileReader("cube.ply");

      // getline(FileReader, fileText);
      // getline(FileReader, fileText);

      // std::cout << fileText << std::endl;

      // if (fileText.compare("ply") != 0) {
      //    std::cout << "WARNING: Ply file is incorrect." << std::endl;
      //    return false;
      // }

      // getline(FileReader, fileText); // Skips "format ascii 1.0" line
   
      // getline(FileReader, fileText); // Reads "element vertex [number]"
      // splitString(fileText); // Splits string by spaces
      // // Gets only the number from the element vertex line
      // int vertexAmount = stoi(words_vec[words_vec.size() - 1]);

      // getline(FileReader, fileText); // Skips "property float32 x" line
      // getline(FileReader, fileText); // Skips "property float32 y" line
      // getline(FileReader, fileText); // Skips "property float32 z" line

      // getline(FileReader, fileText); // Reads "element face [number]"
      // splitString(fileText); // Splits string by spaces
      // // Gets only the number from the element face line
      // int faceAmount = stoi(words_vec[words_vec.size() - 1]);

      // // Skips "property list uint8 int32 vertex_indices" line
      // getline(FileReader, fileText);

      // getline(FileReader, fileText); // Skips "end_header" line
      // words_vec.clear();

      // for (int i = 0; i < vertexAmount; i++) {
      //    getline(FileReader, fileText); // Reads vertex information
      //    splitString(fileText); // Splits string by spaces
      //    // float x = 
      //    _positions.push_back(stof(words_vec[0]));
      //    // float y = 
      //    _positions.push_back(stof(words_vec[1]));
      //    // float z = 
      //    _positions.push_back(stof(words_vec[2]));
      //    // vertexPos vert = {x, y, z};

      //    // vertices_vec.push_back(vert);
      //    words_vec.clear();
      // }

      // for (int j = 0; j < faceAmount; j++) {
      //    getline(FileReader, fileText); // Reads face information
      //    splitString(fileText); // Splits string by spaces
      //    // int vertOne = 
      //    _faces.push_back(stoi(words_vec[1]));
      //    // int vertTwo = 
      //    _faces.push_back(stoi(words_vec[2]));
      //    // int vertThree = 
      //    _faces.push_back(stoi(words_vec[3]));
      //    // facePos face = {vertOne, vertTwo, vertThree};

      //    // faces_vec.push_back(face);
      //    words_vec.clear();
      // }

      // FileReader.close();

      // return false;
   }

   glm::vec3 PLYMesh::minBounds() const {
      return glm::vec3(0);
   }

   glm::vec3 PLYMesh::maxBounds() const {
      return glm::vec3(0);
   }

   int PLYMesh::numVertices() const {
      return _positions.size();
   }

   int PLYMesh::numTriangles() const {
      return _faces.size();
   }

   const std::vector<GLfloat>& PLYMesh::positions() const {
      return _positions;
   }

   const std::vector<GLfloat>& PLYMesh::normals() const {
      return _normals;
   }

   const std::vector<GLuint>& PLYMesh::indices() const {
      return _faces;
   }
}
