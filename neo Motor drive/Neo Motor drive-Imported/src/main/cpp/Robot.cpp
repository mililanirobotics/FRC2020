/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

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
    leftFront.Set (leftPower * -0.1);
    leftBack.Set (leftPower * -0.1);
    rightFront.Set (rightPower * 0.1);
    rightBack.Set (rightPower * 0.1);
    //wait
    leftFront.Set (leftPower);
    leftBack.Set (leftPower);
    rightFront.Set (rightPower);
    rightBack.Set (rightPower);
    leftFront.Set (leftPower * 0.4);
    leftBack.Set (leftPower * 0.4);
    rightFront.Set (rightPower * -0.4);
    rightBack.Set (rightPower * -0.4);
  } else {
    // Default Auto goes here
  }
}


void Robot::AutonomousPeriodic() {
   if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } 
  else {
    // Default Auto goes here
  }
}

void Robot::SetPower(double leftpower, double rightpower) {
  // leftFront.Set(leftpower * .7);
  // leftBack.Set(leftpower * .7);
  // rightFront.Set(rightpower * .7);
  // rightBack.Set(rightpower * .7);
}

void Robot::IntakeInit(){}

void Robot::TeleopInit() {}

void Robot::pivotMechanism() {
  #ifdef SINGLESOLENOID
  if (gamepad.GetRawButton(1)) {
    pivotLeftPiston.Set(true);
  }
  else if (gamepad.GetRawButton(1) == false) {
    pivotLeftPiston.Set(false);
  }
  if (gamepad.GetRawButton(2)) {
    pivotRightPiston.Set(true);
  }
  else if (gamepad.GetRawButton(2) == false) {
    pivotRightPiston.Set(false);
  }
  #else
  if(gamepad.GetRawButton(1)){
    pivotLeftPiston.Set(frc::DoubleSolenoid::kForward);
  }
  else if(gamepad.GetRawButton(1)){ 
    pivotLeftPiston.Set(frc::DoubleSolenoid::kReverse);
  }
  if(gamepad.GetRawButton(2)){
    pivotRightPiston.Set(frc::DoubleSolenoid::kForward);
  }
  else if(gamepad.GetRawButton(2)){
    pivotRightPiston.Set(frc::DoubleSolenoid::kReverse);
  }
  #endif
}

void Robot::TeleopPeriodic() {
  leftPower = -(gamepad.GetRawAxis(1));
  rightPower = (gamepad.GetRawAxis(5));
  rightTrigger = (gamepad.GetRawAxis(3));

  if (rightTrigger == 1)
  {
  intakeLeft.Set(ControlMode::PercentOutput, 1);
  intakeRight.Set(ControlMode::PercentOutput, -1);
  std::cout << "1";
  }
  else
  {
  intakeLeft.Set(ControlMode::PercentOutput, 0);
  intakeRight.Set(ControlMode::PercentOutput, 0);
  std::cout << "0";
  }
  
  pivotMechanism();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
