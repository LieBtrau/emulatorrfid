## Images ##
<img src='http://emulatorrfid.googlecode.com/files/tagClosed.JPG' height='150' />
<img src='http://emulatorrfid.googlecode.com/files/TagOpened.JPG' height='150' />
<img src='http://emulatorrfid.googlecode.com/files/TagWithCoin.JPG' height='150' />
## Downloads ##
  * [Schematic](http://emulatorrfid.googlecode.com/files/rfid_tag_schematic_3.00.pdf)
  * [Assembly drawing](http://emulatorrfid.googlecode.com/files/rfid_tag_assembly_3.00.pdf)
  * [Gerber data](http://emulatorrfid.googlecode.com/files/rfid_tag_gerber_3.00.zip)
## Design info ##
I based my design on [Micah's tag](http://micah.navi.cx/2008/09/using-an-avr-as-an-rfid-tag/), which is a very basic tag.  I had to make some improvements because the reader at the office has a very limited reading range.  Even my own home made reader performs better.  After trying some coils of Coilcraft, I finally stumbled on the [RFID inlays of TI](http://www.ti.com/rfid/).  These 134.2kHz-tags have coils that were just what I needed.  So I ordered such a tag, cut loose the transponder and soldered my own transponder to it.  It worked!
The tag has just the perfect size for one of the company's numerous gadgets.  So now a have a miniature LED-light and a second tag all in one.