# nodemcu-crypto
Simple code to Display Crypto Currency to 1602 i2c LCD on NodeMCU
Copyright (c) 2021 Mohammad Hafiz bin Ismail <mypapit@gmail.com)
Original Post: https://www.youtube.com/watch?v=bMO5UzgfTi0

The currency displayed is in Malaysian Ringgit (MYR)

## Citing this work
If you use this as a reference for your project, please cite this as (APA-Style): 
   
_Ismail, M. H. (2021). Simple code to Display Crypto Currency on NodeMCU with 1602 i2c LCD. Coding Malaya. 
Retrieved December 16, 2021, from https://github.com/mypapit/nodemcu-crypto_

  
![Screenshot](https://i.ytimg.com/vi/bMO5UzgfTi0/maxresdefault.jpg)
    

## Microcontroller Parts 
Required parts:
1. NodeMCU V2 Amica (V3 Lolin not recommended as it lacks internal LED)
2. i2c 1602 LCD 
3. Some jumper wires
  
Estimated Project cost: 
1. USD 5 + USD 3 = USD 8
2. MYR 20 + MYR 12 = MYR 32
      
This project uses internal LED to indicate the WiFi status. You are free to use external LED, if you want.
All configurable parameters are listed on the top section of the code.
      
===  NOTE: DO NOT FORGET TO CHANGE WiFI SSID and PASSWORD CONFIGURATION ====

## i2c LCD and NodeMCU setup
1. Connect i2c LCD SCL pin with NodeMCU D1 pin
2. Connect i2c SDA pin with NodeMCU D2 pin
3. Connect i2c GND, VCC pins with NodeMCU GND, Vin accordingly
      
      
## TERMS
You are free to use this code in your work and your project as long as:
1. You attribute and cite this work in your project or your project documentation.
2. Provide a link to this source code or its original website URL.
 
