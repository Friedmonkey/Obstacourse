#pragma once

#include <Raylib.h>
#include <Box2D/Box2D.h>

#define SW 800
#define SH 600

#define SW2 SW/2
#define SH2 SH/2

#define PhysicsWorldScale 8

#define ConvertToBox(vector) b2Vec2(vector.x, vector.y)
#define ConvertToRay(vector) Vector2{vector.x, vector.y}

// colors
#define CORNFLOWERBLUE CLITERAL(Color){ 100, 149, 237, 255 }


