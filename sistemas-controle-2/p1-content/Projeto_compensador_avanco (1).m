close all;
clear all;
clc;

%Planta
num=4;
den=[1 2 0];
G=tf(num,den)
%Planta sem compensa��o em malha fechada
Gmf=feedback(G,1)
%Polos de MF sem compensa��o
pole(Gmf)

%Lugar das ra�zes de G(s)
rlocus(G)

%Verifica��o da condi��o de �ngulo
s=-2+j*2*sqrt(3);
angle(4/(s*(s+2)))*180/pi %O resultado � em rad que � convertido para graus.

%C�lculo de Kc
Kc=1/abs(4/(s*(s+4)))

%Compensador
numc=4*[1 2];
denc=[1 4];
Gc=tf(numc,denc)

%Planta com compensa��o em malha fechada
Gmfc=feedback(Gc*G,1);
Gmfc=minreal(Gmfc)
%Polos de MF com compensa��o
pole(Gmfc)

%Resposta ao degrau
figure;
step(Gmf);
hold;
step(Gmfc);
legend('Sem compensa��o', 'Com compensa��o');

%Lugar das ra�zes da planta compensada
figure;
rlocus(Gc*G);