/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTable.h"
#include <math.h>

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::CameraDetection()
{
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto limelight = inst.GetTable("limelight");

  limelight->PutNumber("stream", 0);
}

void Robot::ArcadeDrivePower()
{
  double forwardBackward = -(gamepad.GetRawAxis(1));
  double leftRight = gamepad.GetRawAxis(4);
  if (fabs(forwardBackward) >= 0.05 && fabs(leftRight) <= 0.05)
  {
    leftFront.Set(forwardBackward);
    leftBack.Set(forwardBackward);
    rightFront.Set(forwardBackward);
    rightBack.Set(forwardBackward);
    
  }
  else if (fabs(forwardBackward) >= 0.05 && fabs(leftRight) >= 0.05)
  {
    std::cout << "IN" << std::endl;
    if (forwardBackward > 0)
    {
      drivePower = forwardBackward - fabs(leftRight);
    }
    else if(forwardBackward < 0){
      drivePower = forwardBackward + fabs(leftRight);
    }
    if (leftRight > 0){
      leftFront.Set(forwardBackward);
      leftBack.Set(forwardBackward);
      rightFront.Set(drivePower);
      rightBack.Set(drivePower);
    }
    else if (leftRight < 0){
      leftFront.Set(drivePower);
      leftBack.Set(drivePower);
      rightFront.Set(forwardBackward);
      rightBack.Set(forwardBackward);
    }

  }
  else{
    leftFront.Set(0);
    leftBack.Set(0);
    rightFront.Set(0);
    rightBack.Set(0);
  }
  
    std::cout << "leftFront: " << leftFront.Get() << std::endl;
    std::cout << "leftBack: " << leftBack.Get() << std::endl;
    std::cout << "rightFront: " << rightFront.Get() << std::endl;
    std::cout << "rightBack: " << rightBack.Get() << std::endl;
}

void Robot::TankDrivePower() {
  leftPower = -(gamepad.GetRawAxis(1));
  rightPower = (gamepad.GetRawAxis(5));
  leftFront.Set(leftPower);
  leftBack.Set(leftPower);
  rightFront.Set(rightPower);
  rightBack.Set(rightPower);
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
  //TankDrivePower();
  ArcadeDrivePower();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
