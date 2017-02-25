1)NUME PRENUME : VIJAEAC CRISTIAN-OCTAVIAN
  GRUPA SERIE : 335CB

2)UTILIZARE APLICATIE:
-Taste: W - miscare inainte
	   A - miscare in stanga
        D - miscare dreapta
        S - miscare inapoi
	   
-Mouse: -miscarea mouseului duce la reorientarea 		 	obiectului,intotdeaunca cu fata spre acesta
	   -click stanga pentru a lansa un proiectil/glont

-Stari: -initial playerul se afla in punctul 0,0,0
        -inamicii vor aparea din coltul stang al ecranului o data 	  la 5 secunda,acest timp fiind decrement la fiecare 
       nou inamic pana la valoarea de 2 secunde
	  -acestia au o cale sub forma literei Z din coltul stanga 
	  sus pana in dreapta jos
        -fiecare inamic are numarul lui de vieti astfel:primul o 
	  viata,al doilea doua vieti,al 3-lea 3 vieti etc.
        -cele 3 turnuri sunt pozitionate aproape de player pentru 
	  a-l apara.Acestea lanseaza gloante o data la 1 secunda
       catre cel mai apropiat player.Daca il nimeresc,acesta
	  va pierde o viata
	  -turnurile se orienteaza de fiecare data spre cel mai
       apropiat player
	  -cand un inamic moare,acesta va executa o animatie de 
	  scalare treptata la 0 si,in acelasi timp,o rotatie in
	  jurul axei OZ
        -playerul are 3 vieti afisate sub forma unor sfere care
	   se invart in jurul lui pe cele 3 axe.Cand acesta pierde
	   o viata,una dintre sfere dispare
	   -playerul pierde o viata atunci cand un inamic ajunge
	   in coltul dreapta jos
        -cand pierde toate vietile,jocul se termina,scena se
	   blocheaza iar jucatorul executa o animatie de rotire
	   in jurul axei OZ pana intr-un punct
	   -playerul detine 3 tipuri de arme:
		-pistol:trage o data la 0.8 secunde,pe distanta mica
		si fiecare glont poate lua maxim o viata
		-shotgun:trage o data la 0.5 secunde,pe distanta mai 
		mare si fiecare glont poate lua maxim 2 vieti
		-grenade:trase o data la 3 secunde,pe distanta foarte
		mica insa cu un impact mare:pot lua 5 vieti


3)DETALII DE IMPLEMENTARE:
GameObject - clasa parinte care contine caracteristicile fiecarui 		obiect in parte :pozitie,rotatie,scalare,tip de 
		glont,vector de gloante,etc
Player - clasa care contine caracteristicile playerului precum 
	  si functiile necesare miscarii pe harta si pozitionarii
	  camerei astfel incat sa se realizez efectul de THIRD
	  person
Enemy - clasa care contine caracteristicile fiecarui inamic in 			parte
Bullet - clasa care contine caracteristicile fiecarui glont in 			parte
Tower - clasa care contine caracteristicile fiecarui turn in 
		parte
!Clasele Player,Enemy,Bullet,Tower mostenesc clasa parinte GameObject.

Game - clasa care realizeaza toate operatiile si transformarile 	necesare realizarii acestui joc
	-Init() - initializeaza 	playerul,camerele,meshele,primul inamic,turnurile,etc
	-AddNewEnemy() - construieste un nou jucator dupa o perioada de timp asa 	cum este mentionat in enunt,seteaza caracteristicile acestuia 
	-EnemyEscapedDetection() - verifica daca un inamic a reusit sa ajunga in coltul din dreapta jos
       -TowerHitDetected() - verifica daca unul din gloantele
lasate de catre un turn si-a atins tinta
	-SetEnemies - updateaza pozitia fiecarui inamic la fiecare frame	
	-SetLifes() - in functie de numarul de vieti ale jucaturului,se plaseaza in scena cele 3 sfere care se rotesc in jurul acestuia reprezentand vietile ramase
	sub forma unor dreptunghiuri,in functie de valoarea variabilei "no_lifes"
	-SetPlayerAndCamera() - updateaza pozitia playerului la fiecare frame precum si cea a camerei.In functie de arme se alege
si tipul de view:First pentru arma 2,Third pentru armele 1 si 3
	-SetTowers()- plaseaza turnurile in scena si verifica distantele dintre fiecare turn si inamicii.Daca un inamic se afla la o distanta mica fata de turn,acesta va incarca un glont si va updata vectorul de gloante.
			-de asemenea,pentru fieace turn se ia vectorul 
de gloante si se introduc acestea in scena in functie de noile 
pozitii
	-TriggerPlayer() - updateaza pozitia fiecarui proiectil la fiecare frame.Mai intai,se verifica daca distanta maxima pe care un glont de un anumit tip o poate parcurge a fost atinsa
	-PlayerHitDetected() - verifica daca unul din gloantele
lansate de catre player si-au atins tinta si daca da,se scade
numarul de vieti al inamicului in consecinta
	-EnemyDeadAnimation - daca un inamic are numarul de vieti
<=0 atunci se va executa o animatie de rotire in jurul axei OZ
a acestui si de scalare pana cand inamicul va disparea de pe
ecran
	-PlayerDeadAnimation() - daca playerul ramane fara vieti,
jocul se termina.Astfel,toti inamicii,turnurile,gloantele sunt repuse in scena in aceeasi pozitie(Scena se blocheaza) iar playerul va executa o animatie de rotatie in jurul axei OZ pana cand acesta "ajunge la pamant"
	-CreateMiniMAp() - functie ce schimba viewportul si il plaseaza in scena.De asemnea,toatte obiectele aflate in scena mare sunt plasate in noua scena
	-Update() - apeleaza functiile de mai sus si updateaza fereastra cu noile informatii obtinute
	-OnInputUpdate() - deplasarea playerului de-a lungul celor 2 axe(inainte,inapoi,stanga,dreapta stanga,dreapta) precum si selectarea armei de care avem nevoie
	-OnMouseMove() - in functie de pozitia mouseului pe ecran se roteste playerul 
	-OnMouseBtnPress()-un nou proiectil este construit si adaugat in vectorul in functie de tipul de arma aleasa 

4)PROBLEME APARUTE:
-Calcularea si recalcularea vectorilor forward,up,right ai playerului.Mult timp camera nu functiona cum trebuie din cauza acestui lucru.
-Rotatiile celor 3 sfere reprezentant vietile playerului in functie de coordonatele playerului
-Dificultate in crearea minimap-ului,mai exact setarea corecta a proiectiei ortogonale

5) COTINUTUL ARHIVEI
-

6)STATUS IMPLEMENTARE FUNCTIONALITATI
Toate punctele obligatorii din cadrul acestei teme au fost atinse in proiectul meu.
Nu exista bonus.

			

