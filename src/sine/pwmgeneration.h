/*
 * This file is part of the tumanako_vc project.
 *
 * Copyright (C) 2015 Johannes Huebner <dev@johanneshuebner.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef PWMGENERATION_H
#define PWMGENERATION_H

#include <stdint.h>
#include "my_fp.h"

class PwmGeneration
{
   public:
      static uint16_t GetAngle();
      static bool Tripped();
      static void PwmInit();
      static void SetOpmode(int);
      static void SetAmpnom(s32fp amp);
      static void SetFslip(s32fp fslip);
   private:
      static void EnableOutput();
      static void DisableOutput();
      static uint16_t TimerSetup(uint16_t deadtime, int pwmpol);
};

#endif // PWMGENERATION_H
