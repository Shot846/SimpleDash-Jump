#include "zcommon.acs"

int Buttons, OldButtons, Buttonz, OldButtonz;

int ByteAngle, Angle;

int DashCooldown[64], JumpCooldown[64];

int x, y, z, xv, yv, zv;

int djump2rnd;

float dashpower;
int dashpowerup;

//Original code by TerminusEst13, Huge thanks to him!
//Modified by Shot846

Script "CooldownInit" ENTER
{
DashCooldown[PlayerNumber()] = 0;
JumpCooldown[PlayerNumber()] = 0;
}


Script "ThrustMe" (int angle)
{
	
	dashpower = GetCVar("sv_dashpower");
	dashpowerup = GetCVar("sv_dashpowerup");
	
	if(angle == 8) //Absolute Forward
	{
	  SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)),dashpower),yv + FixedMul(sin(GetActorAngle(0)),dashpower),0.0,FALSE,FALSE);
	}
	
	if(angle == 4) //Absolute Left
	{
	SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+16384),dashpower),yv + FixedMul(sin(GetActorAngle(0)+16384),dashpower),0.0,FALSE,FALSE);
	}
	
	if(angle == 2) //Absolute Backward
	{
	SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+32768),dashpower),yv + FixedMul(sin(GetActorAngle(0)+32768),dashpower),0.0,FALSE,FALSE);	
	}
	
	if(angle == 6) //Absolute Right
	{
	SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+49152),dashpower),yv + FixedMul(sin(GetActorAngle(0)+49152),dashpower),0.0,FALSE,FALSE);
	}
	
	if(angle == 7) //Forward Diagonal Left
	{
	SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+8192),dashpower),yv + FixedMul(sin(GetActorAngle(0)+8192),dashpower),0.0,FALSE,FALSE);
	}
	
	if(angle == 9) //Forward Diagonal Right
	{
	SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+57344),dashpower),yv + FixedMul(sin(GetActorAngle(0)+57344),dashpower),0.0,FALSE,FALSE);
	}
	
	if(angle == 1) //Backward Diagonal Left
	{
	SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+24576),dashpower),yv + FixedMul(sin(GetActorAngle(0)+24576),dashpower),0.0,FALSE,FALSE);
	}
	
	if(angle == 3) //Backward Diagonal Right
	{
	SetActorVelocity(0,xv + FixedMul(cos(GetActorAngle(0)+40960),dashpower),yv + FixedMul(sin(GetActorAngle(0)+40960),dashpower),0.0,FALSE,FALSE);
	}
	
	if (CheckInventory("OnTheGround") == 0)			  
			  {
			  ThrustThingZ(0,dashpowerup,0,1);
			  }
              else 
			  { 
			  ThrustThingZ(0,dashpowerup/4,0,1);
			  }

	
	  if (GetCVar("cl_allowdashsound") == 1)
              {
                if (GetCVar("cl_dashsoundtype") == 0)
                {
                  PlaySound(0,"DASH1",CHAN_AUTO,1.0,FALSE);
                }
                if (GetCVar("cl_dashsoundtype") == 1)
                {
                  PlaySound(0,"DASH2",CHAN_AUTO,1.0,FALSE);
                }
              }
				        
              DashCooldown[PlayerNumber()] = GetCVar("sv_dashcooldown");
	

}



Script "Dash" ENTER
{


OldButtons = GetPlayerInput(-1, INPUT_OLDBUTTONS);
Buttons = GetPlayerInput(-1, INPUT_BUTTONS);
ByteAngle = GetActorAngle(0) >> 8;
//Angle = GetActorAngle(0);

xv = GetActorVelX(0);
yv = GetActorVelY(0);
zv = GetActorVelZ(0);
            
x = GetActorX(0);
y = GetActorY(0);
z = GetActorZ(0) - GetActorFloorZ(0);
	
		if (DashCooldown[PlayerNumber()] == 0 && GetCvar("sv_allowdash"))
        {
          if (buttons & BT_SPEED)
          {
			  //8 = Absolute Forward
              if (buttons & BT_FORWARD && !(buttons & BT_BACK) && !(buttons & BT_MOVELEFT) && !(buttons & BT_MOVERIGHT) ) { ACS_NamedExecuteAlways("ThrustMe",0,8); }
			  //4 = Absolute Left
              if (buttons & BT_MOVELEFT && !(buttons & BT_BACK) && !(buttons & BT_FORWARD) && !(buttons & BT_MOVERIGHT) ) { ACS_NamedExecuteAlways("ThrustMe",0,4); }
			  //2 = Absolute Backward
              if (buttons & BT_BACK && !(buttons & BT_MOVELEFT) && !(buttons & BT_FORWARD) && !(buttons & BT_MOVERIGHT)  ) { ACS_NamedExecuteAlways("ThrustMe",0,2); }
			  //6 = Absolute Right
              if (buttons & BT_MOVERIGHT && !(buttons & BT_BACK) && !(buttons & BT_MOVELEFT) && !(buttons & BT_FORWARD) ) { ACS_NamedExecuteAlways("ThrustMe",0,6); }
	  
			  //7 = Forward Diagonal Left
			  if (buttons & BT_FORWARD && !(buttons & BT_BACK) && (buttons & BT_MOVELEFT) && !(buttons & BT_MOVERIGHT) ) { ACS_NamedExecuteAlways("ThrustMe",0,7); } 
			  //9 = Forward Diagonal Right
			  if (buttons & BT_FORWARD && !(buttons & BT_BACK) && !(buttons & BT_MOVELEFT) && (buttons & BT_MOVERIGHT) ) { ACS_NamedExecuteAlways("ThrustMe",0,9); }
			  
			  //1 = Backward Diagonal Left
			  if (buttons & BT_BACK && (buttons & BT_MOVELEFT) && !(buttons & BT_FORWARD) && !(buttons & BT_MOVERIGHT)  ) { ACS_NamedExecuteAlways("ThrustMe",0,1); }	  
			  //3 = Backward Diagonal Right
			  if (buttons & BT_BACK && !(buttons & BT_MOVELEFT) && !(buttons & BT_FORWARD) && (buttons & BT_MOVERIGHT)  ) { ACS_NamedExecuteAlways("ThrustMe",0,3); }
			  
			  
			  
              
			  
			 
          }
        }
		
	While (DashCooldown[PlayerNumber()] > 0)
	{
	DashCooldown[PlayerNumber()]--;
	Delay(1);
	}
    Delay(1);
	ACS_NamedExecuteAlways("Dash",0);
}





Script "DoubleJump" ENTER
{
OldButtonz = GetPlayerInput(-1, INPUT_OLDBUTTONS);
Buttonz = GetPlayerInput(-1, INPUT_BUTTONS);

 if (GetActorVelZ(0) <= 8 && !CheckInventory("OnTheGround") && CheckInventory("InTheAir") == 0 && buttonz & BT_JUMP && GetCvar("sv_nojump") == 0 && GetCvar("sv_allowdoublejump"))
        {
		  if(GetCvar("sv_allowdoublejump"))
		  {
			  
			
          if (GetCVar("cl_allowdjumpsound") == 1)
          {
            if (GetCVar("cl_djumpsoundtype") == 0)
            {
              PlaySound(0,"DJUMP1",CHAN_AUTO,1.0,FALSE);
            }
             if (GetCVar("cl_djumpsoundtype") == 1)
            {
              djump2rnd = random(1, 2);
              if (djump2rnd == 1)
              {
                PlaySound(0,"DJUMP2A",CHAN_AUTO,1.0,FALSE);
              }
              if (djump2rnd == 2)
              {
                PlaySound(0,"DJUMP2B",CHAN_AUTO,1.0,FALSE);
              }
              
            }          
		  }
			ThrustThingZ(0,36,0,0);
			GiveInventory("InTheAir", 1);
			}
		
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
