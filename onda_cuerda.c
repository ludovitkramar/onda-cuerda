#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define SAMPLES 10000
#define SIZE 1
#define OFFSET 140
#define SPACING 0.01f

float A = 6;
float w = .4f * M_PI;
float k = M_PI / 6;
float fi = 0;
int tm = 0;
float az = 10;          // amplitude zoom
float lz = 15;          // longitud zoom
int settingsSwitch = 0; // 1 = A , 2 = w, 3 = k, 4 = fi

float y(float x, float t) { return A * sinf((w * t) - (k * x) + fi); }
float v(float x, float t) { return A * w * cosf((w * t) - (k * x) + fi); }
float a(float x, float t) { return -A * w * w * sinf((w * t) - (k * x) + fi); }

int main(void) {
  // Initialization
  const int screenWidth = 1600;
  const int screenHeight = 900;

  InitWindow(screenWidth, screenHeight, "Onda cuerda");

  Camera2D camera = {0};
  camera.offset = (Vector2){20, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  Rectangle sample[SAMPLES] = {0};
  Color sampleColor[SAMPLES] = {0};

  for (int i = 0; i < SAMPLES; i++) {
    sample[i].height = SIZE;
    sample[i].width = SIZE;
    sample[i].x = i * SPACING;
    sample[i].y = 0;
    sampleColor[i] = BLACK;
  }

  SetTargetFPS(75);

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //---------------------------------------------------------------------------------

    // 2d camera controlls
    // Camera rotation
    if (IsKeyDown(KEY_Q))
      camera.rotation--;
    else if (IsKeyDown(KEY_E))
      camera.rotation++;

    // Reset
    if (IsKeyPressed(KEY_R)) {
      camera.zoom = 1.0f;
      camera.rotation = 0.0f;
      az = 10;
      tm = 0;
      lz = 15;
    }

    // input
    if (IsKeyDown(KEY_PAGE_DOWN)) {
      tm -= 1;
    }
    if (IsKeyDown(KEY_PAGE_UP)) {
      tm += 1;
    }
    if (IsKeyDown(KEY_UP))
      az += .1;
    else if (IsKeyDown(KEY_DOWN))
      az -= .1;
    if (IsKeyDown(KEY_RIGHT))
      lz += .05f;
    else if (IsKeyDown(KEY_LEFT))
      lz -= .05f;
    if (IsKeyPressed(KEY_A))
      settingsSwitch = 1;
    if (IsKeyPressed(KEY_W))
      settingsSwitch = 2;
    if (IsKeyPressed(KEY_K))
      settingsSwitch = 3;
    if (IsKeyPressed(KEY_F))
      settingsSwitch = 4;
    if (IsKeyPressed(KEY_ONE))
      settingsSwitch = 1;
    if (IsKeyPressed(KEY_TWO))
      settingsSwitch = 2;
    if (IsKeyPressed(KEY_THREE))
      settingsSwitch = 3;
    if (IsKeyPressed(KEY_FOUR))
      settingsSwitch = 4;

    switch (settingsSwitch) {
    case 1:
      A += ((float)GetMouseWheelMove() * 0.05f);
      break;
    case 2:
      w += ((float)GetMouseWheelMove() * 0.05f);
      break;
    case 3:
      k += ((float)GetMouseWheelMove() * 0.05f);
      break;
    case 4:
      fi += ((float)GetMouseWheelMove() * 0.05f);
      break;
    default:
      break;
    }

    // calculate
    for (int i = 0; i < SAMPLES; i++) {
      sample[i].x = i * SPACING * lz;
      sample[i].y = y(i * SPACING, tm) * az;
    }

    // convert numbers to text
    char time[11];
    sprintf(time, "%d", tm); // convert int t to time
    char At[11];
    sprintf(At, "%f", A); // convert amplitud to text
    char wt[11];
    sprintf(wt, "%f", w); // convert Pulsacion to text
    char kt[11];
    sprintf(kt, "%f", k); // convert k to text
    char fit[11];
    sprintf(fit, "%f", fi); // convert fi0 to text
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    for (int i = 0; i < SAMPLES; i++) {
      DrawRectangleRec(sample[i], sampleColor[i]);
    }

    EndMode2D();
    DrawFPS(10, 10);

    DrawText("Flechas para zoom, PageUp PageDown controla el tiempo, R "
             "restaura los valores al estado inicial.",
             10, 35, 20, GRAY);
    DrawText(
        "La tecla A activa la configuración de la amplitud, W de la pulsación, "
        "K del valor k y F del desfase. La rueda del ratón cambio los valores.",
        10, 60, 20, GRAY);

    DrawText("Amplitud:", 10, 100, 20, BLACK);
    DrawText(At, OFFSET, 100, 20, BLACK);

    DrawText("Pulsación:", 10, 130, 20, BLACK);
    DrawText(wt, OFFSET, 130, 20, BLACK);

    DrawText("Nº onda (k):", 10, 160, 20, BLACK);
    DrawText(kt, OFFSET, 160, 20, BLACK);

    DrawText("Desfase:", 10, 190, 20, BLACK);
    DrawText(fit, OFFSET, 190, 20, BLACK);

    DrawText("Tiempo:", 10, 220, 20, BLACK);
    DrawText(time, OFFSET, 220, 20, BLACK);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
