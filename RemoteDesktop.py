# Send message "LOGON" through the 9600 baud serial port
import time
import serial
import win32com.client
import psutil
import subprocess


def main():
    ser = serial.Serial('COM11', 9600, timeout=1)

    while not ser.isOpen():
        pass

    is_remote_desktop = False

    print("Serial open")

    for i in range(5):
        line = ser.readline().strip()
        print(line)
        if line == b"REMOTE_DESKTOP":
            print("Remote desktop detected")
            ser.write(b"LOGON")
            is_remote_desktop = True
            break

        time.sleep(1)

    if is_remote_desktop:

        print("Opening parsec")
        executable_path = "C:\\Program Files\\Parsec\\parsecd.exe"
        subprocess.run([executable_path])

        parsec_running = False

        for i in range(5):

            if parsec_running:
                break

            time.sleep(1)
            for proc in psutil.process_iter():
                if proc.name() == "parsecd.exe":
                    parsec_running = True
                    break
    else:
        ser.write(b"ERROR")
        return

    if parsec_running:
        ser.write(b"RUNNING")

    else:
        ser.write(b"ERROR")
        return


if __name__ == "__main__":
    main()
