/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <rev/CANPIDController.h>
#include <rev/CANSparkMax.h>
#include <rev/CANError.h>

#include <ctre/Phoenix.h>

#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

class Robot:public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  rev::CANSparkMax NeoMotor{10, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANPIDController PIDController{NeoMotor};

  frc::Joystick gamepad{1};

  double motorPowerOne = 0.0;
  double motorPowerTwo = 0.0;
  double joystick;

  TalonSRX LBack{11};
  TalonSRX Roller{17};
};
