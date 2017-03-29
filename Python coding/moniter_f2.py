import serial
import socket
#import client
import xlwt

book = xlwt.Workbook(encoding="utf-8")
sheet1 = book.add_sheet("Sheet 1")
sheet1.write(0, 0, "Actuator 1 difference")
sheet1.write(0, 1, "Actuator 2 difference")
sheet1.write(0, 2, "Actuator 3 difference")
sheet1.write(0, 3, "Actuator 4 difference")
sheet1.write(0, 4, "Actuator 5 difference")
sheet1.write(0, 5, "Actuator 6 difference")


TCP_IP_address = '' #Write IP address here
TCP_port = 50005
BUFFER_SIZE = 1024

try:
    s = socket.socket()                # s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) Create object
    s.connect((TCP_IP_address, TCP_port))       # connect to the port
    print 'waiting for connection'
except socket.error, (value,msg):
    if(s):
        s.close()
    print 'could not open socket: ' + msg


Data =  list() #Making a list to save data
len_1 = [0,0,0,0,0,0] #initialize array for acutual lenth 
e_len = [0,0,0,0,0,0]#initialzing array for error data 
ArduinoSerialData = serial.Serial('COM5', 9600) #REETTING DATA FROM CENTRAL BOARD
z=1
x=0
row = 0
while (z == 1):
    row = row+1
    cmd_data = s.recv(BUFFER_SIZE)
    if (ArduinoSerialData.inWaiting()>0): #reading data from central board
        Data = ArduinoSerialData.readline()#.rstrip('\0') # Saving received data in list
        i = 0
        k = 0

        for x in range(0, 200): #this for loop is for read the recieved data to check if there are commas 
            if(Data[x]==','): 
                len_1[k] = int(Data[i:x]) #this converts the string data to intiger
                                                      #len_1.append(int(Data[i:x]))
                k = k+1
                i = x+1
                if (k==6):
                    k=0
                    break

                    
        for y in range(0, 6):
            e_len[y] = cmd_data[y] - len_1[y]# calculates the diffrence for comanded and theactual values
            sheet1.write(row, y, e_len[y])
        print "Error of actuator |1-> %d"%(e_len[0]),"|2-> %d"%(e_len[1]),"|3-> %d"%(e_len[2]),"|4-> %d"%(e_len[3]),"|5-> %d"%(e_len[4]),"|6-> %d"%(e_len[5])
        book.save("Error.xls")
#s.close()
