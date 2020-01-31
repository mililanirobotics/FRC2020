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

void Robot::TeleopInit() {
  topConveyorBeltOne.ConfigPeakOutputForward(1.0, 10);
  topConveyorBeltOne.ConfigPeakOutputReverse(-1.0, 10);
  topConveyorBeltOne.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);

  //bottomConveyorBeltOne.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, 10);

  topConveyorBeltTwo.ConfigPeakOutputForward(1.0, 0);
  topConveyorBeltTwo.ConfigPeakOutputReverse(-1.0, 0);
  topConveyorBeltTwo.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
  
  //bottomConveyorBeltTwo.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, 12);
}

void Robot::TeleopPeriodic() {
  conveyorBeltOnePower = gamepad.GetRawAxis(1);
  conveyorBeltTwoPower = gamepad.GetRawAxis(5);

  topConveyorBeltOne.Set(ControlMode::PercentOutput, conveyorBeltOnePower);
  topConveyorBeltTwo.Set(ControlMode::PercentOutput, -conveyorBeltOnePower);

  std:: cout << topConveyorBeltOne.GetMotorOutputPercent() << std::endl;
  std::cout << "left:" << conveyorBeltOnePower << std::endl;
  std::cout << "right:" << conveyorBeltTwoPower << std::endl;
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
