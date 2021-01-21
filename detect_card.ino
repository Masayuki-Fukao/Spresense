/*
    camera.ino - One second interval time-lapse Camera
    Copyright 2018 Sony Semiconductor Solutions Corporation

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    This is a test app for the camera library.
    This library can only be used on the Spresense with the FCBGA chip package.
*/
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS -1
#define TFT_RST 8
#define TFT_DC 9

#define PIN1 2
#define PIN2 1
#define PIN3 0

#define PIC 15 //16pcx
#define ADDPIC 32
Adafruit_ILI9341 tft = Adafruit_ILI9341(&SPI, TFT_DC , TFT_CS , TFT_RST);

#include <SDHCI.h>
#include <stdio.h>  /* for sprintf */
#include <NetPBM.h>
#include <DNNRT.h>
#include <limits.h>


DNNRT dnnrt;

#include <Camera.h>

#define BAUDRATE                (115200)

SDClass  theSD;
int take_picture_count = 0;
/*
int point[9][2] = {
  {58,138},{70,136},{82,136},{94,135},{105,134},{117,134},{129,133},{140,132},{152,131}
  };
*/
int point[9][2] = {
  {43,136},{55,135},{68,136},{79,135},{91,134},{103,134},{115,134},{128,134},{140,134}
  };

/**
   Print error message
*/

void printError(enum CamErr err)
{
  Serial.print("Error: ");
  switch (err)
  {
    case CAM_ERR_NO_DEVICE:
      Serial.println("No Device");
      break;
    case CAM_ERR_ILLEGAL_DEVERR:
      Serial.println("Illegal device error");
      break;
    case CAM_ERR_ALREADY_INITIALIZED:
      Serial.println("Already initialized");
      break;
    case CAM_ERR_NOT_INITIALIZED:
      Serial.println("Not initialized");
      break;
    case CAM_ERR_NOT_STILL_INITIALIZED:
      Serial.println("Still picture not initialized");
      break;
    case CAM_ERR_CANT_CREATE_THREAD:
      Serial.println("Failed to create thread");
      break;
    case CAM_ERR_INVALID_PARAM:
      Serial.println("Invalid parameter");
      break;
    case CAM_ERR_NO_MEMORY:
      Serial.println("No memory");
      break;
    case CAM_ERR_USR_INUSED:
      Serial.println("Buffer already in use");
      break;
    case CAM_ERR_NOT_PERMITTED:
      Serial.println("Operation not permitted");
      break;
    default:
      break;
  }
}

/**
   Callback from Camera library when video frame is captured.
*/

void CamCB(CamImage img)
{

  /* Check the img instance is available or not. */

  if (img.isAvailable())
  {

    /* If you want RGB565 data, convert image data format to RGB565 */

    img.convertPixFormat(CAM_IMAGE_PIX_FMT_RGB565);
    //img.convertPixFormat(CAM_IMAGE_PIX_FMT_GRAY);

    /* You can use image data directly by using getImgSize() and getImgBuff().
       for displaying image to a display, etc. */

    /*tft.drawRGBBitmap(0, 0, (uint16_t *)img.getImgBuff(), 320, 240);*/
    tft.drawGrayscaleBitmap(0, 0, (uint8_t *)img.getImgBuff(), 320, 240);
    /*
    Serial.print("Image data size = ");
    Serial.print(img.getImgSize(), DEC);
    Serial.print(" , ");

    Serial.print("buff addr = ");
    Serial.print((unsigned long)img.getImgBuff(), HEX);
    Serial.println("");
    */
  }
  else
  {
    Serial.print("Failed to get video stream image\n");
  }
}

/**
   @brief Initialize camera
*/
void setup()
{
  CamErr err;

  /* Open serial communications and wait for port to open */

  Serial.begin(BAUDRATE);
  while (!Serial)
  {
    ; /* wait for serial port to connect. Needed for native USB port only */
  }

  /* Initialize SD */
  while (!theSD.begin())
  {
    /* wait until SD card is mounted. */
    Serial.println("Insert SD card.");
  }

  /* begin() without parameters means that
     number of buffers = 1, 30FPS, QVGA, YUV 4:2:2 format */

  Serial.println("Prepare camera");
  err = theCamera.begin();
  if (err != CAM_ERR_SUCCESS)
  {
    printError(err);
  }

  /* Start video stream.
     If received video stream data from camera device,
      camera library call CamCB.
  */

  tft.begin(40000000);
  tft.setRotation(3);

  Serial.println("Start streaming");
  err = theCamera.startStreaming(true, CamCB);
  if (err != CAM_ERR_SUCCESS)
  {
    printError(err);
  }

  /* Auto white balance configuration */

  //Serial.println("Set Auto white balance parameter");
  /*
  err = theCamera.setAutoWhiteBalanceMode(CAM_WHITE_BALANCE_DAYLIGHT);
  if (err != CAM_ERR_SUCCESS)
  {
    printError(err);
    
  }
  */
  /*
  err = theCamera.setAutoWhiteBalance(false);
  if (err != CAM_ERR_SUCCESS)
  {
    printError(err);
    
  }

  err = theCamera.setAutoISOSensitivity(false);
  if (err != CAM_ERR_SUCCESS)
  {
    printError(err);
    
  }
  
  err = theCamera.setColorEffect(CAM_COLOR_FX_BW);
    if (err != CAM_ERR_SUCCESS)
    {
      printError(err);
    
    } 
  
  /* Set parameters about still picture.
     In the following case, QUADVGA and JPEG.
  */
  //CAM_IMGSIZE_QUADVGA_H,CAM_IMGSIZE_QUADVGA_V,
  Serial.println("Set still picture format");
  err = theCamera.setStillPictureImageFormat(
          320,
          240,
          CAM_IMAGE_PIX_FMT_YUV422);
  if (err != CAM_ERR_SUCCESS)
  {
    printError(err);
  }
  /*CAM_IMGSIZE_QUADVGA_V*/
  pinMode(PIN1,OUTPUT);
  pinMode(PIN2,OUTPUT);
  pinMode(PIN3,OUTPUT);
  digitalWrite(PIN1, LOW);
  digitalWrite(PIN2, LOW);
  digitalWrite(PIN3, LOW);
}

/**
   @brief Take picture with format JPEG per second
*/

void loop()
{
  sleep(0.1); /* wait for one second to take still picture. */

  /* You can change the format of still picture at here also, if you want. */

  /* theCamera.setStillPictureImageFormat(
       CAM_IMGSIZE_HD_H,
       CAM_IMGSIZE_HD_V,
       CAM_IMAGE_PIX_FMT_JPG);
  */

  /* This sample code can take 100 pictures in every one second from starting. */
  digitalWrite(PIN1, HIGH);
  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN3, HIGH);
  
  
    /* Take still picture.
      Unlike video stream(startStreaming) , this API wait to receive image data
       from camera device.
    */

    Serial.println("call takePicture()");
    CamImage img = theCamera.takePicture();
    if(!img.isAvailable()){
      Serial.println("can not take picture");
      return 0 ;
    }
    
    CamImage img_small;
    
    /* Check availability of the img instance. */
    /* If any error was occured, the img is not available. */

      //kyoubunnsann counter
      String bunsancounter ;

    if (img.isAvailable()){

        CamErr err = img.clipAndResizeImageByHW(img_small,64,131, 111 ,178, 24, 24);
        if(err){
          Serial.println("ERROR : " + String(err));
          return 0 ;
        }
        CamErr err1 = img_small.resizeImageByHW(img_small,48,48);
        if(err1){
          Serial.println("resize (16,16)");
          Serial.println("ERROR : " + String(err1));
          return 0 ;
        }
  
        //kyoubunnsann 
        double distribut = INT_MAX;          
       
          //input heikinn
          double input_ave = 0;
          
          //road heikin
          double road_ave = 0;
    
          //seki
          double mult = 0;
    
          //hikaku
          double hikakudistribut = 0;
          double sa = 0;
          //sigumax*x
          double sigma_input = 0 ;
          double sigma_load = 0 ;
          //road pgm file
 
          //Serial.println("detect.pgm");
          File pgmfile = theSD.open("detect2.pgm");
          if(!pgmfile){
            Serial.println("con not load pgm file");
            return 0 ;
          }
          NetPBM pgm(pgmfile);
          
          unsigned short width, height;
          pgm.size(&width, &height);
          
          DNNVariable input(width * height);
          float *buf = input.data();
          //Serial.println(String(width));
          //DNNVariable input(16 * 16);
          //uint8_t *roadpgbbuf = (uint8_t*)input.data();
          uint16_t  *inputbuf = (uint16_t*)img_small.getImgBuff();
          int count = 0;
          //sabunn 
          for(int x = 0 ; x < 48 ; x ++){
            for(int y = 0 ; y < 48 ; y++){
              //
              uint8_t val = (uint8_t*)((*inputbuf & 0xFF00) >> 8);
              float pgmbuf = float(pgm.getpixel(x, y));

              double val_dou = (double)val / 2304 ;
              double pgmbuf_dou = (double)pgmbuf /2304  ;

              //Serial.println(String(pgmbuf));
              //Serial.println(String(val_dou));
              input_ave = input_ave + val_dou ;
              //Serial.println(String(input_ave));
              road_ave = road_ave + pgmbuf_dou ;
              mult = mult + pgmbuf_dou * val_dou *2304 ;
              sigma_input = sigma_input + val_dou * val_dou *2304 ;
              sigma_load = sigma_load + pgmbuf_dou * pgmbuf_dou *2304;
              sa = sa + (val_dou - pgmbuf_dou) * (val_dou - pgmbuf_dou) *2304;
              
              ++inputbuf;             
              
            }
          }
        
          hikakudistribut = (mult - (input_ave * road_ave));

          double zncc = (hikakudistribut)/(sqrt((sigma_input - input_ave*input_ave)) * sqrt((sigma_load - road_ave *road_ave)));
           
          Serial.print("zncc = ");
          Serial.println(String(zncc));
          Serial.print("sa = ");
          Serial.println(String(sa));
          
          if( 0.3 < zncc){
            //
            Serial.print("これは学生証です");         
          }
          else{
            Serial.print("これは学生証ではありません");   
          }
          pgmfile.close();       
        }
    
   
    Serial.println("finish !");
    while(1);
    
}
   
