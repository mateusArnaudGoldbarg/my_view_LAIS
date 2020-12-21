import serial
import pandas as pd
import time

ser = serial.Serial('COM5',9600)
print("oi")
vol = 0
res = 0
    
poi = []
primeiro = True
while 1:
    leitura = ser.readline().rstrip()
    a = str(leitura)
    b = a.split('\'');
    
    v = b[1].split('v')
    
    if v[0] == '':
        vol = round(float(v[1]),3)
        
    r = b[1].split('r')
    
    if r[0] == '':
        res = round(float(r[1]),3)
    i = round(vol/(res+220),5)
    
    medidas = [res,vol,i]
    poi.append(medidas)
    final = pd.DataFrame(poi,columns=['resistencia','tensao','corrente'])
    print(final)
    #print()
    final.to_csv(r'C:\Users\mateu\Documents\UFRN\lais\a.csv')
