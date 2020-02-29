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
#include <ctre/Phoenix.h>
#include "ControlScheme.hpp"
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <frc/Joystick.h>
#include "AHRS.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  double MotorConversion(double distance);
  void AutoPathOne(bool sideOfField, double speed);
  void AutoPathTwo(bool sideOfField, double speed);
  void AutoPathThree(double speed);
  void DrivePower();
  void LiftScrew();
  void IntakePosition();
  void IntakePower();
  void Winch();

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDiagonalLeft = "Option diagnal Left Side";
  const std::string kAutoNameDiagonalRight = "Option diagnal Right Side";
  const std::string kAutoNameNotDirectLeft = "Option 2 Left Side";
  const std::string kAutoNameNotDirectRight = "Option 2 Right Side";
  const std::string kAutoNameStraight = "Center";
  std::string m_autoSelected;

  #define TELEOPENABLED

  #ifdef TELEOPENABLED
  frc::Joystick gamepad{0};
  frc::Joystick joyStickLeft{1};
  frc::Joystick joyStickRight{2};
  frc::Joystick gamepadSecondaryControls{3};


  frc::Compressor compressor{0};
  frc::Solenoid rightUpPiston{0};
  frc::Solenoid rightDownPiston{1};
  frc::Solenoid leftUpPiston{2};
  frc::Solenoid leftDownPiston{3};
  #endif

  rev::CANSparkMax leftFront{10, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax leftBack{11, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax rightFront{12, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax rightBack{13, rev::CANSparkMax::MotorType::kBrushless};

  rev::CANEncoder leftEncoder{leftFront, rev::CANEncoder::EncoderType::kHallSensor, 42};
  rev::CANEncoder rightEncoder{rightFront, rev::CANEncoder::EncoderType::kHallSensor, 42};

  #ifdef TELEOPENABLED
  TalonSRX linearAch{14};

  TalonSRX winchLeft{15};
  TalonSRX winchRight{16};

  TalonSRX intakeLeft{17};
  TalonSRX intakeRight{18};

  PrimaryControlScheme* m_controlScheme;
  SecondaryControl* m_secondControlScheme;
  #endif
  AHRS* m_ahrs;
  
  double leftPower; // used for the tank drive
  double rightPower; // used for the tank drive
  double drivePower; // used for arcade drive
  double forwardBackward; //used for arcade drive
  double leftRight; //used for arcade drive
  double winchSpeed; 
  bool upPiston;
  bool downPiston;
};
