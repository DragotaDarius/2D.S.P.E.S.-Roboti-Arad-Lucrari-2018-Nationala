import RPi.GPIO as GPIO
import MFRC522
import signal
import MySQLdb
import sys
import os
import copy
import time
import math
import Adafruit_CharLCD as LCD

credit=0
#GPIO.setmode(GPIO.BOARD)
#GPIO.setup(n, GPIO.OUT)
GPIO.setup(26, GPIO.OUT)
GPIO.setup(19, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(20, GPIO.OUT)
GPIO.setup(21, GPIO.OUT)
GPIO.setup(4, GPIO.OUT)


GPIO.output(13, 1)
GPIO.output(20, 1)
GPIO.output(21, 1)


# configurarea pinilor a raspberry pi-ului:
lcd_rs        = 27
lcd_en        = 24
lcd_d4        = 23
lcd_d5        = 17
lcd_d6        = 18
lcd_d7        = 22
lcd_backlight = 4
lcd_columns = 16
lcd_rows    = 2
lcd = LCD.Adafruit_CharLCD(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7,
                           lcd_columns, lcd_rows, lcd_backlight)
# Print a two line message
lcd.clear()
#lcd.autoscroll(True)
lcd.message('**Hello World!**\n====Get Suc!====')
#lcd.blink(True)
# se deschide conexiunea cu baza de date
connection = MySQLdb.connect (host = "127.0.0.1", user = "admin", passwd = "admin1234", db = "wordpress")
# prepararea unui obiect de tip cursor prin metoda cursor()
cursor = connection.cursor ()
# se executa SQL dupa metoda execute() 


continue_reading = True

# Capture SIGINT for cleanup when the script is aborted
def end_read(signal,frame):
    global continue_reading
    print "Ctrl+C captured, ending read."
    continue_reading = False
    GPIO.cleanup()


signal.signal(signal.SIGINT, end_read)

# Se creaza un obiect de clasa MFRC522
MIFAREReader = MFRC522.MFRC522()

flag_tag=5
status2=0

print "Welcome to the MFRC522 data read example"
print "Press Ctrl-C to stop."

# Acest loop este pentru cautarea cardurilor. Daca unul e gasit, el este scanat si intregistrat
while continue_reading:

    # Scaneaza pentru carduri
    (status,TagType) = MIFAREReader.MFRC522_Request(MIFAREReader.PICC_REQIDL)
    # print status
    # Daca s-a gasit un card
    if status == MIFAREReader.MI_OK:
        print "Card detected"
        flag_tag=5
    else:
        flag_tag=flag_tag-1
        if flag_tag<0:
            flag_tag=0
            status2=0

    # Scaneaza ID-ul a cardului
    (status,uid) = MIFAREReader.MFRC522_Anticoll()

    # Daca avem UID-ul continua
    if status == MIFAREReader.MI_OK and status2 == 0:
        status2=1
        # Print UID
        # print "Card read UID: %s,%s,%s,%s" % (uid[0], uid[1], uid[2], uid[3])
        buf = "%02X%02X%02X%02X" % (uid[0], uid[1], uid[2], uid[3])
        print buf
        try:
            sql="SELECT * FROM wp_credit, wp_users where wp_users.id=wp_credit.id and nfc='%s'" % (buf)
            rows_count = cursor.execute (sql)
            if rows_count > 0:
                data = cursor.fetchall ()
                for row in data :
                    row[1]
                credit=row[1]
                id=row[0]
                username=row[4]
                buf2= "Creditul pentru id=%s (%s) este:%s" % (id,username,credit)
                print buf2
                buf2= "Credit  User\n%04s    %s" % (credit,username)
                lcd.clear()
                lcd.message(buf2)
                time.sleep(5)
            else:
                print "Card neinregistrat"
                buf2= "Card\n   neinregistrat"
                lcd.clear()
                lcd.message(buf2)
                time.sleep(5)

        except:
           print "Error: unable to fecth data"


        if credit > 0:
            try:

                #se trimite un semnal la arduino care va elibera paharul
				#deoarece raspberry functioneaza pe 3.3V iar arduino pe 5V, semnalul trebuie sa fie
				#de 0V ca arduino sa il poata detecta fara probleme.
                lcd.clear()
                lcd.message('Se pregateste\nPaharul!')
                GPIO.output(26, 0)
                time.sleep(1)
                GPIO.output(26, 1)
                time.sleep(7)
				
                if GPIO.input(19):                  # semnal de la arduino
                    #se activeaza releul la care este atasata pompa
                    lcd.clear()
                    lcd.message('Curge suc in \npahar!')
					
                    GPIO.output(13, 0)
                    time.sleep(5)
                    GPIO.output(13, 1)
                    #gata
                    lcd.clear()
                    lcd.message('Sucul este gata\nPofta buna!')
                    time.sleep(10)
                    sql="UPDATE wp_credit SET credit = credit - 1 WHERE  id = '%s';" %(id)
                    cursor.execute (sql)
                    connection.commit()
                    buf2= "Credit  User\n%04s    %s" % (credit-1,username)
                    lcd.clear()
                    lcd.message(buf2)
                    time.sleep(5)
                    credit=0
                else:
                    print "Eroare Pahar"
                    lcd.clear()
                    lcd.message('Eroare Pahar')
                    time.sleep(5)
            except:
               print "Error: unable to fecth data"
               connection.rollback()
        lcd.clear()
        lcd.message('**Hello World!**\n====Get Suc!====')



cursor.close ()
