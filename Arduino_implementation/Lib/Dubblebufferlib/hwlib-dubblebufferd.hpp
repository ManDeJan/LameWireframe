/**
 * \file
 * \brief      Double bufferd Hwlib header, can be used as an extension to hwlib.
 * \author     Jan Halsema
 * \copyright  Copyright (c) 2016, Jan Halsema
 *
 * \page License
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <hwlib-graphics.hpp>

namespace hwlib {

/**
 * \brief the main class of dubblebufferd, a decorator for hwlib windows.
 *
 * This class implements an decorator to any* hwlib window, it adds the functionallity
 * of dubble buffering for windows that take a very long time to clear and rewrite completly
 * each frame, such as SSD1306 controlled screens.
 * right now I only support the SSD1306 Glcd-Oled window because that is #1 priority
 * 
 * It uses an array of bools instead of working with bitwise operators because the memory loss outweighed the performance increase,
 * plus it was way easier to make in my available time.
 *
 * Usage:
 * The only thing you need to change in your code is add a .flush() command every time you want to update the screen
 */
class bufferwindow : public window {
private:
   bool currentframe[128][64];
   bool nextframe[128][64];
   window &slave;

   void write_implementation( location pos, color col ) override {
      if( col == foreground ){ 
         currentframe[pos.x][pos.y] = 1;  
      } else {
         currentframe[pos.x][pos.y] = 0; 
      }      
   }
   
public:
   /**
    * \brief The decorator of a buffered window
    *
    * \param slaveWindow slaveWindow is a reference to any hwlib window.
    */
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
