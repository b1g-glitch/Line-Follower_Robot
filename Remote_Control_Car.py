import keyboard
import serial
import time
import serial.tools.list_ports

for p in serial.tools.list_ports.comports():
    print(p.device, "-", p.description)
    
print(serial.__file__)
PORT = "COM4"   #varies
BAUD = 9600

ser = serial.Serial(PORT, BAUD, timeout=1)
time.sleep(2)

last_cmd = None

def send(cmd):
    global last_cmd
    if cmd != last_cmd:
        ser.write(cmd.encode())
        last_cmd = cmd
        print("Sent:", cmd)

try:
    while True:
        if keyboard.is_pressed('w'):
            send('w')
        elif keyboard.is_pressed('s'):
            send('s')
        elif keyboard.is_pressed('a'):
            send('a')
        elif keyboard.is_pressed('d'):
            send('d')
        else:
            send('x')

        time.sleep(0.05)

except KeyboardInterrupt:
    ser.write(b'x')
    ser.close()
    print("Stopped")