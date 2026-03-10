#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include "sand_grain.h"
#include <vector>
#include "utils.h"

const float gravityForce = 9.8f;

float deltaTime(Uint64& lastTick);
void ApplyGravity(std::shared_ptr<SandGrain> sandGrain, float dt);
void CheckCollisions(std::shared_ptr<SandGrain> sandGrain);