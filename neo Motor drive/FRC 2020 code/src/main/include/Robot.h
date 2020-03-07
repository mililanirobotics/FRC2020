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

class Robot : public frc::TimedRobot
{
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

  double MotorConversion(double distance);                                    // This converts inches into rotations for the motor
  void AutoPathOne(bool sideOfField, double speed);                           // Direct path to target
  void AutoPathTwo(bool sideOfField, double speed);                           // Travels diagnally and directly horizontal to the target
  void AutoPathThree(double speed);                                           // Horizontal path to target
  void DrivePower();                                                          // States the power for the drive motors during teleop
  void IntakePosition();                                                      // Pivots the intake: piston controlled
  void IntakePower();                                                         // Sets the power of the intake motors
  void Winch();                                                               // Sets a static power for the motor and the motor can only go one way
  void LiftScrew();                                                           // States the power of the lift motor
  static void Limelight(double speed, double &leftPower, double &rightPower); // Used for auto alignment
  void AutoTurn(double degreesTurned, double speed);                          //used to turn the robot to a set position
  void AutoAlign(double speed);                                               // Uses the auto alignment and adds the ty value

private:
  // Allows the user to select which auto they want in the smart dashboad
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDiagonalLeft = "Option diagnal Left Side";
  const std::string kAutoNameDiagonalRight = "Option diagnal Right Side";
  const std::string kAutoNameNotDirectLeft = "Option 2 Left Side";
  const std::string kAutoNameNotDirectRight = "Option 2 Right Side";
  const std::string kAutoNameStraight = "Center";
  std::string m_autoSelected;

// Used to mass comment out things
#define TELEOPENABLED

  // Controllers that we could have used
  frc::Joystick gamepad{0};
  frc::Joystick joyStickLeft{1};
  frc::Joystick joyStickRight{2};
  frc::Joystick gamepadSecondaryControls{3};

  frc::Compressor compressor{0};  // defines the compress
  frc::Solenoid rightPiston{0}; // defines the right piston
  frc::Solenoid leftPiston{1};

  //Defines the Neo motors we are using for the drive
  rev::CANSparkMax leftFront{10, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax leftBack{11, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax rightFront{12, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax rightBack{13, rev::CANSparkMax::MotorType::kBrushless};

  // Defines the Neo motor encoders
  rev::CANEncoder leftEncoder{leftFront, rev::CANEncoder::EncoderType::kHallSensor, 42};
  rev::CANEncoder rightEncoder{rightFront, rev::CANEncoder::EncoderType::kHallSensor, 42};

  // Defines the Neo Motors PID Controller
  rev::CANPIDController leftPIDController{leftFront};
  rev::CANPIDController rightPIDController{rightFront};

#ifdef ADDLIFT
  TalonSRX linearAch{14}; // lift motor

  TalonSRX winchLeft{15}; // defines the winch motors
  TalonSRX winchRight{16};
#endif

  TalonSRX shooterMotor{17}; // defines the intake motors
  TalonSRX feederMotor{18};

  PrimaryControlScheme *m_controlScheme;   // calls upon the control library we created for each driver
  SecondaryControl *m_secondControlScheme; // calls upon the control library we created for the secondary driver
  
  AHRS *m_ahrs; // This defines the NAV X or gyro we use

  double leftPower;       // used for the tank drive
  double rightPower;      // used for the tank drive
  double drivePower;      // used for arcade drive
  double forwardBackward; // used for arcade drive
  double leftRight;       // used for arcade drive
  double winchSpeed;      // Sets the winch speed
  bool pivot;
  double fPower;
  double sPower;
};
