#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

void AddRegionToMatrix(int tl_x, int tl_y, int width, int height, Mat& matrix) {
  int curr_val;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      curr_val = matrix.at<char>(tl_y+j,tl_x+i);
      matrix.at<char>(tl_y+j,tl_x+i) = curr_val + 1;
      // std::cout << "incrementing pixel at " << tl_x+i << " " << tl_y+j << std::endl;
    }
  }
}

int CountOverlap(Mat& matrix) {
  int acc = 0;
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      if (matrix.at<char>(i,j) > 1) {
        // std::cout << "examining coord: " << i << " " << j << std::endl;
        acc++;
      }
    }
  }
  return acc;
}

bool NoOverlap(int tl_x, int tl_y, int width, int height, Mat& matrix) {
  int curr_val;
  bool res = true;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      curr_val = matrix.at<char>(tl_y+j,tl_x+i);
      if (curr_val > 1) {
        res = false;
      }
    }
  }
  return res;
}

int main(int argc, char const *argv[]) {
  Mat visualization_matrix(1000,1000,CV_8UC1);  //1000x1000 8-bit 1-channel matrix
  vector<vector<int>> list;
  ifstream inFile;
  inFile.open("/home/samtitle/Desktop/adventofcode/SamAdventCodeChallenge/Day_3/input.txt");
  if (!inFile) {
    std::cout << "Error couldn't open file." << std::endl;
  } else {
    string id, at, corner, area;
    int corner_x, corner_y;
    int area_width, area_height;
    while (inFile >> id >> at >> corner >> area) {
      //Extract ID
      std::cout << id << at << corner << area << std::endl;
      id.erase(0,1);
      std::cout << "Id: " << id << std::endl;

      //Extract Corner
      char* to_split = new char[corner.size()+1];
      strcpy(to_split,corner.c_str());
      char* token = strtok(to_split, ",:");
      corner_x = strtol(token, &token, 10);
      token = strtok(NULL,",:");
      corner_y = strtol(token, &token, 10);
      std::cout << "Corner: " << corner_x << " " << corner_y << std::endl;

      //Extract Area
      to_split = new char[area.size()+1];
      strcpy(to_split,area.c_str());
      token = strtok(to_split, "x");
      area_width = strtol(token, &token, 10);
      token = strtok(NULL,",:");
      area_height = strtol(token, &token, 10);
      std::cout << "Area: " << area_width << " x " << area_height << std::endl;
      vector<int> entry;
      entry.push_back(stoi(id));
      entry.push_back(corner_x);
      entry.push_back(corner_y);
      entry.push_back(area_width);
      entry.push_back(area_height);
      list.push_back(entry);
      AddRegionToMatrix(corner_x, corner_y, area_width, area_height, visualization_matrix);
    }
    inFile.close();
    std::cout << "Finished reading input..." << std::endl;
    std::cout << "# of Regions in Overlap : " << CountOverlap(visualization_matrix) << std::endl;
    for (int i = 0; i < list.size(); i++) {
      if (NoOverlap(list[i][1],list[i][2],list[i][3],list[i][4],visualization_matrix)) {
        std::cout << "No overlap ID: " << list[i][0] << std::endl;
      }
    }
    double min, max;
    minMaxLoc(visualization_matrix, &min, &max);
    normalize(visualization_matrix, visualization_matrix, 0, 255, NORM_MINMAX);
    imshow("result", visualization_matrix);
    waitKey(0);

  }
  return 0;
}
