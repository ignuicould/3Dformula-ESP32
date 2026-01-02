#include <TFT_eSPI.h>
#include "penger.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

#define BACKGROUND_COLOR TFT_BLACK
#define FOREGROUND_COLOR TFT_GREEN

int CANVAS_WIDTH;
int CANVAS_HEIGHT;

struct Point2D {
  int x, y;
};

float dz = 1.0f;
float angle = 0.0f;

Vec3 translate_z(const Vec3& p, float delta_z) {
  return {p.x, p.y, p.z + delta_z};
}

Vec3 rotate_xz(const Vec3& p, float rotation_angle) {
  float c = cosf(rotation_angle);
  float s = sinf(rotation_angle);
  return {
    p.x * c - p.z * s,
    p.y,
    p.x * s + p.z * c
  };
}

Vec3 project(const Vec3& p) {
  if (p.z < 0.001f) return {0.0f, 0.0f, 0.0f}; 
  return {p.x / p.z, p.y / p.z, 0.0f};
}

Point2D screen(const Vec3& p) {
  return {
    (int)round((p.x * 0.5f + 0.5f) * CANVAS_WIDTH),
    (int)round((0.5f - p.y * 0.5f) * CANVAS_HEIGHT)
  };
}

void clear_sprite() {
  spr.fillSprite(BACKGROUND_COLOR);
}

void draw_line(const Point2D& p1, const Point2D& p2) {
  spr.drawLine(p1.x, p1.y, p2.x, p2.y, FOREGROUND_COLOR);
}

void frame() {
  const float ROTATION_SPEED = 0.05f;
  angle += ROTATION_SPEED;
  
  if (angle > TWO_PI) {
    angle -= TWO_PI;
  }

  clear_sprite();

  for (int i = 0; i < NUM_VERTICES; ++i) {
    Point2D p = screen(project(translate_z(rotate_xz(vs[i], angle), dz)));
    spr.fillRect(p.x - 1, p.y - 1, 3, 3, TFT_WHITE);
  }

  for (int i = 0; i < NUM_EDGES; ++i) {
    const Vec3& vA = vs[object_edges[i][0]];
    const Vec3& vB = vs[object_edges[i][1]];

    Vec3 tA = translate_z(rotate_xz(vA, angle), dz);
    Vec3 tB = translate_z(rotate_xz(vB, angle), dz);

    draw_line(screen(project(tA)), screen(project(tB)));
  }

  spr.pushSprite(0, 0);
}

void setup() {
  tft.init();
  tft.setRotation(1);
  
  CANVAS_WIDTH = tft.width();
  CANVAS_HEIGHT = tft.height();

  //spr.setColorDepth(8); // Optional: Use 8-bit to save RAM if 16-bit is too large
  spr.createSprite(CANVAS_WIDTH, CANVAS_HEIGHT);
}

void loop() {
  frame();
}