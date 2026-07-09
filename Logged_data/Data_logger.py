import serial
import datetime
import os

#Configuration
Port= "COM15"
Baud= 115200
Dir= "E:/R/RA_CSU/CSU_filament_bench_rig_with_encoder/Logged_data"

# Create filename with timestamp

timestamp= datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
filename=f"filament_{timestamp}.csv"
filepath= os.path.join(Dir,filename)

#Open serial port
ser= serial.Serial(Port,Baud)

#Open file and write header
f=open(filepath,'w')
f.write("length_mm,diameter1_mm,diameter2_mm\n")

print(f"Logging to : {filepath}")
print("Press Ctrl+c to stop.")

try:
    while True:
        line= ser.readline()  # read raw bytes
        line= line.decode().strip() #decode() converts bytes to string,
                                    #.strip() removes the newline character at the end.
        if not line.startswith('#'): # this loop removes initial outputs in serial monitor
            f.write(line+'\n')
            f.flush()   #force save immediately 
            print(line) #to check if its data logging  
except KeyboardInterrupt:
    print("\n Stopped by user.")

finally:
    f.close()
    ser.close()
    print("File and port closed cleanely")                        