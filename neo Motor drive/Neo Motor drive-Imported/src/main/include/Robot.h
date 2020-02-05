
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Joystick.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>

#include <rev/CANSparkMax.h>

#include <ctre/Phoenix.h>
#define SINGLESOLENOID

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void IntakeInit();
  void SetPower(double leftpower, double rightPower);

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  frc::Joystick gamepad{0};
  frc::Compressor compressor{0};

  #ifdef SINGLESOLENOID
  frc::Solenoid pivotOnePiston{1,0};
  frc::Solenoid pivotTwoPiston{1,1};
  frc::Solenoid pivotThreePiston{1,2};
  frc::Solenoid pivotFourPiston{1,3};
  #else
  frc::DoubleSolenoid pivotOnePiston{1,0};
  frc::DoubleSolenoid pivotTwoPiston{1,1};
  frc::DoubleSolenoid pivotThreePiston{1,2};
  frc::DoubleSolenoid pivotFourPiston{1,3};
  #endif

  rev::CANSparkMax leftFront{10, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax leftBack{11, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax rightFront{12, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax rightBack{13, rev::CANSparkMax::MotorType::kBrushless};

  TalonSRX intakeLeft {14};
  TalonSRX intakeRight {15};
  
  void pivotMechanism();

  double leftPower;
  double rightPower;
  double rightTrigger;
};
