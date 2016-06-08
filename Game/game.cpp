#include "game.h"

Game::Game()
{
    multipler = 100;
    carLength = 50;
}

Game::Game(double base,double carSize)
{
    multipler = base;
    carLength = carSize;
}

void Game::Init()
{
    Serial.println("Start Wheels");
    wheels.Start();   //this function must be called before any actions for wheels!!!
    CarCom.Init();
}

//base functions for moving
void Game::Move(double Left_Speed,double Right_Speed)
{
    Serial.println("Move based on the left and right Speed");
    wheels.LeftWheel(Left_Speed);
    wheels.RightWheel(Right_Speed);
}

void Game::GoAhead(int Speed)
{
    Serial.println("Forward");
    wheels.Forward(Speed);
}

void Game::GoBack(int Speed)
{
    Serial.println("Backward");
    wheels.Backward(Speed);
}

void Game::Turn_Left(int Speed)
{
    Serial.println("TurnLeft");
    wheels.TurnLeft(Speed);
}

void Game::Turn_Right(int Speed)
{
    Serial.println("TurnRight");
    wheels.TurnRight(Speed);
}

void Game::Stop_Car()
{
    Serial.println("Stop");
    wheels.Stop();
}

//communication function
void Game::Update()
{
    com_status = CarCom.UpdatePosAndDest();

    if (com_status == ComSucess){
        //  move car
        UpdateDataFromCommunication();  //update currentPos, previousPos,destPos
        if(mode==0){
            //Auto Mode
            if(currentPos.GetX()==1023 || currentPos.GetY()==1023){
                Stop_Car();
            }
            else{
                //calling PID stuff: passing errorVelocity,carlength,currentPos
                Serial.println("**********************************");
                Point errorVelocity = destPos - currentPos;
                Serial.print("currentPos: (");Serial.print(currentPos.GetX());
                Serial.print(",");Serial.print(currentPos.GetY());Serial.println(")");
                Serial.print("destPos: (");Serial.print(destPos.GetX());
                Serial.print(",");Serial.print(destPos.GetY());Serial.println(")");
                Serial.print("errorVelocity: (");Serial.print(errorVelocity.GetX());
                Serial.print(",");Serial.print(errorVelocity.GetY());Serial.println(")");
                PID p_i_d(errorVelocity,carLength,currentPos);
                double ratio = p_i_d.GetRatioVelocity();            
                Serial.print("ratio: ");Serial.println(ratio);
                //based on the pid ratio to move the car
                double leftSpeed = ratio * multipler;
                double rightSpeed = multipler;
                Serial.print("leftSpeed: ");Serial.println(leftSpeed);
                Serial.print("rightSpeed: ");Serial.println(rightSpeed);
                Move(leftSpeed,rightSpeed); //move the car based on PID ratio
                Serial.println("**********************************");
            }
        }
        else{
            //Manual Mode
            com_status = CarCom.UpdateCmd();
            if(com_status == ComSucess){
                int leftSpeed = CarCom.getCmdLeft();
                int rightSpeed = CarCom.getCmdRight();
                Move(leftSpeed,rightSpeed);
            }
            else{
                Stop_Car();
            }
        }
    }
    if (com_status == ComWifiDisconnect){
        // stop car...
        Stop_Car();
        // reconnect to wifi & server
        CarCom.ReconnectWifi();
        CarCom.ReconnectServer();
    }
    else if (com_status == ComServerDisconnect) {
        // stop car...
        Stop_Car();
        // reconnect to server
        CarCom.ReconnectServer();
    }
    else {
        // stop car...
        Stop_Car();
        delay(5000);    //just for now...
        // other error...
    }
}

void Game::UpdateDataFromCommunication()
{
    previousPos = CarCom.getCurrentPos();
    currentPos = CarCom.getPrevPos();
    destPos = CarCom.getDest();
}

//access functions
double Game::GetMultipler()
{
    return multipler;
}

Point Game::GetCurrentPos()
{
    return currentPos;
}

Point Game::GetDestPos()
{
    return destPos;
}

double Game::GetTime()
{
    return time;
}
