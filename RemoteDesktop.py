# Send message "LOGON" through the 9600 baud serial port
import time
import serial
import psutil
import subprocess
import win32api
import win32con


def turn_off_monitor():
    win32api.SendMessage(win32con.HWND_BROADCAST,
                         win32con.WM_SYSCOMMAND, win32con.SC_MONITORPOWER, 2)


def turn_on_monitor():
    win32api.SendMessage(win32con.HWND_BROADCAST,
                         win32con.WM_SYSCOMMAND, win32con.SC_MONITORPOWER, -1)


def main():

    ser = serial.Serial('COM11', 9600, timeout=1)

    while not ser.isOpen():
        pass

    is_remote_desktop = False

    print("Serial open")
    print("Opening parsec")
    executable_path = "C:\\Program Files\\Parsec\\parsecd.exe"
    subprocess.Popen([executable_path])

    parsec_running = False

    for i in range(5):
        for proc in psutil.process_iter():
            if proc.name() == "parsecd.exe":
                parsec_running = True
                break

        if parsec_running:
            break

        time.sleep(1)

    if parsec_running:
        ser.write(b"RUNNING")

    else:
        ser.write(b"ERROR")
        return


if __name__ == "__main__":
    main()
