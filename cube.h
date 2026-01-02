#ifndef D_OBJECT_DATA_H
#define D_OBJECT_DATA_H

// Define the 3D Vector structure (moved from .ino)
struct Vec3 {
  float x, y, z;
};

// --- 3D Object Data (Vertices and Faces) ---

// 3D Object vertices (relative coordinates -0.25 to 0.25)
const Vec3 vs[] = {
    {0.25f, 0.25f, 0.25f},
    {-0.25f, 0.25f, 0.25f},
    {-0.25f, -0.25f, 0.25f},
    {0.25f, -0.25f, 0.25f},

    {0.25f, 0.25f, -0.25f},
    {-0.25f, 0.25f, -0.25f},
    {-0.25f, -0.25f, -0.25f},
    {0.25f, -0.25f, -0.25f},
};
const int NUM_VERTICES = 8;

// 3D Object faces (edges defined by vertex indices)
// Renamed from 'fs' to 'object_edges' to avoid conflict with the ESP32 'fs' File System namespace.
const int object_edges[][2] = {
    // Front face edges
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    // Back face edges
    {4, 5}, {5, 6}, {6, 7}, {7, 4},
    // Connecting edges
    {0, 4}, {1, 5}, {2, 6}, {3, 7},
};
const int NUM_EDGES = 12;

#endif // D_OBJECT_DATA_H