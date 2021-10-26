close all;
clear all;
clc;

%Planta
num=4;
den=[1 2 0];
G=tf(num,den);
%Planta sem compensa��o em malha fechada
Gmf=feedback(G,1);
%Polos de MF sem compensa��o
pole(Gmf)
%Lugar das ra�zes de G(s)
rlocus(G);

%C�lculo de Kp
s=-2+j*2*sqrt(3);
Kp=1/abs((0.125*(s+8)*4)/(s*(s+2)))

%Compensador
numc=0.5*[1 8];
denc=1;
Gc=tf(numc,denc)
%Planta com compensa��o em malha fechada
Gmfc=feedback(Gc*G,1);
%Polos de MF com compensa��o
pole(Gmfc)

%Resposta ao degrau
figure;
step(Gmf);
hold;
step(Gmfc);
legend('Sem compensa��o','PD');

%Lugar das ra�zes do sistema compensado
figure;
rlocus(Gc*G)

%Controlador PD com filtro passa-baixas (avan�o)
numc2=200*0.5*[1 8];
denc2=[1 200];
Gc2=tf(numc2,denc2)

%Planta com compensa��o PD como filtro passa-baixas em malha fechada
Gmfc2=feedback(Gc2*G,1);

%Polos de MF do sistema compensado por PD+filtro passa-baixas (avan�o)
pole(Gmfc2)

%Compara��o da compensa��o PD vs PD+filtro passa-baixas (avan�o)
figure;
step(Gmfc,linspace(0,6,1000));
hold;
step(Gmfc2,linspace(0,6,1000));
legend('PD','Avan�o');

%Compara��o entre a resposta em frequ�ncia do PD vs PD+filtro passa-baixas
%(avan�o)
figure;
bode(Gc);
hold;
bode(Gc2);
legend('PD','Avan�o');