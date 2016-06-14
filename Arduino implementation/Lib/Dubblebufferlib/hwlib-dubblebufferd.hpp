// ==========================================================================
//
// File      : hwlib-glcd-oled.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#pragma once

#include <hwlib-graphics.hpp>

namespace hwlib {
   
/// Oled B/W graphics LCD
//
/// This class implements an decorator to any* hwlib window, it adds the functionallity
/// of dubble buffering for windows that take a very long time to clear and rewrite completly
/// each frame, such as SSD1306 controlled screens.
/// * right now I only support the SSD1306 Glcd-Oled window because that is #1 priority
class bufferwindow : public window {
private:
   bool currentframe[128][64];
   bool nextframe[128][64];
   window &slave;

   void write_implementation( location pos, color col ) override {
      if( col == foreground ){ 
         currentframe[pos.x][pos.y] = 1;  
      } else {
         currentframe[pos.x][pos.y] = 1; 
      }      
   }
   
public:
   
   bufferwindow( window &slaveWindow ):
      window (slaveWindow.size, slaveWindow.foreground, slaveWindow.background ),
      slave (slaveWindow)
   {
      slave.clear();
      for( uint8_t y = 0; y < 64; y++ ){
         for( uint8_t x = 0; x < 128; x++ ){
            nextframe[x][y] = 0;
            currentframe[x][y] = 0;
         }                 
      }    
   }

   virtual void clear(){

      for( uint8_t y = 0; y < 64; y++ ){
         for( uint8_t x = 0; x < 128; x++ ){
            currentframe[x][y] = 0;
         }                 
      }         
   }  


   void flush(){
      bool tmp;
      for( uint8_t y = 0; y < 64; y++ ){
         for( uint8_t x = 0; x < 128; x++ ){
            if(currentframe[x][y] != nextframe[x][y]) {
               tmp = currentframe[x][y];
               nextframe[x][y] = tmp;
               if (tmp == 1) {
                  slave.write(location{x,y}, foreground);
               } else {
                  slave.write(location{x,y}, background);
                  //slave.clear();
               }
            }
         }                 
      }  
   }

   // this code was used when I was trying to use bitwise operators to store the buffer
   // void flush(){
   //    for( uint8_t y = 0; y < 64 / 8; y++ ){
   //       for( uint8_t x = 0; x < 128; x++ ){
   //          uint8_t a, *b, c;
   //          bool d;
   //          a = currentframe[x * y];
   //          b = nextframe[x * y];
   //          c = a ^ b;
   //          for (uint8_t i = 0; i < 8; i++){
   //             d = (c >> i) & 1;
   //             if (d == 0) {
   //                b = a;
   //                slave.write(location{x,(y*8)+(x/16)}, ((a >> i) & 1));
   //             }
   //          }
   //       }                 
   //    }  
   // }
   
}; // class bufferwindow
   
}; // namespace hwlib
