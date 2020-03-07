#include "ControlScheme.hpp"
#include <iostream>
#include <Robot.h>
#include <frc/smartdashboard/SmartDashboard.h>

void TankControlScheme::getMotorPower(double &leftPower, double &rightPower) //Tank code gets the power back for the function
{
    leftPower = -(m_gamepad.GetRawAxis(1) * .6);  //limits the power than can come out to 0.6
    rightPower = -(m_gamepad.GetRawAxis(5) * .6); //limits the power than can come out to 0.6
}
TankControlScheme::TankControlScheme(frc::Joystick &gamepad) : m_gamepad(gamepad) // Initialize the gamepad
{
}
void TankControlScheme::AutoAlign(double &leftPower, double &rightPower) //Initializes the auto align so it can build
{
}
double TankControlScheme::ArmLift() //Initializes the arm lift so it can build
{
}

MatthewPrimary::MatthewPrimary(frc::Joystick &gamepad) : TankControlScheme(gamepad) // Initializes the builder of Tankcontrol scheme to inherit the gamepad from the cunstructor
{
}
void MatthewPrimary::AutoAlign(double &leftPower, double &rightPower) // Sets the autoalign buttons
{
    if (m_gamepad.GetRawButton(5)) // check if left bumper is being pushed down
    {
        Robot::Limelight(1, leftPower, rightPower);
    }
}
double MatthewPrimary::ArmLift()
{
    double liftSpeed = 0;
    if (m_gamepad.GetRawButton(6)) // right bumper
    {
        liftSpeed = 1; //returns a fixed power
    }
    else if (m_gamepad.GetRawAxis(3) >= .1) // right trigger
    {
        liftSpeed = -1;
    }
    else
    {
        liftSpeed = 0;
    }
    return liftSpeed;
}

KentPrimary::KentPrimary(frc::Joystick &gamepad) :TankControlScheme(gamepad)
{
    
}

void KentPrimary::AutoAlign(double &leftPower, double &rightPower) // sets power of motors to align the robot
{
    if (m_gamepad.GetRawButton(1)) // A button
    {
        Robot::Limelight(1, leftPower, rightPower);
    }
}
double KentPrimary::ArmLift()
{
    if (m_gamepad.GetRawButton(5)) //Left bumper
    {
        return 1;
    }
    else if (m_gamepad.GetRawAxis(2) >= .1) // left trigger
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

// ArcadeControlScheme was used for tariq and Troy. There primary drive controls are the same
void ArcadeControlScheme::getMotorPower(double &leftPower, double &rightPower) //sets the power of the motors in an arcade drive
{
    double forwardBackward = -(m_gamepad.GetRawAxis(1) * .6); //grabs the input and gives it to a variable for forward
    double leftRight = (m_gamepad.GetRawAxis(4) * .6);        //grabs the input and gives it to a variable for turning
    double drivePower = 0;

    // Checks to make sure that the user just wants to go straight and not turn. If so then it tells the motors to move according to the input of controllers
    if (fabs(forwardBackward) >= 0.05 && fabs(leftRight) <= 0.05)
    {
        leftPower = forwardBackward;
        rightPower = forwardBackward;
    }
    // Checks to see if you are turning while driving if so then it decrease power according to the turn
    else if (fabs(forwardBackward) >= 0.05 && fabs(leftRight) >= 0.05)
    {
        if (forwardBackward > 0)
        {
            drivePower = forwardBackward - fabs(leftRight);
            if (drivePower < 0)
            {
                drivePower = 0;
            }
        }
        else if (forwardBackward < 0)
        {
            drivePower = forwardBackward + fabs(leftRight);
            if (drivePower > 0)
            {
                drivePower = 0;
            }
        }
        if (leftRight > 0)
        {
            leftPower = forwardBackward;
            rightPower = drivePower;
        }
        else if (leftRight < 0)
        {
            leftPower = drivePower;
            rightPower = forwardBackward;
        }
    }
    // Checks to see if you just want to turn if so it makes you spin
    else if (fabs(forwardBackward) <= 0.05 && fabs(leftRight) >= 0.05)
    {
        leftPower = leftRight;
        rightPower = -leftRight;
    }
    // Sets power to zero if it does not fall into any of the conditions
    else
    {
        leftPower = 0;
        rightPower = 0;
    }
}
ArcadeControlScheme::ArcadeControlScheme(frc::Joystick &gamepad) : m_gamepad(gamepad)
{
}
void ArcadeControlScheme::AutoAlign(double &leftPower, double &rightPower) //sets the power for the motors to align it self with the camera
{
    if (m_gamepad.GetRawButton(1)) // A button for auto alignment
    {
       Robot::Limelight(1, leftPower,rightPower);
    }
}
double ArcadeControlScheme::ArmLift()
{
    double liftPower = 0;
    if (m_gamepad.GetRawButton(6)) // right bumper
    {
        liftPower = 1;
    }
    else if (m_gamepad.GetRawButton(5)) //left bumper
    {
        liftPower = -1;
    }
    else
    {
        liftPower = 0;
    }
    return liftPower;
}

void ZandersControlScheme::getMotorPower(double &leftPower, double &rightPower) // returns power to the motor uses joysticks
{
    double forwardBackward = -(m_joyStickLeft.GetRawAxis(1) * .6); // sets the input of the axis to the variable
    double leftRight = (m_joyStickRight.GetRawAxis(1) * .6);       // sets the input of the axis to the variable
    double drivePower = 0;

    // Checks to make sure that the user just wants to go straight and not turn. If so then it tells the motors to move according to the input of controllers
    if (fabs(forwardBackward) >= 0.05 && fabs(leftRight) <= 0.05)
    {
        leftPower = forwardBackward;
        rightPower = forwardBackward;
    }
    // Checks to see if you are turning while driving if so then it decrease power according to the turn
    else if (fabs(forwardBackward) >= 0.05 && fabs(leftRight) >= 0.05)
    {
        if (forwardBackward > 0)
        {
            drivePower = forwardBackward - fabs(leftRight);
        }
        else if (forwardBackward < 0)
        {
            drivePower = forwardBackward + fabs(leftRight);
        }
        if (leftRight > 0)
        {
            leftPower = forwardBackward;
            rightPower = drivePower;
        }
        else if (leftRight < 0)
        {
            leftPower = drivePower;
            rightPower = forwardBackward;
        }
    }
    // Checks to see if you just want to turn if so it makes you spin
    else if (fabs(forwardBackward) <= 0.05 && fabs(leftRight) >= 0.05)
    {
        leftPower = leftRight;
        rightPower = -leftRight;
    }
    // Sets power to zero if it does not fall into any of the conditions
    else
    {
        leftPower = 0;
        rightPower = 0;
    }
}
ZandersControlScheme::ZandersControlScheme(frc::Joystick &joyStickLeft, frc::Joystick &joyStickRight) : m_joyStickLeft(joyStickLeft), m_joyStickRight(joyStickRight) //builds the builder to be used to assign joysticks
{
}
void ZandersControlScheme::AutoAlign(double &leftPower, double &rightPower) // returns power to the motors to align the robot to the target
{
    if (m_joyStickRight.GetRawButton(1)) // A button
    {
        Robot::Limelight(1, leftPower, rightPower);
    }
}
double ZandersControlScheme::ArmLift()
{
    double liftPower = 0;
    if (m_joyStickRight.GetPOV(0)) //uses the d pad on the gamepads 0 being up and 180 being down
    {
        liftPower = 1;
    }
    else if (m_joyStickRight.GetPOV(180))
    {
        liftPower = -1;
    }
    else
    {
        liftPower = 0;
    }
    return liftPower;
}

MatthewSecondary::MatthewSecondary(frc::Joystick &gamepad) : m_gamepad(gamepad) // initializes the gamepad for secondary controlls
{
}
double MatthewSecondary::Winch() // used to send power to the winch motors
{
    double WinchSpeed = 0;
    if (m_gamepad.GetRawButton(2)) // B button
    {
        WinchSpeed = 1; //sets the power
    }
    else
    {
        WinchSpeed = 0;
    }
    return WinchSpeed;
}
void MatthewSecondary::Intake(double& ShooterPower, double& FeederPower) //Set power for intake and sends it to the motors
{
    if (m_gamepad.GetRawAxis(2) > 0.1)
    {
        FeederPower = -1;
    }
    else if(m_gamepad.GetRawAxis(3) > 0.1)
    {
        FeederPower = 1;
    }
    else
    {
        FeederPower = 0;
    }

    if (m_gamepad.GetRawButton(5))
    {
        ShooterPower = -1;
    }
    else if(m_gamepad.GetRawButton(6))
    {
        ShooterPower = 1;
    }
    else
    {
        ShooterPower = 0;
    }
}
void MatthewSecondary::pivot(bool &firstPiston)
{
    int position = 0;
    if (m_gamepad.GetRawButtonPressed(1))
    {
        firstPiston = true;
    }
    else if (m_gamepad.GetRawButtonPressed(2))
    {
        firstPiston = false;
    }
}

ZanderSecondary::ZanderSecondary(frc::Joystick &gamepad) : m_gamepad(gamepad)
{
}
double ZanderSecondary::Winch()
{
    double WinchSpeed = 0;
    if (m_gamepad.GetPOV(0)) // up d pad
    {
        WinchSpeed = 1;
    }
    else
    {
        WinchSpeed = 0;
    }
    return WinchSpeed;
}
void ZanderSecondary::Intake(double& ShooterPower, double& FeederPower)
{
    if (m_gamepad.GetRawAxis(2) > 0.1)
    {
        FeederPower = -1;
    }
    else if(m_gamepad.GetRawAxis(3) > 0.1)
    {
        FeederPower = 1;
    }
    else
    {
        FeederPower = 0;
    }

    if (m_gamepad.GetRawButton(5))
    {
        ShooterPower = -1;
    }
    else if(m_gamepad.GetRawButton(6))
    {
        ShooterPower = 1;
    }
    else
    {
        ShooterPower = 0;
    }
}
void ZanderSecondary::pivot(bool &firstPiston)
{
    int position = 0;
    if (m_gamepad.GetRawButtonPressed(1))
    {
        firstPiston = true;
    }
    else if (m_gamepad.GetRawButtonPressed(2))
    {
        firstPiston = false;
    }
}

TroyAndTariqSecondary::TroyAndTariqSecondary(frc::Joystick &gamepad) : m_gamepad(gamepad)
{
}
double TroyAndTariqSecondary::Winch()
{
    double WinchSpeed = 0;
    if (m_gamepad.GetPOV(0)) // up button d pad
    {
        WinchSpeed = 1;
    }
    else
    {
        WinchSpeed = 0;
    }
    return WinchSpeed;
}
void TroyAndTariqSecondary::Intake(double& ShooterPower, double& FeederPower)
{
    if (m_gamepad.GetRawAxis(2) > 0.1)
    {
        FeederPower = -1;
    }
    else if(m_gamepad.GetRawButton(5))
    {
        FeederPower = 1;
    }
    
    else if (m_gamepad.GetRawButton(1))
    {
        ShooterPower = -1;
        FeederPower = -1;
    }
    else if (m_gamepad.GetRawButton(4))
    {
        ShooterPower = 1;
        FeederPower = 1;
    }
    else
    {
        FeederPower = 0;
    }

    if (m_gamepad.GetRawAxis(3) > 0.1)
    {
        ShooterPower = -1;
    }
    else if(m_gamepad.GetRawButton(6))
    {
        ShooterPower = 1;
    }
    
    else if (m_gamepad.GetRawButton(1))
    {
        ShooterPower = -1;
        FeederPower = -1;
    }
    else if (m_gamepad.GetRawButton(4))
    {
        ShooterPower = 1;
        FeederPower = 1;
    }
    else
    {
        ShooterPower = 0;
    }
}
void TroyAndTariqSecondary::pivot(bool &firstPiston)
{
    if (m_gamepad.GetPOV(0))
    {
        firstPiston = true;
    }
    else if (m_gamepad.GetPOV(180))
    {
        firstPiston = false;
    }
}

KentSecondary::KentSecondary(frc::Joystick &gamepad) : m_gamepad(gamepad)
{
}
double KentSecondary::Winch()
{
    double WinchSpeed = 0;
    if (m_gamepad.GetRawButton(5)) // left bumper
    {
        WinchSpeed = 1;
    }
    else
    {
        WinchSpeed = 0;
    }
    return WinchSpeed;
}
void KentSecondary::Intake(double& ShooterPower, double& FeederPower)
{
    if (m_gamepad.GetRawAxis(2) > 0.1)
    {
        FeederPower = -1;
    }
    else if(m_gamepad.GetRawButton(5))
    {
        FeederPower = 1;
    }
    
    else if (m_gamepad.GetRawButton(1))
    {
        ShooterPower = -1;
        FeederPower = -1;
    }
    else if (m_gamepad.GetRawButton(4))
    {
        ShooterPower = 1;
        FeederPower = 1;
    }
    else
    {
        FeederPower = 0;
    }

    if (m_gamepad.GetRawAxis(3) > 0.1)
    {
        ShooterPower = -1;
    }
    else if(m_gamepad.GetRawButton(6))
    {
        ShooterPower = 1;
    }
    
    else if (m_gamepad.GetRawButton(1))
    {
        ShooterPower = -1;
        FeederPower = -1;
    }
    else if (m_gamepad.GetRawButton(4))
    {
        ShooterPower = 1;
        FeederPower = 1;
    }
    else
    {
        ShooterPower = 0;
    }
}
void KentSecondary::pivot(bool &firstPiston)
{
    int position = 0;
    if (m_gamepad.GetRawAxis(2) > .1) // uses the left trigger
    {
        firstPiston = true;
    }
    else if (m_gamepad.GetRawButtonPressed(5)) // uses the right bumper
    {
        firstPiston = false;
    }
}