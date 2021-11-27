# Notes on 7x6 layout

The 7x6 is a copy of the 6x6 layout with a few differencies:
 - ARM (STM32F401) instad of Atmel
 - simpler matrix wiring
 - serial full-duplex split connection
 - handness defined by pin

## Quick Setup

1. boot each controller to DFU mode and flash the firmware, i.e.:
   `qmk flash -kb handwired/dactyl_manuform/7x6 -km rubienr`
3. bridge B10 to 3.3V on the left hand side 
4. wire the split serial connection in between controllers:
   A9 to A10 and A10 to A9 (crossed over)
5. wire the GND to GND and 5V to 5V in between controllers
6. optionally attach OLED displays to B6 (SCL) and B7 (SDA), one each side

## Notes

* STM32F4 has no flash, for simplicity left vs right is defined by handness-pin.
  The USB cable can be then attached to any side.
* for split keyboard on ARM it is recommended to use serial connection rather than I2C
* Whilst the first 5x6 matrix rows/cols are intuitive to address,
  this layout considers the 6th row as the very next row consting of
  six keys (two normal + four thumb keys) below the 5x6 matrix.
  This keys are not aligned in a straight line.
  The remaining two (thumb) keys are counted to be in the seventh row.
  The matrix is as follows:
         C0 C1 C2 C3 C4 C5        C0 C1 C2 C3 C4 C5
    R0   .. .. .. .. .. ..        .. .. .. .. .. ..
    R1   .. .. .. .. .. ..        .. .. .. .. .. ..
    R2   .. .. .. .. .. ..        .. .. .. .. .. ..
    R3   .. .. .. .. .. ..        .. .. .. .. .. ..
    R4   .. .. .. .. .. ..        .. .. .. .. .. ..
    R5   .. .. .. .. .. ..        .. .. .. .. .. ..
    R6               .. ..        .. ..
  * the Blackpill pins are:
                LEFT                     RIGHT
         B1 B0 A7 A6 A5 A4         B1 B0 A7 A6 A5 A4
    A3   .. .. .. .. .. ..         .. .. .. .. .. ..
    A2   .. .. .. .. .. ..         .. .. .. .. .. ..
    A1   .. .. .. .. .. ..         .. .. .. .. .. ..
    A0   .. .. .. .. .. ..         .. .. .. .. .. ..
    C15  .. .. .. .. .. ..         .. .. .. .. .. ..
    C14  .. .. .. .. .. ..         .. .. .. .. .. ..
    C13              .. ..         .. ..
  * the physical layout is rather:  
         .. .. .. .. .. ..         .. .. .. .. .. ..
         .. .. .. .. .. ..         .. .. .. .. .. ..
         .. .. .. .. .. ..         .. .. .. .. .. ..
         .. .. .. .. .. ..         .. .. .. .. .. ..
         .. .. .. .. .. ..         .. .. .. .. .. ..
               .. ..                     .. ..
                     .. ..         .. ..
                        .. ..   .. ..
                        .. ..   .. ..  
