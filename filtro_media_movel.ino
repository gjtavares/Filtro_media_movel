/* 
 Gabriel Jeronimo
 2020
*/

#define Qtd_Amostras 8 // Número de amostras

float yMed(void);
float filtro(float);
float filtroMediaMovel(float);

float ym, inv_ym;
  
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() 
{
     ym=yMed();
     Serial.print(ym);
     Serial.print(',');
     //Serial.println(filtro(ym));
  	 Serial.println(filtroMediaMovel(ym));
  
     delay(1);
}

float yMed(void)
{  
  float randNum,ruido;
  randNum=random(-100,100)/100.0;
  ruido=1+5*randNum/100; // 5% de ruído (-0.95 a +1.05)
  return(ruido*analogRead(0));
}  

/*float filtro(float yin)
{
  float yout;
  static float yout_ant=0;  
  yout=1.2*yin;                 //lei de filtragem
  return(yout); 
}*/  

float filtroMediaMovel(float yin)
{
  static  int Leituras_anteriores[Qtd_Amostras]; // Buffer circular
  static  int Posicao = 0; // Posicao atual de leitura
  static long Soma=0; // Soma total do buffer circular
  static float Media = 0; // A media, Saída da função
  static bool zera_vetor = 1;  // Indica se é a primeira execução, zerando todo o buffer circular.
  
  if (zera_vetor){ // Zera todo o buffer circular
    for(int i=0; i<= Qtd_Amostras; i++){
      Leituras_anteriores[i] = 0;
    }
    zera_vetor = 0; // Atualiza a variável

  }
  
  Soma = yin - Leituras_anteriores[Posicao%Qtd_Amostras] + Soma; // Atualiza a soma total do buffer
  Leituras_anteriores[Posicao%Qtd_Amostras] = yin; // Atualiza o buffer
  Media = (float)Soma/(float)(Qtd_Amostras); // Calcula a média
  Posicao = (Posicao+1)%Qtd_Amostras;  // Atualiza a posção atual
  return((double)Media); // retorna o valor
}
