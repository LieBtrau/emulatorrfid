## RFID-reader ##
### Images ###
<img src='http://emulatorrfid.googlecode.com/files/readerClosed.JPG' align='left' height='150' title='Closed RFID-reader' />

<img src='http://emulatorrfid.googlecode.com/files/readerOpened.JPG' align='middle' height='150' title='RFID-reader opened up' />

### Downloads ###
  * [Schematic](http://emulatorrfid.googlecode.com/files/rfidReader_schematic_R2.00.pdf)
  * [Assembly drawing](http://emulatorrfid.googlecode.com/files/rfidReader_assembly_R2.00.pdf)
  * [Gerber data](http://emulatorrfid.googlecode.com/files/reader_gerberdata_2.00.zip)
### MCU ###
The RFID-reader was designed in such a way that the necessary hardware was limited as much as possible.  So the [Cypress PSoc 1](http://www.cypress.com/?id=1573&source=header) was chosen.  This device combines an 8bit-MCU with configurable digital and analog blocks.  So the analog filtering of incoming RFID-data takes place inside this device.

### Communication + Power ###
USB was chosen for powering and communication, as there is only one connector needed to perform both of these functionalities.  [Cypress](http://www.cypress.com) has devices with USB-on board, but these devices are only available in QFN-packages which are very hard to solder by hand.
The FT232R-chip of FTDI takes care of the USB-side of the communication.  The MCU only needs to implement a UART.
On the PC-side, hyperterminal is used to see the ID of the tag currently being read and to see the ID's already in the reader's memory.

### Antenna coil ###
It's impossible to calculate what the ideal coil is for the communication, because the parameters of the coil inside the tag are unknown.  Surfing around can give you some useful information about what manufacturers of RFID-systems are using.  Trying to make a coil that mimics the coil inside the transponder will give you a good start.