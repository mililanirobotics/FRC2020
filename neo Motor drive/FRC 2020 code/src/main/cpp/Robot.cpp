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

void Robot::RobotInit()
{
  m_chooser.SetDefaultOption(kAutoNameNotDirectLeft, kAutoNameNotDirectLeft);
  m_chooser.AddOption(kAutoNameStraight, kAutoNameStraight);
  m_chooser.AddOption(kAutoNameDiagonalLeft, kAutoNameDiagonalLeft);
  m_chooser.AddOption(kAutoNameNotDirectRight, kAutoNameNotDirectRight);
  m_chooser.AddOption(kAutoNameDiagonalRight, kAutoNameDiagonalRight);

  //m_controlScheme = new ZandersControlScheme(joyStickLeft, joyStickRight);
  //m_controlScheme = new MatthewPrimary(gamepad);
  m_controlScheme = new ArcadeControlScheme(gamepad);
  m_secondControlScheme = new MatthewSecondary(gamepadSecondaryControls);

  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  m_ahrs = new AHRS(frc::I2C::Port::kOnboard);
  rightBack.SetInverted(true);
  rightFront.SetInverted(true);
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

void Robot::AutoPathOne(bool sideOfField, double speed)
{
  m_ahrs->ZeroYaw();
  double angle = m_ahrs->GetAngle();
  if (sideOfField)
  {
    while (angle > -29 && IsAutonomous() && IsEnabled())
    {
      leftFront.Set(-0.5 * speed);
      rightFront.Set(0.5 * speed);
      angle = m_ahrs->GetAngle();
      frc::SmartDashboard::PutNumber("angles 70:", angle);
    }
  }
  else
  {
    while (angle < 29 && IsAutonomous() && IsEnabled())
    {
      leftFront.Set(0.5 * speed);
      rightFront.Set(-0.5 * speed);
      angle = m_ahrs->GetAngle();
      frc::SmartDashboard::PutNumber("angles 80:", angle);
    }
  }
  std::cout << "working" << std::endl;
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto limelight = inst.GetTable("limelight");
  double height = limelight->GetNumber("ty", 0.0);
  while (height < 2.08 && IsAutonomous() && IsEnabled())
  {
    double alignment = limelight->GetNumber("tx", 0.0);
    frc::SmartDashboard::PutNumber("alignment: ", alignment);
    double offsetAdjust = fabs(alignment * 0.03); //changes how much the alignment adjusts by 0.02
    if (alignment < 0)                            //turn left
    {
      leftFront.Set(0.4 * speed);
      rightFront.Set((0.4 + offsetAdjust) * speed);
    }
    else if (alignment > 0) //turn right
    {
      leftFront.Set((0.4 + offsetAdjust) * speed);
      rightFront.Set(0.4 * speed);
    }
    else
    {
      leftFront.Set(0.4 * speed);
      rightFront.Set(0.4 * speed);
    }
    height = limelight->GetNumber("ty", 0.0);
  }
  leftFront.Set(0);
  rightFront.Set(0);
}

double Robot::MotorConversion(double distance)
{
  double wheelCircumference = 18.84;                     // Wheel circumfrence
  double rotationAmount = distance / wheelCircumference; // Gets the distance the user wants to travel and turns it into the amount of rotations the motor has to move to reach it
  double gearboxRatio = 10.71;                           // Sets the gear box ratio for one wheel rotation you need to turn your motor 10.71 times
  double motorRotation = rotationAmount * gearboxRatio;  // turns the amount the wheel needs to rotate to how much the motor needs to rotate
  return motorRotation;
}

void Robot::AutoPathTwo(bool sideOfField, double speed) // not direct route
{
  m_ahrs->ZeroYaw();                                // Sets the Nav x to 0
  double angle = m_ahrs->GetAngle();                // Gets the angle the nav x is now
  double travelDistance = 60.8;                     // States the distance we need to travel
  travelDistance = MotorConversion(travelDistance); // Calls upon the function MotorConversions and gets the new value we have to move the motors

  if (sideOfField) // Checks to see which side the robot is placed the left or the right, if it true the robot needs to be on the right if it is false the robot is on the left side
  {
    while (angle > -60 && IsAutonomous() && IsEnabled()) // Checks to see if the robot is at a certain angle, if auto is selected and if it is enabled, if so then it goes through the while loop
    {
      leftFront.Set(-0.5 * speed);
      rightFront.Set(0.5 * speed);
      angle = m_ahrs->GetAngle();                       // updates the angle of the robot
      frc::SmartDashboard::PutNumber("angles:", angle); // returns the value of the angle to the smart dashboard
    }
  }
  else
  {
    while (angle < 60 && IsEnabled() && IsAutonomous()) // Checks to see if the robot is at a certain angle, if auto is selected and if it is enabled, if so then it goes through the while loop
    {
      leftFront.Set(0.5 * speed);
      rightFront.Set(-0.5 * speed);
      angle = m_ahrs->GetAngle();                       // updates the angle of the robot
      frc::SmartDashboard::PutNumber("angles:", angle); // returns the value of the angle to the smart dashboard
    }
  }
  leftFront.Set(0);            // Sets the motor power back to 0
  rightFront.Set(0);           // Sets the motor power back to 0
  leftEncoder.SetPosition(0);  // Sets the encoder value back to 0 for the left side motors
  rightEncoder.SetPosition(0); // Sets the encoder value back to 0 for the right side motors

  // Tells the robot to move a certain distance with the travel distance and the value of the left encoder
  while (travelDistance >= leftEncoder.GetPosition() && IsAutonomous() && IsEnabled())
  {
    leftFront.Set(0.5 * speed); // Sets the speed of the robot for moving
    rightFront.Set(0.5 * speed);
    frc::SmartDashboard::PutNumber("moved: ", leftEncoder.GetPosition()); // returns how much the robot moved into the smart dashboard
    std::cout << travelDistance << std::endl;                             // prints the travel distance the robot has to travel
  }

  leftFront.Set(0); // Sets the motor power back to 0
  rightFront.Set(0);

  if (sideOfField)
  {
    while (angle < 0 && IsAutonomous() && IsEnabled())
    {
      leftFront.Set(0.5 * speed);
      rightFront.Set(-0.5 * speed);
      angle = m_ahrs->GetAngle();
      frc::SmartDashboard::PutNumber("angles:", angle);
    }
  }
  else
  {
    while (angle > 0 && IsAutonomous() && IsEnabled())
    {
      leftFront.Set(-0.5 * speed);
      rightFront.Set(0.5 * speed);
      angle = m_ahrs->GetAngle();
      frc::SmartDashboard::PutNumber("angles:", angle);
    }
  }
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto limelight = inst.GetTable("limelight");
  double height = limelight->GetNumber("ty", 0.0);
  while (height < 2.09 && IsAutonomous() && IsEnabled())
  {
    double alignment = limelight->GetNumber("tx", 0.0);
    frc::SmartDashboard::PutNumber("alignment: ", alignment);
    double offsetAdjust = fabs(alignment * 0.03); //changes how much the alignment adjusts by 0.02
    if (alignment < 0)                            //turn left
    {
      leftFront.Set(0.4 * speed);
      rightFront.Set((0.4 + offsetAdjust) * speed);
    }
    else if (alignment > 0) //turn right
    {
      leftFront.Set((0.4 + offsetAdjust) * speed);
      rightFront.Set(0.4 * speed);
    }
    else
    {
      leftFront.Set(0.4 * speed);
      rightFront.Set(0.4 * speed);
    }
    height = limelight->GetNumber("ty", 0.0);
  }
  leftFront.Set(0);
  rightFront.Set(0);
}

void Robot::AutoPathThree(double speed)
{
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto limelight = inst.GetTable("limelight");

  double height = limelight->GetNumber("ty", 0.0);
  while (height < 1.09 && IsAutonomous() && IsEnabled())
  {
    double alignment = limelight->GetNumber("tx", 0.0);
    frc::SmartDashboard::PutNumber("height: ", height);
    double offsetAdjust = fabs(alignment * 0.03); //changes how much the alignment adjusts by 0.02
    if (alignment < 0)                            //turn left
    {
      leftFront.Set(0.4 * speed);
      rightFront.Set((0.4 + offsetAdjust) * speed);
    }
    else if (alignment > 0) //turn right
    {
      leftFront.Set((0.4 + offsetAdjust) * speed);
      rightFront.Set(0.4 * speed);
    }
    else
    {
      leftFront.Set(0.4 * speed);
      rightFront.Set(0.4 * speed);
    }
    height = limelight->GetNumber("ty", 0.0);
  }
  leftFront.Set(0);
  rightFront.Set(0);
}

void Robot::AutonomousInit()
{
  m_autoSelected = m_chooser.GetSelected();                      // grabs the option that was selected from the smart dashboard
  frc::SmartDashboard::PutString("auto Mode: ", m_autoSelected); // prints the auto path that was selected on the smart Dashboard
  std::cout << "Auto selected: " << m_autoSelected << std::endl; // Prints the auto path that was selected in the console
  m_ahrs->ZeroYaw();                                             // sets the Nav x back to 0
  leftBack.Follow(leftFront, false);                             // Sets the left back motor to follow the front motor
  rightBack.Follow(rightFront, false);                           // Sets the right back motor to follow the right motor
  double slowmode = 0.2;                                         // Limits the speed of the motor

  // Checks the input of the Smart Dashboard and selects the auto path from there
  if (m_autoSelected == kAutoNameDiagonalLeft) // turns a certain amount of degrees and goes to the bottom port
  {
    AutoPathOne(true, slowmode); // The true value states the robot is on the left
  }
  if (m_autoSelected == kAutoNameDiagonalRight) // turns a certain amount of degrees and goes to the bottom port
  {
    AutoPathOne(false, slowmode); // The false value states the robot is on the right side of the field
  }
  if (m_autoSelected == kAutoNameNotDirectLeft) // Goes diagnal to be in the center and goes head on to the bottom port
  {
    AutoPathTwo(true, slowmode);
  }
  if (m_autoSelected == kAutoNameNotDirectRight) // Goes diagnal to be in the center and goes head on to the bottom port
  {
    AutoPathTwo(false, slowmode);
  }
  if (m_autoSelected == kAutoNameStraight)
  {
    AutoPathThree(slowmode);
  }
  std::cout << "you are leaving auto init" << std::endl;
}

void Robot::AutonomousPeriodic()
{
  return;
}
#ifdef TELEOPENABLED
void Robot::DrivePower()
{
  //Grabs the input from the gamepads for tank drive
  m_controlScheme->getMotorPower(leftPower, rightPower);
  m_controlScheme->AutoAlign(leftPower, rightPower);
  // sets motors power according to the input from the left joystick and the right joystick
  leftFront.Set(leftPower);
  leftBack.Set(leftPower);
  rightFront.Set(rightPower);
  rightBack.Set(rightPower);
  frc::SmartDashboard::PutNumber("left", leftPower);
  frc::SmartDashboard::PutNumber("right", rightPower);
}
void Robot::LiftScrew()
{
  // gets the power to set the motor to
  double speed = m_controlScheme->ArmLift();
  // Sets power to the arm lift motor
  linearAch.Set(ControlMode::PercentOutput, speed);
  frc::SmartDashboard::PutNumber("speed", speed);
}
void Robot::Winch() // sets the power for the winch
{
  winchSpeed = m_secondControlScheme->Winch(); // returns the value the winch attribute gives from secondControlScheme

  // Sets the power of the winch motors
  winchLeft.Set(ControlMode::PercentOutput, winchSpeed);
  winchRight.Set(ControlMode::PercentOutput, winchSpeed);
  frc::SmartDashboard::PutNumber("Winch speed", winchSpeed);
}

void Robot::IntakePosition() // used to set the pistons value
{
  m_secondControlScheme->pivot(upPiston, downPiston); //grabs values from the pivot attribute of secondControlScheme

  // Sets the piston to open or not depending on the position its suppose to be in
  leftUpPiston.Set(upPiston);
  leftDownPiston.Set(downPiston);
  rightDownPiston.Set(downPiston);
  rightUpPiston.Set(upPiston);
}
void Robot::IntakePower()
{
  double power = m_secondControlScheme->Intake(); // calls upon the Intake attribute of the m_secondControlScheme object

  // Sets the power of the Intake motors to the power
  intakeLeft.Set(ControlMode::PercentOutput, power);
  intakeRight.Set(ControlMode::PercentOutput, power);
}
#endif // teleop enabled
void Robot::TeleopInit()
{
#ifdef TELEOPENABLED
  //Initializes the motors for winch setting what the high and low values are
  winchLeft.ConfigPeakOutputForward(1, 10);
  winchLeft.ConfigPeakOutputReverse(-1, 10);
  winchLeft.SetNeutralMode(NeutralMode::Brake);

  winchRight.ConfigPeakOutputForward(1, 10);
  winchRight.ConfigPeakOutputReverse(-1, 10);
  winchRight.SetNeutralMode(NeutralMode::Brake);

  // Initialiezes the motors setting the highes and lowest values for the intake
  intakeLeft.ConfigPeakOutputForward(1, 10);
  intakeLeft.ConfigPeakOutputReverse(-1, 10);
  intakeLeft.SetNeutralMode(NeutralMode::Brake);

  intakeRight.ConfigPeakOutputForward(1, 10);
  intakeRight.ConfigPeakOutputReverse(-1, 10);
  intakeRight.SetInverted(motorcontrol::InvertType::InvertMotorOutput); //sets the motor inverted
  intakeRight.SetNeutralMode(NeutralMode::Brake);

  //Initializes the motors for linear motor setting what the high and low values are
  linearAch.ConfigPeakOutputForward(1, 10);
  linearAch.ConfigPeakOutputReverse(-1, 10);
  linearAch.SetNeutralMode(NeutralMode::Brake);

  // turns the compressor on
  compressor.SetClosedLoopControl(true);

  // sets the nav x to 0
  m_ahrs->ZeroYaw();
#endif
}

void Robot::TeleopPeriodic()
{
  DrivePower();     // Calls upon the drive motors to set power
  LiftScrew();      // Calls upon the lift motor to set power
  Winch();          // Calls upon the winch motor to set the power
  IntakePower();    // Calls upon the Intake motors to set the power
  IntakePosition(); // Calls upon the solenoids to their positions
  //https://www.kauailabs.com/public_files/navx-mxp/apidocs/c++/class_a_h_r_s.html

  //double angle = m_ahrs->GetAngle();
  //frc::SmartDashboard::PutNumber("angle Of robot: ", angle);
}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
