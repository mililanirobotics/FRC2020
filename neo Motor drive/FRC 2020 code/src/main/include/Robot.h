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
#include <rev/CANSparkMax.h>
#include <frc/Joystick.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void TankDrivePower();
  void ArcadeDrivePower();
  void CameraDetection();

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  frc::Joystick gamepad{0};

  rev::CANSparkMax leftFront{10, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax leftBack{11, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax rightFront{12, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax rightBack{13, rev::CANSparkMax::MotorType::kBrushless};
  
  double leftPower; // used for the tank drive
  double rightPower; // used for the tank drive
  double drivePower; // used for arcade drive
};
