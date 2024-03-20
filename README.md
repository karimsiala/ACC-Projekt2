# ACC-Projekt2
# Adaptive Cruise Control (ACC) Sensordaten-Integration

Dieses Repository enthält den Arduino-Quellcode und das MATLAB/Simulink-Modell zur Erfassung und Verarbeitung von Distanzdaten mit drei TFmini Plus LiDAR-Sensoren für ein  Adaptive Cruise Control (ACC) Studienprojekt für das IRT Buggy.

## Arduino-Code

Der Arduino-Code liest die Distanzdaten von drei TFmini Plus Sensoren und überträgt diese Daten seriell an einen Host-PC. Jeder Distanzwert wird als 4-Byte Fließkommazahl (float) übertragen. Der Code befindet sich im Verzeichnis `FinalSensorReadSend`. 

### Output-Format

Jeder Output-Datensatz beginnt mit einem Header-Byte 'A', gefolgt von den Distanzdaten der drei Sensoren und endet mit einem Zeilenumbruch (`\n`). Bei einem Fehler in der Distanzmessung wird der Wert `-1.0` gesendet.

Hier ist ein Beispiel für einen seriellen Output-Datensatz (in Bytes dargestellt):

```
41 // Header 'A'
xx xx xx xx // Distanzwert von Sensor 1 als 4 Bytes
xx xx xx xx // Distanzwert von Sensor 2 als 4 Bytes
xx xx xx xx // Distanzwert von Sensor 3 als 4 Bytes
0A // Zeilenumbruch ('\n')
```

Bei einem Messfehler würde der Output so aussehen:
```
41 // Header 'A'
BF 80 00 00 // -1.0 repräsentiert als 4 Bytes im Falle eines Fehlers
BF 80 00 00 // Wiederholung für jeden Sensor, der einen Fehler aufweist
BF 80 00 00
0A // Zeilenumbruch ('\n')
```

Die Übertragung erfolgt mit einer Baudrate von 115200.

### Anschlüsse

- `RX1/TX1` wird für den Sensor 1 verwendet
- `RX2/TX2` wird für den Sensor 2 verwendet
- `RX3/TX3` wird für den Sensor 3 verwendet
  
![Untitled Sketch 2_Schaltplan](https://github.com/karimsiala/ACC-Projekt2/assets/61633482/61d0bf0e-5613-4a12-ad2b-9aaba742a9de)

### Verwendung

Laden Sie den Code auf einen Arduino Mega 2560 hoch und verbinden Sie ihn über USB mit Ihrem PC. Stellen Sie sicher, dass Sie die korrekte COM-Port-Nummer in Ihrem MATLAB/Simulink-Modell eingeben.

## MATLAB/Simulink-Modell

Das MATLAB/Simulink-Modell liest die übertragenen Daten und verarbeitet sie für das ACC-System. Die Modell-Dateien befinden sich im Verzeichnis `Simulink Model`.



![image](https://github.com/karimsiala/ACC-Projekt2/assets/61633482/f5bdaeff-827d-4f28-a8c3-1c081d411112)
