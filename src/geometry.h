#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint16_t x, y;
} Point;

typedef struct {
  float x, y, z;
} Vertex;

typedef struct {
  Vertex* vertices[3];
} Triangle;

typedef struct {
  size_t vertex_number, triangle_number;
  Vertex* vertices;
  Triangle* triangles;
} Mesh;

#endif
