#include "zcommon.acs"

int Buttons;
int OldButtons;
int Buttonz;
int OldButtonz;
int ByteAngle;
int Angle;
int DashCooldown[64];
int JumpCooldown[64];
int xv;
int yv;
int zv;
int x;
int y;
int z;

int dg = 32.0; //dash on the ground
int da = 12.0; //dash in the air
int du = 8.0; //dash upwards

//Original code by TerminusEst13, Huge thanks to him!
//Modified by Shot846

Script "CooldownInit" ENTER
{
DashCooldown[PlayerNumber()] = 0;
JumpCooldown[PlayerNumber()] = 0;
}

Script "Dash" ENTER
{


OldButtons = GetPlayerInput(-1, INPUT_OLDBUTTONS);
Buttons = GetPlayerInput(-1, INPUT_BUTTONS);
//ByteAngle = GetActorAngle(0) >> 8;
//Angle = GetActorAngle(0);

xv = GetActorVelX(0);
yv = GetActorVelY(0);
zv = GetActorVelZ(0);
            
x = GetActorX(0);
y = GetActorY(0);
z = GetActorZ(0) - GetActorFloorZ(0);


// DASH
        if (DashCooldown[PlayerNumber()] == 0 && GetCvar("shot_allowdash"))
        {
          if (buttons & BT_SPEED && buttons & BT_FORWARD && DashCooldown[PlayerNumber()] == 0)
          {
              if (CheckInventory("OnTheGround") == 1) { SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)),dg),yv + FixedMul(sin(GetActorAngle(0)),dg),0.0,0,0);  } else { SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)),da),yv + FixedMul(sin(GetActorAngle(0)),da),du,0,0); }
              ActivatorSound("DASH",127);
              DashCooldown[PlayerNumber()] = 35;
          }
          if (buttons & BT_SPEED && buttons & BT_MOVELEFT && DashCooldown[PlayerNumber()] == 0)
          {
              if (CheckInventory("OnTheGround") == 1) { SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+16384),dg),yv + FixedMul(sin(GetActorAngle(0)+16384),dg),0.0,0,0); } else { SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+16384),da),yv + FixedMul(sin(GetActorAngle(0)+16384),da),du,0,0); }
              ActivatorSound("DASH",127);
              DashCooldown[PlayerNumber()] = 35; 
          }
          if (buttons & BT_SPEED && buttons & BT_BACK && DashCooldown[PlayerNumber()] == 0)
          {
              if (CheckInventory("OnTheGround") == 1) { SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+32768),dg),yv + FixedMul(sin(GetActorAngle(0)+32768),dg),0.0,0,0);  } else { SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+32768),da),yv + FixedMul(sin(GetActorAngle(0)+32768),da),du,0,0);  }
              ActivatorSound("DASH",127);
              DashCooldown[PlayerNumber()] = 35;
          }
          if (buttons & BT_SPEED && buttons & BT_MOVERIGHT && DashCooldown[PlayerNumber()] == 0)
          {
              if (CheckInventory("OnTheGround") == 1) { SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+49152),dg),yv + FixedMul(sin(GetActorAngle(0)+49152),dg),0.0,0,0);  } else { SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+49152),da),yv + FixedMul(sin(GetActorAngle(0)+49152),da),du,0,0);  }
              ActivatorSound("DASH",127);
              DashCooldown[PlayerNumber()] = 35;
          }
        }
    
    
While (DashCooldown[PlayerNumber()] > 0)
{
DashCooldown[PlayerNumber()]--;
Delay(1);
}


    
    
      
delay(1);
ACS_NamedExecuteAlways("Dash",0);
}






Script "DoubleJump" ENTER
{
OldButtonz = GetPlayerInput(-1, INPUT_OLDBUTTONS);
Buttonz = GetPlayerInput(-1, INPUT_BUTTONS);

 if (GetActorVelZ(0) <= 8 && !CheckInventory("OnTheGround") && CheckInventory("InTheAir") == 0 && buttonz & BT_JUMP && GetCvar("sv_nojump") == 0 && GetCvar("shot_allowdoublejump"))
        {
          ActivatorSound("DJUMP", 127);
          ThrustThingZ(0,36,0,0);
          GiveInventory("InTheAir", 1);
        }

        if (GetActorZ(0) - GetActorFloorZ(0) == 0)
        {
              GiveInventory("OnTheGround", 1);
              TakeInventory("InTheAir",1);
        }
        else
            { 
             TakeInventory("OnTheGround", 1);      
            }
ACS_NamedExecuteAlways("DoubleJump",0);
}

