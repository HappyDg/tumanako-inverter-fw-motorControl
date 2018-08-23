/*
 * This file is part of the tumanako_vc project.
 *
 * Copyright (C) 2011 Johannes Huebner <dev@johanneshuebner.com>
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

#define OPMODES     "0=Off, 1=Run, 2=ManualRun, 3=Boost, 4=Buck, 5=Sine, 6=AcHeat"
#define PWMFRQS     "0=17.6kHz, 1=8.8kHz, 2=4.4KHz, 3=2.2kHz, 4=1.1kHz"
#define PWMPOLS     "0=ACTHIGH, 1=ACTLOW"
#define DIRS        "-1=REV, 0=NEUTRAL, 1=FWD"
#define TRIPMODES   "0=AllOff, 1=dcswon, 2=prechargeon"
#define SNS_HS      "0=JCurve, 1=Semikron, 2=MBB600"
#define SNS_M       "12=KTY83-110, 13=KTY84-130, 14=Leaf"
#define PWMFUNCS    "0=tmpm, 1=tmphs, 2=speed"
#define CRUISEMODS  "0=Button, 1=Switch"
#define IDLEMODS    "0=always, 1=nobrake, 2=cruise"
#define ONOFF       "0=Off, 1=On"
#define CHARGEMODS  "0=Off, 3=Boost, 4=Buck"
#define ENCMODES    "0=Single, 1=AB, 2=ABZ, 3=SPI, 4=Resolver"
#define POTMODES    "0=SingleRegen, 1=DualChannel, 2=CAN"
#define CANSPEEDS   "0=250k, 1=500k, 2=800k, 3=1M"
#define CANIOS       "1=Cruise, 2=Start, 4=Brake, 8=Fwd, 16=Rev, 32=Bms"
#define CAT_MOTOR    "Motor"
#define CAT_INVERTER "Inverter"
#define CAT_THROTTLE "Throttle"
#define CAT_REGEN    "Regen"
#define CAT_AUTOM    "Automation"
#define CAT_DERATE   "Derating"
#define CAT_PWM      "Aux PWM"
#define CAT_CONTACT  "Contactor Control"
#define CAT_TEST     "Testing"
#define CAT_CHARGER  "Charger"
#define CAT_COMM     "Communication"

#define VER 3.96

enum _modes
{
   MOD_OFF = 0,
   MOD_RUN,
   MOD_MANUAL,
   MOD_BOOST,
   MOD_BUCK,
   MOD_SINE,
   MOD_ACHEAT,
   MOD_LAST
};

enum _tripmodes
{
   TRIP_ALLOFF = 0,
   TRIP_DCSWON,
   TRIP_PRECHARGEON
};

enum _canio
{
   CAN_IO_CRUISE = 1,
   CAN_IO_START = 2,
   CAN_IO_BRAKE = 4,
   CAN_IO_FWD = 8,
   CAN_IO_REV = 16,
   CAN_IO_BMS = 32
};

#define BUTTON 0

#define PWM_FUNC_TMPM       0
#define PWM_FUNC_TMPHS      1
#define PWM_FUNC_SPEED      2

#define IDLE_MODE_ALWAYS    0
#define IDLE_MODE_NOBRAKE   1
#define IDLE_MODE_CRUISE    2

#define POTMODE_REGENADJ    0
#define POTMODE_DUALCHANNEL 1
#define POTMODE_CAN         2

/* Entries must be ordered as follows:
   1. Saveable parameters (id != 0)
   2. Temporary parameters (id = 0)
   3. Display values
 */
//Next param id (increase when adding new parameter!): 88
/*              category     name         unit       min     max     default id */
#define PARAM_LIST \
    PARAM_ENTRY(CAT_MOTOR,   boost,       "dig",     0,      37813,  1700,   1   ) \
    PARAM_ENTRY(CAT_MOTOR,   fweak,       "Hz",      0,      1000,   90,     2   ) \
    PARAM_ENTRY(CAT_MOTOR,   udcnom,      "V",       0,      1000,   0,      78  ) \
    PARAM_ENTRY(CAT_MOTOR,   fpconst,     "Hz",      0,      1000,   1000,   60  ) \
    PARAM_ENTRY(CAT_MOTOR,   fslipmin,    "Hz",      0,      10,     1,      37  ) \
    PARAM_ENTRY(CAT_MOTOR,   fslipmax,    "Hz",      0,      10,     3,      33  ) \
    PARAM_ENTRY(CAT_MOTOR,   polepairs,   "",        1,      16,     2,      32  ) \
    PARAM_ENTRY(CAT_MOTOR,   ampmin,      "%",       0,      100,    10,     4   ) \
    PARAM_ENTRY(CAT_MOTOR,   encflt,      "",        0,      16,     1,      6   ) \
    PARAM_ENTRY(CAT_MOTOR,   encmode,     ENCMODES,  0,      4,      0,      75  ) \
    PARAM_ENTRY(CAT_MOTOR,   fmin,        "Hz",      0,      400,    1,      34  ) \
    PARAM_ENTRY(CAT_MOTOR,   fmax,        "Hz",      0,      1000,   200,    9   ) \
    PARAM_ENTRY(CAT_MOTOR,   numimp,      "Imp/rev", 8,      8192,   60,     15  ) \
    PARAM_ENTRY(CAT_MOTOR,   dirchrpm,    "rpm",     0,      2000,   100,    87  ) \
    PARAM_ENTRY(CAT_MOTOR,   syncofs,     "dig",     0,      65535,  0,      70  ) \
    /*PARAM_ENTRY(CAT_MOTOR,   delay,       "µs",      0,      65535,  40,     84  )*/ \
    PARAM_ENTRY(CAT_MOTOR,   snsm,        SNS_M,     12,     14,     12,     46  ) \
    PARAM_ENTRY(CAT_INVERTER,pwmfrq,      PWMFRQS,   0,      4,      1,      13  ) \
    PARAM_ENTRY(CAT_INVERTER,pwmpol,      PWMPOLS,   0,      1,      0,      52  ) \
    PARAM_ENTRY(CAT_INVERTER,deadtime,    "dig",     0,      255,    63,     14  ) \
    PARAM_ENTRY(CAT_INVERTER,ocurlim,     "A",       -65536, 65536,  100,    22  ) \
    PARAM_ENTRY(CAT_INVERTER,tripmode,    TRIPMODES, 0,      2,      0,      86  ) \
    PARAM_ENTRY(CAT_INVERTER,minpulse,    "dig",     0,      4095,   1000,   24  ) \
    PARAM_ENTRY(CAT_INVERTER,il1gain,     "dig/A",   -100,   100,    4.7,    27  ) \
    PARAM_ENTRY(CAT_INVERTER,il2gain,     "dig/A",   -100,   100,    4.7,    28  ) \
    PARAM_ENTRY(CAT_INVERTER,udcgain,     "dig/V",   0,      4095,   6.175,  29  ) \
    PARAM_ENTRY(CAT_INVERTER,udcofs,      "dig",     0,      4095,   0,      77  ) \
    PARAM_ENTRY(CAT_INVERTER,udclim,      "V",       0,      1000,   540,    48  ) \
    PARAM_ENTRY(CAT_INVERTER,snshs,       SNS_HS,    0,      2,      0,      45  ) \
    PARAM_ENTRY(CAT_CHARGER, chargemode,  CHARGEMODS,0,      4,      0,      74  ) \
    PARAM_ENTRY(CAT_CHARGER, chargecur,   "A",       0,      50,     0,      71  ) \
    PARAM_ENTRY(CAT_CHARGER, chargekp,    "dig",     0,      100,    80,     72  ) \
    PARAM_ENTRY(CAT_CHARGER, chargeflt,   "dig",     0,      10,     8,      73  ) \
    PARAM_ENTRY(CAT_CHARGER, chargemax,   "%",       0,      99,     90,     79  ) \
    PARAM_ENTRY(CAT_THROTTLE,potmin,      "dig",     0,      4095,   0,      17  ) \
    PARAM_ENTRY(CAT_THROTTLE,potmax,      "dig",     0,      4095,   4095,   18  ) \
    PARAM_ENTRY(CAT_THROTTLE,pot2min,     "dig",     0,      4095,   4095,   63  ) \
    PARAM_ENTRY(CAT_THROTTLE,pot2max,     "dig",     0,      4095,   4095,   64  ) \
    PARAM_ENTRY(CAT_THROTTLE,potmode,     POTMODES,  0,      2,      0,      82  ) \
    PARAM_ENTRY(CAT_THROTTLE,throtramp,   "%/10ms",  1,      100,    100,    81  ) \
    PARAM_ENTRY(CAT_THROTTLE,throtramprpm,"rpm",     0,      20000,  20000,  85  ) \
    PARAM_ENTRY(CAT_REGEN,   brknompedal, "%",       -100,   0,      -50,    38  ) \
    PARAM_ENTRY(CAT_REGEN,   brkpedalramp,"%/10ms",  1,      100,    100,    68  ) \
    PARAM_ENTRY(CAT_REGEN,   brknom,      "%",       0,      100,    30,     19  ) \
    PARAM_ENTRY(CAT_REGEN,   brkmax,      "%",       0,      100,    30,     49  ) \
    PARAM_ENTRY(CAT_REGEN,   brkrampstr,  "Hz",      0,      400,    10,     39  ) \
    PARAM_ENTRY(CAT_REGEN,   brkout,      "%",       -100,   -1,     -50,    67  ) \
    PARAM_ENTRY(CAT_AUTOM,   idlespeed,   "rpm",     -100,   1000,   -100,   54  ) \
    PARAM_ENTRY(CAT_AUTOM,   idlethrotlim,"%",       0,      100,    50,     65  ) \
    PARAM_ENTRY(CAT_AUTOM,   idlemode,    IDLEMODS,  0,      2,      0,      66  ) \
    PARAM_ENTRY(CAT_AUTOM,   speedkp,     "",        0,      100,    0.25,   53  ) \
    PARAM_ENTRY(CAT_AUTOM,   speedflt,    "",        0,      16,     5,      57  ) \
    PARAM_ENTRY(CAT_AUTOM,   cruisemode,  CRUISEMODS,0,      1,      0,      62  ) \
    PARAM_ENTRY(CAT_DERATE,  bmslimhigh,  "%",       0,      100,    50,     55  ) \
    PARAM_ENTRY(CAT_DERATE,  bmslimlow,   "%",       -100,   0,      -1,     56  ) \
    PARAM_ENTRY(CAT_DERATE,  udcmin,      "V",       0,      1000,   450,    42  ) \
    PARAM_ENTRY(CAT_DERATE,  udcmax,      "V",       0,      1000,   520,    43  ) \
    PARAM_ENTRY(CAT_CONTACT, udcsw,       "V",       0,      1000,   330,    20  ) \
    PARAM_ENTRY(CAT_CONTACT, udcswbuck,   "V",       0,      1000,   540,    80  ) \
    PARAM_ENTRY(CAT_PWM,     pwmfunc,     PWMFUNCS,  0,      2,      0,      58  ) \
    PARAM_ENTRY(CAT_PWM,     pwmgain,     "dig/C",   -65535, 65535,  100,    40  ) \
    PARAM_ENTRY(CAT_PWM,     pwmofs,      "dig",     -65535, 65535,  0,      41  ) \
    PARAM_ENTRY(CAT_PWM,     speedgain,   "rpm/kHz", 0,      65535,  6000,   59  ) \
    PARAM_ENTRY(CAT_COMM,    canspeed,    CANSPEEDS, 0,      3,      0,      83  ) \
    PARAM_ENTRY(CAT_TEST,    fslipspnt,   "Hz",      -100,   1000,   0,      0   ) \
    PARAM_ENTRY(CAT_TEST,    ampnom,      "%",       0,      100,    0,      0   ) \
    PARAM_ENTRY(CAT_TEST,    version,     "",        0,      0,      VER,    0   ) \
    VALUE_ENTRY(opmode,      OPMODES ) \
    VALUE_ENTRY(udc,         "V"     ) \
    VALUE_ENTRY(idc,         "A"     ) \
    VALUE_ENTRY(il1,         "A"     ) \
    VALUE_ENTRY(il2,         "A"     ) \
    VALUE_ENTRY(uac,         "V"     ) \
    VALUE_ENTRY(il1rms,      "A"     ) \
    VALUE_ENTRY(il2rms,      "A"     ) \
    VALUE_ENTRY(boostcalc,   "digit" ) \
    VALUE_ENTRY(fweakcalc,   "Hz"    ) \
    VALUE_ENTRY(id,          "A"     ) \
    VALUE_ENTRY(iq,          "A"     ) \
    VALUE_ENTRY(p,           "kW"    ) \
    VALUE_ENTRY(q,           "kVA"   ) \
    VALUE_ENTRY(s,           "kVA"   ) \
    VALUE_ENTRY(pf,          ""      ) \
    VALUE_ENTRY(t,           "Nm"    ) \
    VALUE_ENTRY(fstat,       "Hz"    ) \
    VALUE_ENTRY(speed,       "rpm"   ) \
    VALUE_ENTRY(amp,         "dig"   ) \
    VALUE_ENTRY(pot,         "dig"   ) \
    VALUE_ENTRY(pot2,        "dig"   ) \
    VALUE_ENTRY(potnom,      "%"     ) \
    VALUE_ENTRY(dir,         DIRS    ) \
    VALUE_ENTRY(tmphs,       "°C"    ) \
    VALUE_ENTRY(tmpm,        "°C"    ) \
    VALUE_ENTRY(uaux,        "V"     ) \
    VALUE_ENTRY(canio,       CANIOS  ) \
    VALUE_ENTRY(din_cruise,  ""      ) \
    VALUE_ENTRY(din_start,   ""      ) \
    VALUE_ENTRY(din_brake,   ""      ) \
    VALUE_ENTRY(din_mprot,   ""      ) \
    VALUE_ENTRY(din_forward, ""      ) \
    VALUE_ENTRY(din_reverse, ""      ) \
    VALUE_ENTRY(din_emcystop,""      ) \
    VALUE_ENTRY(din_ocur,    ""      ) \
    VALUE_ENTRY(din_desat,   ""      ) \
    VALUE_ENTRY(din_bms,     ""      ) \
    VALUE_ENTRY(dout_prec,   ""      ) \
    VALUE_ENTRY(dout_dcsw,   ""      ) \
    VALUE_ENTRY(tm_meas,     "us"    ) \
    VALUE_ENTRY(angle,     "°"    ) \

