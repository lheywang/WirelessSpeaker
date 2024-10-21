# EEPROMS
This ensemble of headers define the way the configuration data is configured on the speaker, and stored on the EEPROM.
It's under the form of a struct, which contain struct and maybe even more structs on it.
This is done to separate the data in the cleanest way as possible.

## EEPROM Notes
The EEPROM can only be written on chunks of 64 bytes, thus there is series of writes.
Read at the opposite can be done in a single shot.

### Timings
Due to the slow write time, the EEPROM can't be wrote frequently.
As information, a page take ~5ms to be wrote, and our data is 401 page long. This give us a write time of about 2.8s. That's slow.
At the opposite, reading the whole array take only 1.2 ms, so it's not an issue on the boot state.

### CRC
A CRC8 value is computed for each page, and then wrote on the EEPROM. This ensure the data has been correcly rode cycle after cycle.

## Layout
Please check the PDF file on git that store the layout.

### Notes for the layout 
This layout has been designed to be easy to parse and read, rather than memory density. This is why there is a lot of naturals values expressed here.

## Revisions
There is three states : 

Major
Median
Minor

Only major revisions are allowed to perform a layout modification. 
Median revisions can be a type change for example.
Minor can be type changes.
