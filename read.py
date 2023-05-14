#!/usr/bin/env python3

import serial
import mysql.connector

cnx  =  mysql.connector.connect(
    host="localhost",
    user="root",
    database="uids"
)
cursor = cnx.cursor()
cursor.execute("SELECT * FROM validUids")
results = cursor.fetchall()

ser = serial.Serial(
        port='COM4', #plz change this according to your port number
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)

ser.flush()

if __name__ == '__main__':
    valid = False
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            for uid in results:
                if(uid[0].strip() == line.strip()):
                    valid = True
                    ser.write('Wow......'.encode())
            if(valid):
                print('UID is valid')
                valid= False
            else:
                ser.write('Not working....'.encode())
                print("UID is invalid!")
        

