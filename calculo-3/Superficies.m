%Como usar o c�digo: Digite as partes sem % direto no matlab que vai
%funcionar automaticamente. Pode alterar os c�digos para melhorar as
%figuras. Para isso utilize o comando "help" + nome da fun��o, por exemplo:
% help plot3
% Esse comando lista todas as op��es j� programadas da fun��o plot3.
% Use um c�digo por vez nesse caso. 

%%%%%%
%Exercicio 1
% Calcule a �rea da parte do plano 3x+2y+z=6 no primeiro octante.
x=[0:.01:5];
y=[0:.01:5];
[X, Y] = meshgrid(x,y);
Z=6-3*X-2*Y;
plot3(X,Y,Z);
xlabel x
ylabel y
zlabel z
%Observe que � um peda�o do plano de fato. Tente melhorar esse desenho.
%============================================
%Exerc�cio 2:
%Calcule a �rea da parte do parabol�ide hiperbolico z=y^2-x^2 que est�
%entre os cil�ndros x^2+y^2=1 e x^2+y^2=4.
x = [-4:.2:4];
y=[-4:.2:4];
[X, Y] = meshgrid(x,y);
Z = X.^2-Y.^2;
surf(X,Y,Z)
xlabel x
ylabel y
zlabel z
%=============================================
% Exerc�cio 3:
% Calcule a �rea da parte da superf�cie y=4x+z^2 que est� entre os planos
% x=0,x=1,z=0 e z=1.
x = [0:.01:1];
z=[0:.01:1];
[X, Z] = meshgrid(x,z);
Y = 4*X.^2+Z.^2;
surf(X,Y,Z)
xlabel x
ylabel y
zlabel z


