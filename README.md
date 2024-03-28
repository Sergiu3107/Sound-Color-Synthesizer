![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.001.png)

Sintezator de culoare-sonor![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.002.png)

Proiectare cu Microprocesoare![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.003.png)

Autor: Isac Sergiu Ionut Grupa: 30237

Facultatea de Automatica

si Calculatoare

11 Ianuarie 2024

Cuprins

[1 Descriere ](#_page2_x70.87_y70.87). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 2

1\.1 Componente folosite . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 2

[2 Functionalitati ](#_page4_x70.87_y252.28). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 4 [3 Convertire RGB ](#_page4_x70.87_y673.89). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 4 [4 Schema electrica a componentelor ](#_page6_x70.87_y70.87). . . . . . . . . . . . . . . . . . . . . . . . . . . 6 [5 Biografie ](#_page6_x70.87_y475.20). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6

1  Descriere

<a name="_page2_x70.87_y70.87"></a>Acest proiect consta intr-un dispozitiv care poate reda culorile sub forma de sunete, bazandu- se pe un senzor de culoare si un buzzer pasiv. Aria de culori pot fi selectate prin intermediul unei aplicatii Android, care la randul ei comunica cu placa de dezvoltare prin modulul bluetooth. Culoare care este perceputa de senzor este redata pe un display.

<a name="_page2_x70.87_y169.45"></a>1.1 Componente folosite

Arduino Mega 2560 este placa de dezvoltare prin care au fost conectate toate componentele folosite la acest proiect, prezentandu-se tot ce am avut nevoie pentru implementare.

![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.004.png)

Figura 1: Placa de dezvolatare

Senzorul de Culoare TCS230 este baza acestui proiect. Prin acesta a fost determinata intensitate fiecarei culori, convertand lungimea de unda a culorii intr-un semnal dreptunghiu-

lar de o anumita frecventa. Pentru citirea datelor au fost folosite librariile MD\_TCS230.h si FreqCount.h .

![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.005.png)

Figura 2: Placa de dezvolatare

Display ST7735 prezinta o comunicare SPI, afisand date din buffer pe un ecran de 128x120 pixeli, cu ajutorul librariilor Adafruit\_ST7735.h si Adafruit\_GFX.h .

![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.006.png)

Figura 3: Display SPI

Buzzer pasiv a fost folosit pentru redare frecventei asosciate unei culori. Libraria FreqCo- unt.h interfera cu functia tone() , de accea am folosit alte librarii pentru readarea sunetului : TimerFreeTone.h si toneAC.h .

![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.007.png)

Figura 4: Buzzer pasiv

Modul Bluetooth HC-05 folosit pentru comunicarea cu aplicatia Bluetooth, urmand ca datele primite sa fie citite de pe serial.

![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.008.png)

Figura 5: Modul Bluetooth

Breadboard folosit pentru plasarea componentelor prezentate.

![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.009.png)

Figura 6: Breadboard

2  Functionalitati

<a name="_page4_x70.87_y252.28"></a>Selectare culorilor

Posibil ca unii utilizatorii sa nu fie interesati toate culorile disponibile, de accea, prin inter- mediul aplicatie Bluetooth, acestia isi pot alege gama de culori ca se pot reda prin buzzer.

![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.010.jpeg)

Figura 7: Aplicatia Bluetooth

Pentru utilizare, intai de toate, este necesara conectare prin Bluetooth la modulul HC-05 , apoi legarea acestuia cu aplicatia prin Connect device .

3  Convertire<a name="_page4_x70.87_y673.89"></a> RGB

Datele primite de la sezorul de culorare sunt de forma RGB, componente ale unei culori. Pentru redarea sub forma de sunet aceasta valoare a fost convertita la lungime de unda, prin urmatoarea metoda:

1. Intai a fost convertita voloara RGB la HUE, pentru a converti 3 valori intr-una.

![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.011.png)

Figura 8: Hue

2. Valoare HUE a fost ulterior convertita la lungime de unda ( λ) conform formulei:

λ = λmax − λrange ∗HUE

huemax

Lungimea de unda a fost folosita pentru a determina intervalele pentru fiecare culoare dispo-

nibila.

1 float rgbToWavelenght(int r, int g, int b){

2 float R = r / 255.0;

3 float G = g / 255.0;

4 float B = b / 255.0;

5

6

7 // rgb to hue

8 float hue;

9 float maxV = max(R, max(G,B));

10 float minV = min(R, min(G,B));

11

12 if(maxV == R)

13 hue = (G-B)/(maxV-minV);

14

15 if(maxV == G)

16 hue = 2.0 + (B-R)/(maxV-minV);

17

18 if(maxV == B)

19 hue = 4.0 + (R-G)/(maxV-minV);

20

21 hue \*= 60.0;

22 if(hue < 0.0)

23 hue += 360.0;

24

25 // hue to waveleght

26

27 // waveleght -> [400, 700]

28 // hue -> [0, 270]

29 float wavelenght = 700 - (300/270 \* hue); 30

31 return wavelenght;

32

33 }

4  Schema<a name="_page6_x70.87_y70.87"></a> electrica a componentelor![](docs/images/Aspose.Words.0cab1afa-6ae7-4203-a50b-990a9250dac3.012.png)

Figura 9: Schema

5  Biografie
- <a name="_page6_x70.87_y475.20"></a>MD\_TCS23
- FreqCount
- ST7735
- TimerFreeTone
- Color to Sound
- RGB to HUE
- Wavelenght from HUE
- Wavelenght to Color
6
