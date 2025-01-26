from time import sleep
from time import time
import serial
import serial.tools.list_ports as list_ports
import psutil
import subprocess
import win32api
import win32con
import os
import Secret
from Types import *

path = "C:\\Users\\Esteban\\Documents\\Proyectos\\RemoteDesktop\\Python\\Logoff.txt"

TIMEOUT = 5

Console = None


def send_error(error):
    print("Failure: " + error)
    Console.write(("/FAILURE -"+error).encode("UTF-8"))


def send_status(status):
    print("Writing status: " + status)
    log("Status: " + status)
    Console.write(("/SETSTAT +"+status).encode("UTF-8"))
    print("Status written")


def connect_to_serial():
    global Console

    print("Connecting to serial")

    COM = "COM11"

    start = time()
    while time() - start < TIMEOUT:

        log("Attempt")

        ports = list(list_ports.comports())
        for p in ports:
            log(p.description)
            if "Arduino" in p.description or "Leonardo" in p.description:
                log("Found")
                COM = p.device
                break

        log("COM: " + COM)
        Console = serial.Serial(COM, 9600, timeout=3, write_timeout=3)
        log("Serial: " + str(Console.isOpen()))
        sleep(2)

        if Console.isOpen():
            log("Serial open")
            print("Serial open")
            return True

    log("Serial not open")
    return False


def log(msg):
    with open(path, "a") as f:
        f.write(msg + "\n")


def main():

    with open(path, "w") as f:
        f.write("")

    try:
        log("Try")

        if not connect_to_serial():
            log("No serial")
            send_error(Error.NO_SERIAL)
            return
    except:
        print("No serial")
        log("Except: No serial")
        return

    try:
        send_status(Status.IDLE)
    except Exception as e:
        log("Except: " + str(e))
        return
    log("End")


if __name__ == "__main__":
    main()
    log("End of script")
