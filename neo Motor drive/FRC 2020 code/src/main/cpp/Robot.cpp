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
  //m_controlScheme = new TariqPrimary(gamepad);
  //m_secondControlScheme = new MatthewSecondary(gamepadSecondaryControls);

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
  while( height < 2.08 && IsAutonomous() && IsEnabled()){
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
  double wheelCircumference = 18.84;
  double rotationAmount = distance / wheelCircumference;
  double gearboxRatio = 10.71;
  double motorRotation = rotationAmount * gearboxRatio;
  return motorRotation;
}

void Robot::AutoPathTwo(bool sideOfField, double speed)
{
  m_ahrs->ZeroYaw();
  double angle = m_ahrs->GetAngle();
  double travelDistance = 60.8;
  travelDistance = MotorConversion(travelDistance);

  if (sideOfField)
  {
    while (angle > -60 && IsAutonomous() && IsEnabled())
    {
      leftFront.Set(-0.5 * speed);
      rightFront.Set(0.5 * speed);
      angle = m_ahrs->GetAngle();
      frc::SmartDashboard::PutNumber("angles:", angle);
    }
  }
  else
  {
    while (angle < 60 && IsEnabled() && IsAutonomous())
    {
      leftFront.Set(0.5 * speed);
      rightFront.Set(-0.5 * speed);
      angle = m_ahrs->GetAngle();
      frc::SmartDashboard::PutNumber("angles:", angle);
    }
  }
  leftFront.Set(0);
  rightFront.Set(0);
  leftEncoder.SetPosition(0);
  rightEncoder.SetPosition(0);
  while (travelDistance >= leftEncoder.GetPosition() && IsAutonomous() && IsEnabled())
  {
    leftFront.Set(0.5 * speed);
    rightFront.Set(0.5 * speed);
    frc::SmartDashboard::PutNumber("moved: ", leftEncoder.GetPosition());
    std::cout << travelDistance << std::endl;
  }
  std::cout << "out" << std::endl;
  leftFront.Set(0);
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
  while(height < 2.09 && IsAutonomous() && IsEnabled()){
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

void Robot::AutoPathThree(double speed) {
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto limelight = inst.GetTable("limelight");

  double height = limelight->GetNumber("ty", 0.0);
  while(height < 1.09 && IsAutonomous() && IsEnabled()){
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
  m_autoSelected = m_chooser.GetSelected();
  frc::SmartDashboard::PutString("auto Mode: ", m_autoSelected);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;
  m_ahrs->ZeroYaw();
  leftBack.Follow(leftFront, false);
  rightBack.Follow(rightFront, false);
  double slowmode = 0.2;
  if (m_autoSelected == kAutoNameDiagonalLeft)
  {
    AutoPathOne(true, slowmode);
  }
  if (m_autoSelected == kAutoNameDiagonalRight)
  {
    AutoPathOne(false, slowmode);
  }
  if (m_autoSelected == kAutoNameNotDirectLeft)
  {
    AutoPathTwo(true, slowmode);
  }
  if (m_autoSelected == kAutoNameNotDirectRight)
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
  if (m_autoSelected == kAutoNameStraight)
  {
  }
  else if (m_autoSelected == kAutoNameNotDirectLeft) {
  }
  else if (m_autoSelected == kAutoNameNotDirectRight) {
  }
  else if (m_autoSelected == kAutoNameDiagonalLeft) {
  }
  else if (m_autoSelected == kAutoNameDiagonalRight) {
    
  }
  
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
  double speed = m_controlScheme->ArmLift();
  linearAch.Set(ControlMode::PercentOutput, speed);
  frc::SmartDashboard::PutNumber("speed", speed);
}
void Robot::Winch() // sets the power for the winch
{
  winchSpeed = m_secondControlScheme->Winch(); // returns the value the winch attribute gives from secondControlScheme

  winchLeft.Set(ControlMode::PercentOutput, winchSpeed);
  winchRight.Set(ControlMode::PercentOutput, winchSpeed);
  frc::SmartDashboard::PutNumber("Winch speed", winchSpeed);
}

void Robot::IntakePower() // used to set the pistons value
{
  m_secondControlScheme->pivot(upPiston, downPiston); //grabs values from the pivot attribute of secondControlScheme

  leftUpPiston.Set(upPiston);
  leftDownPiston.Set(downPiston);
  rightDownPiston.Set(downPiston);
  rightUpPiston.Set(upPiston);
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
  intakeRight.SetNeutralMode(NeutralMode::Brake);

  //Initializes the motors for linear motor setting what the high and low values are
  linearAch.ConfigPeakOutputForward(1, 10);
  linearAch.ConfigPeakOutputReverse(-1, 10);
  linearAch.SetNeutralMode(NeutralMode::Brake);

  // turns the compressor on
  compressor.SetClosedLoopControl(true);

  m_ahrs->ZeroYaw();
  #endif
}

void Robot::TeleopPeriodic()
{
  DrivePower();
  LiftScrew();
  Winch();
  IntakePower();
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
