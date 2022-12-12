import serial

ser = serial.Serial('COM11', 9600, timeout=1)

while not ser.isOpen():
    pass

ser.write(b"LOGON")
