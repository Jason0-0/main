#include "robot_movement.h"
#include <Arduino.h>
#include "Arm.h"

//const identify
const long arm_grab_angle = -10;
const long arm_place_angle = 3;
const long arm_smallRise_angle = 15; //微微抬起以避免夹爪舵机干涉
const long arm_camera_angle = 45;      //用到摄像头识别时抬起的角度
const long wrist_grab_angle = 59;
const long wrist_place_angle = 225;
const long wrist_camera_angle = 25;
const int delaytime = 500;
const int servoDelay = 10;
const long wrist_hold_angle=140; //两次连续夹取之间腕部停驻的角度（避免打到地上的和车上的物料
const long arm_release_angle=-10;//放置的位置
const long arm_bigRise_angle=60;
const long wrist_release_angle=50;

const long arm_moving_angle =20;  //行走过程中为了平衡重心...
const long wrist_moving_angle= 24;

void Grab(char ID)
{
  switch (ID)
  {
  case 1:
    top.turnTo(1);
    Serial.println("1. turn wrist.");
    top.moveWrist(wrist_grab_angle);
    delay(delaytime);
    Serial.println("2. move arms down.");
    Serial.println("moving...");

    //调速，todo:需要改起始角度的逻辑
    for (int i = ARM_MAX_ANGLE; i >= arm_grab_angle; i--)
    {
      //Serial.println(i);
      top.moveArm(i);
      delay(servoDelay);
    }
    //top.moveArm(-7);
    delay(delaytime);
    Serial.println("3. grab!"); //夹取
    top.grabIt();
    delay(delaytime);

    Serial.println("4. rise arms."); //提一个小角度便于越过干涉
    top.moveArm(arm_smallRise_angle);
    delay(delaytime);

    Serial.println("5. turn wrist."); //放置
    top.moveWrist(wrist_place_angle);
    delay(delaytime);
    Serial.println("6. down arms.");
    top.moveArm(arm_place_angle);
    delay(delaytime);
    Serial.println("7. place.");
    top.loosenIt();
    delay(delaytime);

    Serial.println("8. rise arms.");  //准备下一次夹取
    top.moveArm(arm_smallRise_angle);
    delay(delay);
    Serial.println("9. turn wrist."); 
    top.moveWrist(wrist_hold_angle);  //转到中间的角度
    
    //整点骚操作（伪时序配合
    delay(250);
    top.turnTo((char)2);    //转到2号盘

    //等底盘移到下一个位置
    break;
  case 2:
    top.moveWrist(wrist_grab_angle);
    delay(delaytime);
    //2.手臂放下
    top.moveArm(arm_grab_angle);
    delay(delaytime);
    //3.夹取
    top.grabIt();
    delay(delaytime);
    //4.放
    top.moveArm(arm_smallRise_angle);
    delay(delaytime);
    top.moveWrist(wrist_place_angle);
    delay(delaytime);
    top.moveArm(arm_place_angle);
    delay(delaytime);
    top.loosenIt();
    delay(delaytime);

    top.moveArm(arm_smallRise_angle);
    delay(delaytime); 
    top.moveWrist(wrist_hold_angle);  //转到中间的角度
    
    //整点骚操作（伪时序配合
    delay(250);
    top.turnTo((char)0);    //转到中间

    //wait for next grab...
    break;
  case 3:
      //1.腕部转到夹取位置
    top.moveWrist(wrist_grab_angle);
    delay(delaytime);
    //2.手臂放下
    top.moveArm(arm_grab_angle);
    delay(delaytime);
    //3.夹取
    top.grabIt();
    delay(delaytime);
    break;
  default:
    break;
  }
}

// void firstGrab()
// {
//   //任务编号判断（待写）

//   //任务内容
//   Serial.println("1. turn wrist.");
//   top.moveWrist(wrist_grab_angle);
//   delay(delaytime);
//   Serial.println("2. move arms down.");
//   Serial.println("moving...");

//   //调速，todo:需要改起始角度的逻辑
//   for (int i = ARM_MAX_ANGLE; i >= arm_grab_angle; i--)
//   {
//     //Serial.println(i);
//     top.moveArm(i);
//     delay(servoDelay);
//   }
//   //top.moveArm(-7);
//   delay(delaytime);
//   Serial.println("3. grab!"); //夹取
//   top.grabIt();
//   delay(delaytime);

//   Serial.println("4. rise arms."); //提一个小角度便于越过干涉
//   top.moveArm(arm_smallRise_angle);
//   delay(delaytime);

//   Serial.println("5. turn wrist."); //放置
//   top.moveWrist(wrist_place_angle);
//   delay(delaytime);
//   Serial.println("6. down arms.");
//   top.moveArm(arm_place_angle);
//   delay(delaytime);
//   Serial.println("7. place.");
//   top.loosenIt();
//   delay(delaytime);

//   Serial.println("8. rise arms.");  //准备下一次夹取
//   top.moveArm(arm_smallRise_angle);
//   delay(delay);
//   Serial.println("9. turn wrist."); 
//   top.moveWrist(wrist_hold_angle);  //转到中间的角度
  
//   //整点骚操作（伪时序配合
//   delay(250);
//   top.turnTo((char)2);    //转到2号盘

//   //等底盘移到下一个位置
// }

// /**
//  * @brief 夹取第二个物料
//  * **********************************
//  * 调用该函数时各部分的预期状态：
//  * ** armAngle=arm_smallRise_angle;
//  * ** wristAngle=wrist_hold_angle;
//  * ** isGrab=false;
//  * ** platformID=2
//  * **********************************
//  */
// void secondGrab()
// {
//   //1.腕部转到夹取位置
//   top.moveWrist(wrist_grab_angle);
//   delay(delaytime);
//   //2.手臂放下
//   top.moveArm(arm_grab_angle);
//   delay(delaytime);
//   //3.夹取
//   top.grabIt();
//   delay(delaytime);
//   //4.放
//   top.moveArm(arm_smallRise_angle);
//   delay(delaytime);
//   top.moveWrist(wrist_place_angle);
//   delay(delaytime);
//   top.moveArm(arm_place_angle);
//   delay(delaytime);
//   top.loosenIt();
//   delay(delaytime);

//   top.moveArm(arm_smallRise_angle);
//   delay(delaytime); 
//   top.moveWrist(wrist_hold_angle);  //转到中间的角度
  
//   //整点骚操作（伪时序配合
//   delay(250);
//   top.turnTo((char)0);    //转到中间

//   //wait for next grab...
// }

// /**
//  * @brief 第三次夹取，
//  * **************************************
//  * ******* 此时各部分的预期状态：**********
//  * ** armAngle=arm_smallRise_angle;
//  * ** wristAngle=wrist_hold_angle;
//  * ** isGrab=false;
//  * **platformID=0;
//  * ***************************************
//  */
// void thirdGrab()
// {
//   //1.腕部转到夹取位置
//   top.moveWrist(wrist_grab_angle);
//   delay(delaytime);
//   //2.手臂放下
//   top.moveArm(arm_grab_angle);
//   delay(delaytime);
//   //3.夹取
//   top.grabIt();
//   delay(delaytime);
  
//   //考虑就这样一直拿着。。。
// }

/**
 * @brief 放物料
 * 
 * @param ID 物料的ID，对应此时盘上的（1，2）以及拿着的（0）
 */
void Place(char ID)
{
    switch (ID)
    {
    case 0: //默认拿着的
        top.turnTo(0);
        top.moveWrist(wrist_release_angle);
        top.moveArm(arm_release_angle,servoDelay,false);
     
        delay(delaytime);
        top.loosenIt();
        delay(delaytime);
        //抬升到下一次的准备位置
        // top.moveArm(arm_bigRise_angle);
        // //top.moveWrist(wrist_hold_angle);
        // delay(delaytime);
        break;
    case 1:
        top.turnTo(1);
        top.loosenIt();
        top.moveArm(arm_bigRise_angle); //前往不干涉的位置
        delay(150);
        top.moveWrist(wrist_place_angle); //转到取件的位置
        delay(150);
        top.moveArm(arm_place_angle,servoDelay,false);  //机械臂向下到达取件位置
        top.grabIt();
        delay(delaytime);
        top.moveArm(arm_bigRise_angle);
        delay(delaytime);
        top.moveWrist(wrist_hold_angle);  //防止干涉
        top.turnTo(0);
        top.moveArm(arm_release_angle,servoDelay,false);
        top.moveWrist(wrist_release_angle);
        delay(1000);
        top.loosenIt();
        // delay(1000);
        // top.moveArm(arm_bigRise_angle);
        // delay(delaytime);

        break;
    case 2:
        top.turnTo(2);
         top.loosenIt();
        top.moveArm(arm_bigRise_angle);
        delay(delaytime);
        top.moveWrist(wrist_place_angle);
        delay(delaytime);
        top.moveArm(arm_place_angle,servoDelay,false);
        top.grabIt();
        delay(delaytime);
        top.moveArm(arm_bigRise_angle);
        delay(delaytime);
        top.moveWrist(wrist_hold_angle);
         top.turnTo(0);
        top.moveArm(arm_release_angle,servoDelay,false);
        top.moveWrist(wrist_release_angle);
        delay(delaytime);
        top.loosenIt();
        break;

    default:
        break;
    }
}

inline bool CameraState()
{
  top.moveArm(arm_camera_angle,servoDelay,true);
  top.moveWrist(wrist_camera_angle);
  delay(delaytime);
  return true;
}

inline bool ArmWait()
{
  top.moveArm(arm_bigRise_angle);
  delay(delaytime);
  top.moveWrist(wrist_hold_angle);
  delay(delaytime);
}

inline bool MovingState()
{
  top.moveArm(arm_moving_angle);
  top.moveWrist(wrist_moving_angle);
  delay(delaytime);
}