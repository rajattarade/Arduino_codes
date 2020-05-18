int valmedio[5];
int analogPin = 1; //pin da collegare al rilevatore di corrente SCT 013 020
int zerovolt=0;
long Quantacorrenteoldtempo=0; //per evitare che controlli la corrente di continuo

void setup()
{
Serial.begin(19200);
Serial.println("Sketch: AlertHighPower");
delay(500);

//** **************************************************************** **//
//** Per il sensore di corrente – Rileva lo zerovolt                  **//
//** **************************************************************** **//
ZeroVolt();                                                      //** **//
//** **************************************************************** **//
}  // end setup

void loop()
{
//controlla la corrente
QuantaCorrente();
}    //end loop

void ZeroVolt()
{
//** **************************************************************** **//
//** Determino il valore da 2,5V a cui è collegato il sensore         **//
//** SCT 013-020. Lo calcolo ogni volta all’accensione dell’Arduino   **//
//** per evitare la deriva dei componenti.                            **//                   **
//** **************************************************************** **//

int max2 =0;
int min2 =9999;

valmedio[0]=analogRead(analogPin);
valmedio[1]=analogRead(analogPin);
valmedio[2]=analogRead(analogPin);
valmedio[3]=analogRead(analogPin);
valmedio[4]=analogRead(analogPin);

int punta=0;
int mediato=0;

long oldtime1;
oldtime1=millis();

while (millis()-oldtime1<=85)
{
valmedio[punta]=analogRead(analogPin);
if (punta<4)
{punta=punta+1;}
else
{punta=0;}

mediato=(valmedio[0]+valmedio[1]+valmedio[2]+valmedio[3]+valmedio[4])/5;

if (max2<mediato)
{max2=mediato;}
if (min2>mediato)
{min2=mediato;}

}

zerovolt = (max2+min2)/2;

Serial.print("zerovolt = " );
Serial.println(zerovolt);

}    //end zerovolt

int QuantaCorrente()
{
if (abs(millis()-Quantacorrenteoldtempo) >= 10000)   //entra nel ciclo solo ogni dieci secondi
{

long somma=0;
long conta=0;
int punta=0;
int mediato=0;
int i=0;
int PerZeroOk=0;
int tante = 10;             //indica quante mezze onde leggere. Con 10 semionde (5 periodi) ci mette 100ms

//leggi valori per costruire la prima media
valmedio[0]=analogRead(analogPin);
valmedio[1]=analogRead(analogPin);
valmedio[2]=analogRead(analogPin);
valmedio[3]=analogRead(analogPin);
valmedio[4]=analogRead(analogPin);

mediato=(valmedio[0]+valmedio[1]+valmedio[2]+valmedio[3]+valmedio[4])/5;

boolean onda=0;
if (mediato-zerovolt>0 )    //Se maggiore di uno allora per onda metto 1 altrimenti zero, Dice se l’onda è sopra o sotto lo zero
{onda=1;}

long TempoStart;             //variabile per calcolare quanto tempo ci mette
TempoStart=millis();

while (PerZeroOk<=tante && abs(millis()-TempoStart) < (tante+4)*20)
{
//Mediamo i valori letti per contenere gli spikes
valmedio[punta]=analogRead(analogPin);
if (punta<4)
{punta=punta+1;}
else
{punta=0;}
mediato=(valmedio[0]+valmedio[1]+valmedio[2]+valmedio[3]+valmedio[4])/5;
mediato=mediato-zerovolt;

// L’IF seguente Rileva il passaggio per zero e conseguentemente riesce a contare le semionde.
// Tuttavia per bassi assorbimenti di corrente non riesce a contarle bene e quindi fornisce un
// valore più basso di quello dovuto. E’ un problema che  si presenta solo per  basse correnti
// e quindi non inficia  il funzionamento del programma  perchè  lavora sulla fascia dei forti
// assorbimenti di corrente.

if ((onda==1 && mediato <0) || (onda==0 && mediato >0))
{
PerZeroOk=PerZeroOk+1;
onda=onda^B1;   //Cambia lo stato da 0 a 1 e viceversa
}

//In PerZeroOK=0 siamo in un punto a caso della prima semionda per cui ignoriamone i valori. Dobbiamo prendere sempre semionde intere.
if (PerZeroOk>=1)
{
somma=somma+abs(mediato);
conta=conta+1;
}
}

TempoStart=millis()-TempoStart;
somma=somma/conta;

Serial.print("Indicatore=");
Serial.print(somma);
Serial.print(" TempoElaborazione=");
Serial.print(TempoStart);
Serial.print(" conta=");
Serial.print(conta);
Serial.print(" Semionde=");
Serial.println(tante);

if (somma >110 )    //se il valore supera la soglia, qui impostata a 110, allora segnala il troppo assorbimento di corrente.
{
Serial.print("***************");
Serial.print("Troppa corrente");
Serial.print("***************");
}

Quantacorrenteoldtempo=millis();
}
}    //end QuantaCor
