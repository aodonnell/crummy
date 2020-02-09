#ifndef _CRUMBMATH_H
#define _CRUMBMATH_H

#include <raylib.h>

Vector2 Vector2Lerp(Vector2 current, Vector2 target, float by);

int SnapToCrumbX(float snapX);

int SnapToCrumbY(float snapY);

Vector2 SnapToCrumb(Vector2 snap);

int WorldToSnapX(float worldX);

int WorldToSnapY(float worldY);

Vector2 WorldToSnap(Vector2 world);

float ScreenToWorldX(float screenX);

float ScreenToWorldY(float screenY);

Vector2 ScreenToWorld(Vector2 screen);

float ScreenToSnapX(float screenX);

float ScreenToSnapY(float screenY);

Vector2 ScreenToSnap(Vector2 screen);

float WorldToScreenX(float worldX);

float WorldToScreenY(float worldY);

Vector2 WorldToScreen(Vector2 world);

int RandInRange(int low, int high);

double Rand01();

#endif