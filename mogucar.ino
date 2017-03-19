
#include <Servo.h>
Servo myServo;
//3,5,6,9,10,11 PWM


int rData;  //用于保存接受的数据
int n = 175;
int po = 100; //舵机转动延迟时间
int f = 0;
int b;
int q;
int w;
int e;
int r;
int t;
int motor1 = 3;
int motor2 = 5;
int pos = 0;  //  记录舵机的位置
void setup() {
  Serial.begin(115200);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  digitalWrite(motor1, LOW); //利用程序控制小车开关
  digitalWrite(motor2, LOW);
  myServo.attach(9);
  myServo.write(86);   //初始校准舵机的位置
}
void loop() {
  while (Serial.available() > 0) {
    rData = Serial.read();  //取得串口数据流中查找一个有效整数
    Serial.println(rData);
    //++++++++++++++++++++++++++++++++++++++++++++++++          前后停
    if (rData == 0X01) {                   //前进
      analogWrite(motor1, 255);
      analogWrite(motor2, 0);
      delay(100);
      forward();
    }
    else if (rData == 0X02) {           //松开按钮 停止前进
      STOP();
    }
    else if (rData == 0X03) {               //后退
      analogWrite(motor1, 0);
      analogWrite(motor2, 255);
      delay(100);
      backward();

    }
    else if (rData == 0X02 && q == 1) {
      //松开按钮停止后退
      STOPBACK();
    }
    else if (rData == 0X02 && w == 1) {
      STOPFORWARD();
    }
    //+++++++++++++++++++++++++++++++++++++++++++++   在前后运动中加速
    else if (rData == 0X04 && f == 1) {

      forward2();
    }
    else if (rData == 0X04 && b == 1) {

      backward2();
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++   在前进中 右转 左转
    else if (rData == 0X05 && f == 1) {
      servo100();
      forward();
      Serial.println("前左");

    }
    else if (rData == 0X08 && f == 1) {
      servo110();
      forward();
      Serial.println("前左");

    }
    else if (rData == 0X09 && f == 1) {
      servo120();
      forward();
      Serial.println("前左");
      Serial.println(f);
    }
    else if (rData == 0X06 && f == 1) {
      servo70();

      forward();
      //       f =0;
      Serial.println("前右");
    }
    else if (rData == 0X11 && f == 1) {
      servo80();

      forward();

      Serial.println("前右");
    }
    else if (rData == 0X12 && f == 1) {
      servo60();

      forward();
      //       f =0;
      Serial.println("前右");
    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++   在后退中  右转左转
    else if (rData == 0X05 && b == 1) {
      servo100();
      backward();
      //    b =0;
      Serial.println("左后转");
    }
    else if (rData == 0X08 && b == 1) {
      servo110();
      backward();
      //    b =0;
      Serial.println("左后转");
    }
    else if (rData == 0X09 && b == 1) {
      servo120();
      backward();
      //    b =0;
      Serial.println("左后转");
    }
    else if (rData == 0X11 && b == 1) {
      servo80();
      backward();
      //    b =0;
      Serial.println("右后转");
    }
    else if (rData == 0X12 && b == 1) {
      servo60();
      backward();
      //    b =0;
      Serial.println("右后转");
    }
    else if (rData == 0X06 && b == 1) {
      servo70();


      backward();
      Serial.println("右后转");
    }
    // +++++++++++++++++++++++++++++++++++++++   在加速运动的时候进行舵机控制  右后退  左后退  加速会重置加速
    //没有精确时间 估计要定时器/计时器         
    else if (rData == 0X05 && q == 1) {
      servo100();
      forward2();
      Serial.println("加速前100");   //回传数据
    }
     else if (rData == 0X08 && q == 1) {
      servo110();
      forward2();
      Serial.println("加速前110");   //回传数据
    }
     else if (rData == 0X09 && q == 1) {
      servo120();
      forward2();
      Serial.println("加速前左120");   //回传数据
    }
    else if (rData == 0X06 && q == 1) {
      servo70();
      forward2();
      Serial.println("加速前70");   //回传数据
    }
     else if (rData == 0X11 && q == 1) {
      servo80();
      forward2();
      Serial.println("加速前80");   //回传数据
    }
     else if (rData == 0X12 && q == 1) {
      servo60();
      forward2();
      Serial.println("加速前60");   //回传数据
    }
    //+++++++++++++++++++++++++++前进后退的分界线
    else if (rData == 0X05 &&  w == 1) {
      servo100();
      backward2();
      Serial.println(" 加速左转100");
    }
     else if (rData == 0X08 &&  w == 1) {
      servo110();
      backward2();
      Serial.println(" 加速左转110");
    }
     else if (rData == 0X09 &&  w == 1) {
      servo120();
      backward2();
      Serial.println(" 加速左转120");
    }
    else if (rData == 0X06 && w == 1) {
      servo70();
      backward2();
      Serial.println("加速右后转70");
    }
     else if (rData == 0X11 && w == 1) {
      servo80();
      backward2();
      Serial.println("加速右后转80");
    }
     else if (rData == 0X12 && w == 1) {
      servo60();
      backward2();
      Serial.println("加速右后转60");
    }
    //++++++++++++++++++++++++++++++++++++    没有运动的时候控制舵机
    else if (rData == 0X05 ) {  //左转
      servo100();
    }
    else if (rData == 0X06 ) {  //右  70
      servo70();
    }
    else if (rData == 0X07) {   //   90
      servo90();
    }
    else if (rData == 0X08) { //110
      servo110();
    }
    else if (rData == 0X09) {  // 120
      servo120();
    }
    else if (rData == 0X11) { //80
      servo80();
    }
    else if (rData == 0X12) {  //60
      servo60();
    }

  }
}
//++++++++++++++++++++++++++++++++++
void servo70() {
  myServo.write(71);   //20度差不多    15右后不可以
  delay(po);
  Serial.println("70");
}
void servo80() {
  myServo.write(80);   //20度差不多    15右后不可以
  delay(po);
  Serial.println("80");
}
void servo60() {
  myServo.write(60);   //20度差不多    15右后不可以
  delay(po);

  Serial.println("60");
}
void servo100() {
  myServo.write(101);
  delay(po);

  Serial.println("100");
}
void servo90() {         //90
  myServo.write(86);
  delay(po);

  Serial.println("90");
}
void servo110() {
  myServo.write(110);   //20度差不多    15右后不可以
  delay(po);
  Serial.println("110");
}
void servo120() {
  myServo.write(120);   //20度差不多    15右后不可以
  delay(po);

  Serial.println("120");
}
//+++++++++++++++++++++++++++++++++++++++++
void forward() {
  analogWrite(motor1, n);
  analogWrite(motor2, 0);
  Serial.println("前");
  f = 1;
}
void backward() {
  analogWrite(motor1, 0);
  analogWrite(motor2, n);
  Serial.println("后");
  b = 1;
}
void STOP() { //+++++++++++++++++++++++++++++++++
  analogWrite(motor1, 0);
  analogWrite(motor2, 0);
  f = 0;    //重置 f  b
  b = 0;
  Serial.println("停止");
  Serial.println(f);
  Serial.println(b);
}
void STOPBACK() {
  analogWrite(motor1, 0);
  analogWrite(motor2, n);
  delay(500);
  analogWrite(motor1, 0);
  analogWrite(motor2, 0);
}
void STOPFORWARD() {
  analogWrite(motor1, n);
  analogWrite(motor2, 0);
  delay(500);
  analogWrite(motor1, 0);
  analogWrite(motor2, 0);
}
void forward2() {
  analogWrite(motor1, 255);
  analogWrite(motor2, 0);
  delay(1000);
  q = 1 ;
  forward();

  Serial.println("加速前");
}
void backward2() {
  analogWrite(motor1, 0);
  analogWrite(motor2, 255);
  delay(1000);
  w = 1;
  backward();

  Serial.println("加速后");
}
