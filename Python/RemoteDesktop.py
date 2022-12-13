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


TIMEOUT = 30

Console = None


class Error:
    NO_WIFI = "NO_WIFI"
    NO_SERIAL = "NO_SERIAL"
    NO_PARSEC = "NO_PARSEC"


class Status:
    LOGON = "LOGON"
    WIFI = "WIFI"
    PARSEC = "PARSEC"


def send_error(error):
    print("Failure: " + error)
    Console.write(("/FAILURE -"+error).encode("UTF-8"))


def send_status(status):
    Console.write(("/SETSTAT +"+status).encode("UTF-8"))


def connect_to_wifi():
    try:
        os.system('netsh wlan connect name="' + Secret.SSID +
                  '" ssid="' + Secret.SSID)
        sleep(2)
        return True
    except:
        return False


def turn_off_monitor():
    win32api.SendMessage(win32con.HWND_BROADCAST,
                         win32con.WM_SYSCOMMAND, win32con.SC_MONITORPOWER, 2)


def turn_on_monitor():
    win32api.SendMessage(win32con.HWND_BROADCAST,
                         win32con.WM_SYSCOMMAND, win32con.SC_MONITORPOWER, -1)


def connect_to_serial():
    global Console

    print("Connecting to serial")

    COM = "COM11"

    start = time()
    while time() - start < TIMEOUT:
        ports = list(list_ports.comports())
        for p in ports:
            if "Arduino" in p.description or "Leonardo" in p.description:
                COM = p.device

        Console = serial.Serial(COM, 9600, timeout=1)

        sleep(2)

        if Console.isOpen():
            return True

    return False


def open_parsec():
    print("Opening parsec")

    executable_path = "C:\\Program Files\\Parsec\\parsecd.exe"

    subprocess.Popen([executable_path])

    parsec_running = False

    start = time()
    while time() - start < TIMEOUT:
        for proc in psutil.process_iter():
            if proc.name() == "parsecd.exe":
                return True
        sleep(2)

    return False


def aknowledge():
    print("Awaiting aknowledge")
    start = time()
    while time() - start < TIMEOUT:
        if Console.in_waiting > 0:
            message = Console.readline().decode("UTF-8").strip()
            if message.find("AK") != -1:
                return True

    return False


def main():

    if not connect_to_serial():
        send_error(Error.NO_SERIAL)
        return

    send_status(Status.LOGON)

    if (not aknowledge()):
        send_error(Error.NO_SERIAL)

    if not connect_to_wifi():
        send_error(Error.NO_WIFI)
        return

    send_status(Status.WIFI)

    if (not aknowledge()):
        send_error(Error.NO_SERIAL)

    if not open_parsec():
        send_error(Error.NO_PARSEC)
        return

    send_status(Status.PARSEC)

    if (not aknowledge()):
        send_error(Error.NO_SERIAL)


if __name__ == "__main__":
    main()
    input()
