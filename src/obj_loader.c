#include "obj_loader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Mesh obj_loader_load(const char* file_name) {
  char line[256];
  FILE* file = fopen(file_name, "r");

  size_t vertex_number = 0;
  size_t triangle_number = 0;
  Vertex* vertices = NULL;
  Triangle* triangles = NULL;

  while (fgets(line, 256, file) != NULL)  {
    if (line[0] == 'v' && line[1] == ' ') {
      Vertex vertex;
      sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
      ++vertex_number;
      vertices = realloc(vertices, sizeof(Vertex) * vertex_number);
      vertices[vertex_number - 1] = vertex;
    }
    else if (line[0] == 'f' && line[1] == ' ') {
      Triangle triangle;
      char* token;
      strtok(line, " ");

      for (int ix = 0; ix < 3; ++ix) {
        int vertex_index = -1, _texture_index, _normal_index;

        token = strtok(NULL, " ");

        if (sscanf(token, "%i/%i/%i", &vertex_index, &_texture_index, &_normal_index) == 3) {
          triangle.vertices[ix] = &vertices[vertex_index - 1];
        }
        else if (sscanf(token, "%i//%i", &vertex_index, &_normal_index) == 2) {
          triangle.vertices[ix] = &vertices[vertex_index - 1];
        }
        else if (sscanf(token, "%i/%i", &vertex_index, &_texture_index) == 2) {
          triangle.vertices[ix] = &vertices[vertex_index - 1];
        }
        else if (sscanf(token, "%i", &vertex_index) == 1) {
          triangle.vertices[ix] = &vertices[vertex_index - 1];
        }
      }

      ++triangle_number;
      triangles = realloc(triangles, sizeof(Triangle) * triangle_number);
      triangles[triangle_number - 1] = triangle;
    }
  }

  return (Mesh) {
    .vertex_number = vertex_number,
    .triangle_number = triangle_number,
    .vertices = vertices,
    .triangles = triangles
  };
}
