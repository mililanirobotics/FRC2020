#pragma once

#include <frc/Joystick.h>
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTable.h"

class PrimaryControlScheme //Primary control scheme setup
{
    public: 
    virtual void getMotorPower(double& leftPower, double& rightPower) = 0;
    virtual void AutoAlign(double& leftPower, double& rightPower) = 0;
    virtual double ArmLift() = 0;
};
class TankControlScheme:public PrimaryControlScheme //Tank drive setup
{
    public:
    virtual void getMotorPower(double& leftPower, double& rightPower);
    virtual void AutoAlign(double& leftPower, double& rightPower);
    virtual double ArmLift();
    TankControlScheme(frc::Joystick &gamepad);
    frc::Joystick& m_gamepad;
};
class MatthewPrimary: public TankControlScheme //Matthew's control scheme
{
    public:
    virtual void AutoAlign(double& leftPower, double& rightPower);
    virtual double ArmLift();
    MatthewPrimary(frc::Joystick &gamepad);
};
class KentPrimary: public TankControlScheme //Kent's control scheme
{
    public:
    virtual void AutoAlign(double& leftPower, double& rightPower);
    virtual double ArmLift();
    KentPrimary(frc::Joystick &gamepad);
};
class ArcadeControlScheme:public PrimaryControlScheme //Arcade control scheme setup
{
    public:
    virtual void getMotorPower(double& leftPower, double& rightPower);
    ArcadeControlScheme(frc::Joystick& gamepad);
    frc::Joystick& m_gamepad;
    virtual double ArmLift();
    virtual void AutoAlign(double& leftPower, double& rightPower);
};
class ZandersControlScheme:public PrimaryControlScheme //Zander's control scheme
{
    public:
    virtual void getMotorPower(double& leftPower, double& rightPower);
    ZandersControlScheme(frc::Joystick& joyStickLeft, frc::Joystick& joyStickRight);
    frc::Joystick& m_joyStickLeft;
    frc::Joystick& m_joyStickRight;
    virtual double ArmLift();
    virtual void AutoAlign(double& leftPower, double& rightPower);
};
class SecondaryControl //Secondary control scheme
{
    public:
    virtual double Winch() = 0;
    virtual void Intake(double& ShooterPower, double& FeederPower) = 0;
    virtual void pivot(bool& firstPiston) = 0;

};
class MatthewSecondary:public SecondaryControl //Matthew's secondary control scheme
{
    public:
    MatthewSecondary(frc::Joystick& gamepad);
    frc::Joystick& m_gamepad;
    virtual double Winch();
    void Intake(double& ShooterPower, double& FeederPower);
    virtual void pivot(bool& firstPiston);
};
class ZanderSecondary:public SecondaryControl //Zander's secondary control scheme
{
    public:
    ZanderSecondary(frc::Joystick& gamepad);
    frc::Joystick& m_gamepad;
    virtual double Winch();
    void Intake(double& ShooterPower, double& FeederPower);
    virtual void pivot(bool& firstPiston);
};
class TroyAndTariqSecondary:public SecondaryControl //Troy's secondary control scheme
{
    public:
    TroyAndTariqSecondary(frc::Joystick& gamepad);
    frc::Joystick& m_gamepad;
    virtual double Winch();
    void Intake(double& ShooterPower, double& FeederPower);
    virtual void pivot(bool& firstPiston);
};
class KentSecondary:public SecondaryControl //Kent's secondary control scheme
{
    public:
    KentSecondary(frc::Joystick& gamepad);
    frc::Joystick& m_gamepad;
    virtual double Winch();
    void Intake(double& ShooterPower, double& FeederPower);
    virtual void pivot(bool& firstPiston);
};