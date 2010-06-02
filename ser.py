import serial,sys

print "=" * 78
print "= Dummy Serial dumper" 
print "=" * 78

ser = None 

def main():
    ser = serial.Serial('/dev/'+sys.argv[1], 57600, timeout=2)

    while 1:
        data = ser.readline()[0:-1]
        if len(data) > 0:
            print "AVR> " + data
        else:
            print ".",
            sys.stdout.flush()


try:
    main()
except KeyboardInterrupt:
    if ser: ser.close()
    print "exit..."
