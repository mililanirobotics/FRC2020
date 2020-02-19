#include <frc/Joystick.h>
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTable.h"

class PrimaryControlScheme 
{
    public: 
    virtual void getMotorPower(double& leftPower, double& rightPower) = 0;
    virtual void AutoAlign(double& leftPower, double& rightPower) = 0;
    virtual double ArmLift() = 0;
};

class TankControlScheme:public PrimaryControlScheme
{
    public:
    virtual void getMotorPower(double& leftPower, double& rightPower);
    virtual void AutoAlign(double& leftPower, double& rightPower);
    virtual double ArmLift();
    TankControlScheme(frc::Joystick &gamepad);
    frc::Joystick& m_gamepad;
};
class MatthewPrimary: public TankControlScheme
{
    public:
    virtual void AutoAlign(double& leftPower, double& rightPower);
    virtual double ArmLift();
    MatthewPrimary(frc::Joystick &gamepad);
};
class KentPrimary: public TankControlScheme
{
    public:
    virtual void AutoAlign(double& leftPower, double& rightPower);
    virtual double ArmLift();
    KentPrimary(frc::Joystick &gamepad);
};



class ArcadeControlScheme:public PrimaryControlScheme
{
    public:
    virtual void getMotorPower(double& leftPower, double& rightPower);
    ArcadeControlScheme(frc::Joystick& gamepad);
    frc::Joystick& m_gamepad;
    virtual double ArmLift();
    virtual void AutoAlign(double& leftPower, double& rightPower);
};



class ZandersControlScheme:public PrimaryControlScheme
{
    public:
    virtual void getMotorPower(double& leftPower, double& rightPower);
    ZandersControlScheme(frc::Joystick& joyStickLeft, frc::Joystick& joyStickRight);
    frc::Joystick& m_joyStickLeft;
    frc::Joystick& m_joyStickRight;
    virtual double ArmLift();
    virtual void AutoAlign(double& leftPower, double& rightPower);
};



class SecondaryControl
{
    public:
    virtual double Winch() = 0;
    virtual double Intake() = 0;
    virtual void pivot(bool& firstPiston, bool& secondPiston) = 0;

};
class MatthewSecondary:public SecondaryControl
{
    public:
    MatthewSecondary(frc::Joystick& gamepad);
    frc::Joystick& m_gamepad;
    virtual double Winch();
    virtual double Intake();
    virtual void pivot(bool& firstPiston, bool& secondPiston);
};
class TariqSecondary:public SecondaryControl
{
    public:
    TariqSecondary(frc::Joystick& gamepad);
    frc::Joystick& m_gamepad;
    virtual double Winch();
    virtual double Intake();
    virtual void pivot(bool& firstPiston, bool& secondPiston);
};
class ZanderSecondary:public SecondaryControl
{
    public:
    ZanderSecondary(frc::Joystick& gamepad);
    frc::Joystick& m_gamepad;
    virtual double Winch();
    virtual double Intake();
    virtual void pivot(bool& firstPiston, bool& secondPiston);
};
class TroySecondary:public SecondaryControl
{
    public:
    TroySecondary(frc::Joystick& gamepad);
    frc::Joystick& m_gamepad;
    virtual double Winch();
    virtual double Intake();
    virtual void pivot(bool& firstPiston, bool& secondPiston);
};
class KentSecondary:public SecondaryControl
{
    public:
    KentSecondary(frc::Joystick& gamepad);
    frc::Joystick& m_gamepad;
    virtual double Winch();
    virtual double Intake();
    virtual void pivot(bool& firstPiston, bool& secondPiston);
};