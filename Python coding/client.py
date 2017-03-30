
import socket
import time
delay = 5
TCP_IP_address = '' #Write IP address here
TCP_port = 50005   #Write port here

s = socket.socket() #s = socket.socket(socket.AF_INE, socket.SOCK_STREAM)
s.connect((TCP_IP_address, TCP_port))
increment = [0,4,8,12,16,20]
center_values = [0,0,0,0,0,0]
#s.send(center_values)
#time.sleep(delay) # delays for 2 seconds
#x=0
for x in range(0, 6):
    x_forward = [increment[x],0,0,0,0,0]
    #s.send(x_forward)
    #time.sleep(delay) # delays for 2 seconds
for x in range(0, 6):
    x_backward = [-increment[x],0,0,0,0,0]
    #s.send(x_backward)
    #time.sleep(delay) # delays for 2 seconds
    
for x in range(0, 6):
    y_forward = [0, increment[x],0,0,0,0]
    #s.send(y_forward)
    #time.sleep(delay) # delays for 2 seconds
for x in range(0, 6):
    y_backward = [0, -increment[x],0,0,0,0]
    #s.send(y_backward)
    #time.sleep(delay) # delays for 2 seconds
    
for x in range(0, 6):
    z_forward = [0,0, increment[x],0,0,0]
    #s.send(z_forward)
    #time.sleep(delay) # delays for 2 seconds
for x in range(0, 6):
    z_backward = [0,0, -increment[x],0,0,0,0]
    #s.send(z_backward)
    #time.sleep(delay) # delays for 2 seconds

for x in range(0, 6):
    roll_forward = [0,0,0, increment[x],0,0]
    #s.send(roll_forward)
    #time.sleep(delay) # delays for 2 seconds
for x in range(0, 6):
    roll_backward = [0,0,0, -increment[x],0,0]
    #s.send(roll_backward)
    #time.sleep(delay) # delays for 2 seconds
    
for x in range(0, 6):
    pitch_forward = [0,0,0,0, increment[x],0]
    #s.send(pitch_forward)
    time.sleep(delay) # delays for 2 seconds
    print pitch_forward[4]
for x in range(0, 6):
    pitch_backward = [0,0,0,0, -increment[x],0,0]
    #s.send(pitch_backward)
    time.sleep(delay) # delays for 2 seconds
    print pitch_backward[4]
